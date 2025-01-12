#include "utils/utils.hpp"

string input_file;   //to pairnoyme apo main
string output_file;

int READ_DATA2(DATA2& data){


    ptree root;
    read_json(input_file, root);
    data.instance_uid=root.get<string>("instance_uid", "NOT FOUND");
    cout<<data.instance_uid<<endl;
    string p=root.get<string>("num_points", "NOT FOUND");
    data.num_points=stoi(p);
    cout<<data.num_points<<endl;
    


    //Read whole vector
    BOOST_FOREACH(const ptree::value_type &v , root.get_child("points_x")){
        data.points_x.push_back(v.second.get_value<int>());
    }
    cout<<"\nPOINTS_X"<<endl;

    for(int i=0; i<data.points_x.size(); i++){
        cout<<data.points_x[i]<< " ,";
    }


    //Read whole vector
    BOOST_FOREACH(const ptree::value_type &v , root.get_child("points_y")){
        data.points_y.push_back(v.second.get_value<int>());
    }
    cout<<"\nPOINTS_Y"<<endl;
    for(int i=0; i<data.points_y.size(); i++){
        cout<<data.points_y[i]<< " ,";
    }



    //Read whole vector
    BOOST_FOREACH(const ptree::value_type &v , root.get_child("region_boundary")){
        data.region_boundary.push_back(v.second.get_value<int>());
    }
    cout<<"\nREGION_BOUND"<<endl;
    for(int i=0; i<data.region_boundary.size(); i++){
        cout<<data.region_boundary[i]<< " ,";
    }



    data.num_constraints = root.get<int>("num_constraints", -1);
    cout<<"\nNUM CONSTRAINTS"<<endl;
    cout<<data.num_constraints<<endl;




    BOOST_FOREACH(const ptree::value_type &v, root.get_child("additional_constraints")){
        

        auto inner=v.second.begin();
        int first=inner->second.get_value<int>();
        ++inner;
        int second=inner->second.get_value<int>();

        // Create a vector to hold the pair
        vector<int> subvector = {first, second};
        data.additional_constraints.push_back(subvector);
     

    }
    cout<<"\nADDITIONAL CONSTRAINTS"<<endl;
    for(const auto& sub : data.additional_constraints){
        cout<<"["<<sub[0]<<","<<sub[1]<<"] ,";
    }
    
    // Read new fields
    data.method = root.get<string>("method", "NOT FOUND");
    cout << "\nMETHOD: " << data.method << endl;

    // Read parameters (nested object)
    BOOST_FOREACH(const ptree::value_type& param, root.get_child("parameters")) {
        data.parameters[param.first] = param.second.get_value<double>();
    }
    cout << "\nPARAMETERS:" << endl;
    for (const auto& param : data.parameters) {
        cout << param.first << ": " << param.second << ", ";
    }

    data.delaunay = root.get<bool>("delaunay", false);
    cout << "\nDELAUNAY: " << boolalpha << data.delaunay << endl;



    return 0;

}



int Contrained_Delaunay(Custom_CDT& cdt,DATA data)

{

    //CDT cdt;
    vector<CDT::Vertex_handle> vertices;

    for(int i=0; i<data.num_points; i++){
        Point p(data.points_x[i], data.points_y[i]);
        vertices.push_back(cdt.insert(p));
    }

    for(const auto& con: data.additional_constraints){
        int index1=con[0];
        int index2=con[1];
        cdt.insert_constraint(vertices[index1], vertices[index2]);

    }

//ADDED THIS ON 25/12/24
    const vector<int>& boundaries = data.region_boundary;
    int num_boundaries = boundaries.size();
    for (int i = 0; i < num_boundaries; i++) {
        int index1 = boundaries[i];
        int index2 = boundaries[(i + 1) % num_boundaries]; // Wrap around to create a closed loop
        cdt.insert_constraint(vertices[index1], vertices[index2]);
    }
    //cout<<"CONSTRAINED DELAUNAY TRINGULATION: DONE"<<endl;
    return 0;

}

Point find_height_intersection(Point a, Point b , Point c){
    RT m_ac, m_h;

    // Διαίρεση με 0
    if ((c.x() - a.x()) == 0) {
        return Point(-9999, -9999); 
    }

 
    m_ac = (c.y() - a.y()) / (c.x() - a.x());   // Κλίση ευθείας AC
    if (m_ac == 0) {
       
        return Point(-9999, -9999);  
    }

    m_h=-1/m_ac;

    RT e_ac=a.y() - m_ac*a.x() ;    //ευθεία AC
    RT e_h=b.y() - m_h*b.x(); //εξίσωση υψους από b




    RT denom = (m_ac - m_h);
    if (denom == 0) {
        return Point(-9999, -9999); 
    }

    RT x_inter = (e_h - e_ac) / denom;
    RT y_inter = m_ac * x_inter + e_ac;

 
    return Point(x_inter, y_inter);


}

Point point_to_h(Custom_CDT& cdt, CDT::Face_handle face, DATA data, int i){
    CDT::Vertex_handle v0=face->vertex((i+1)%3);
    CDT::Vertex_handle v1=face->vertex(i);
    CDT::Vertex_handle v2=face->vertex((i+2)%3);
    if (v0 == nullptr) {
        cerr << "Vertex 0 is null!" << endl;
        return Point(-1.0,-1.0);
    }
    if (v1== nullptr) {
        cerr << "Vertex 1 is null!" << endl;
        return Point(-1.0,-1.0);
    }
    if (v2== nullptr) {
        cerr << "Vertex 2 is null!" << endl;
        return Point(-1.0,-1.0);
    }
    Point a = v0->point();
    Point b = v1->point();
    Point c = v2->point();
  //cout<<"["<<a.x()<<","<<a.y()<<"]"<<" ["<<b.x()<<","<<b.y()<<"]"<<" ["<<c.x()<<","<<c.y()<<"]"<<endl;
    Point steiner = find_height_intersection(a,b ,c);

    CDT::Vertex_handle vh = cdt.insert_no_flip(steiner);
    if (vh == nullptr) {
        cerr << "Error: Insertion returned a null vertex handle." << endl;
    } 
    return steiner;
}


void checking(Custom_CDT& cdt, DATA2& data2){
    DATA data;
    data.additional_constraints=data2.additional_constraints;
    data.instance_uid=data2.instance_uid;
    data.num_constraints=data2.num_constraints;
    data.num_points=data2.num_points;
    data.points_x=data2.points_x;
    data.points_y=data2.points_y;
    data.region_boundary=data2.region_boundary;
    vector<pair<CDT::Face_handle, int>> obtuses=check_for_obtuse(cdt);
    cout<<"obtuses [0]"<<endl;
    cout<<obtuses.size()<<endl;
    int i=0;
    int j=0;
    srand(time(0));
   while(obtuses.size()>1 ){
        Point steiner=point_to_h(cdt, obtuses[j].first, data, obtuses[j].second);
        if(steiner!=Point(-1.0,-1.0)){
            cout<<"βαλαμε με προτζεκτιον και έχουμε από "<<obtuses.size()<<" -> "<<check_for_obtuse(cdt).size()<<endl;
            i++;
        }
    
        obtuses=check_for_obtuse(cdt);

        j=rand()%obtuses.size();
        
        
   }
}

vector<pair<CDT::Face_handle, int>> check_for_obtuse(Custom_CDT& cdt) {
    vector<pair<CDT::Face_handle, int>> obtuses_i;
    int count = 0;

    for (CDT::Face_iterator ft = cdt.faces_begin(); ft != cdt.faces_end(); ++ft) {

        // Έλεγχος εγκυρότητας προσώπου
        if (cdt.is_infinite(ft)) {
            continue;  // Αγνοούμε τα άπειρα πρόσωπα
        }
        
        // Έλεγχος για ατελή σημεία
        for (int i = 0; i < 3; i++) {
            if (cdt.is_infinite(ft->vertex(i))) {
                cerr << "Error: Vertex " << i << " is infinite." << endl;
                continue;
            }
        }
        
        // Πάιρνω τα σημεία που ορίζουν το τρίγωνο
        CDT::Vertex_handle v1 = ft->vertex(0);
        CDT::Vertex_handle v2 = ft->vertex(1);
        CDT::Vertex_handle v3 = ft->vertex(2);

        if (cdt.is_infinite(v1) || cdt.is_infinite(v2) || cdt.is_infinite(v3)) {
            cerr << "Error: Infinite vertices found!" << endl;
            continue;
        }

        Point p = v1->point();
        Point q = v2->point();
        Point r = v3->point();
        
        // Υπολογισμός γωνιών
        auto ang_pqr = CGAL::angle(p, q, r); // Γωνία με κέντρο το q
        auto ang_qrp = CGAL::angle(q, r, p); // Γωνία με κέντρο το r
        auto ang_rpq = CGAL::angle(r, p, q); // Γωνία με κέντρο το p

        CGAL::Orientation orientation = CGAL::orientation(p, q, r);
        if (orientation != CGAL::COUNTERCLOCKWISE) {
            cerr << "Points are not in counter-clockwise orientation!" << endl;
            continue; // Αγνόηση αυτού του τριγώνου
        }

        // Έλεγχος αν είναι αμβλεία γωνία και εισαγωγή στη λίστα
        if (ang_pqr == CGAL::OBTUSE) {
            obtuses_i.emplace_back(ft, 1); // Σημείο q, δείκτης 1
        }
        if (ang_qrp == CGAL::OBTUSE) {
            obtuses_i.emplace_back(ft, 2); // Σημείο r, δείκτης 2
        }
        if (ang_rpq == CGAL::OBTUSE) {
            obtuses_i.emplace_back(ft, 0); // Σημείο p, δείκτης 0
        }

        count++;
    }

    return obtuses_i;
}

bool is_valid_steiner_point(const Custom_CDT& cdt, const CDT::Face_handle& face, const Point& steiner, 
                            DATA data) {
    vector<int> boundaries=data.region_boundary;
    vector<vector<int>> additional_constraints=data.additional_constraints;
    vector<Point> boundary_points;
    vector<Point> points;

    for(int i=0; i<data.points_x.size(); i++){
        points.push_back(Point(data.points_x[i], data.points_y[i]));
    }
    for (int idx:boundaries){
        //cout<<"idx is: "<<idx<<endl;
        boundary_points.push_back(Point(data.points_x[idx], data.points_y[idx]));
        
    }
    typename Custom_CDT::Locate_type locate_result;
    int li = -1; 
    if (cdt.number_of_vertices() == 0) {
        cerr << "CDT is empty!" << endl;
        return false;
    }
    
    //Εντοπισμός του σημείου στο triangulation
    CDT::Face_handle fh = cdt.locate(steiner, locate_result, li);

    //Έλεγχος αν το σημείο είναι εκτός hull
    if (!cdt.is_infinite(face) && locate_result == Custom_CDT::OUTSIDE_AFFINE_HULL) {
        cerr << "Error: Steiner point is outside the triangulation domain." << endl;
        return false;
    }
    if (abs(steiner.x()) > 1e5 || abs(steiner.y()) > 1e5) {
        //cerr << "Error: Steiner point has unreasonably large coordinates." << endl;
        return false;
    }



    //Έλεγχος αν το σημείο βρίσκεται εντός του boundary
    CGAL::Bounded_side side = CGAL::bounded_side_2(boundary_points.begin(), boundary_points.end(), steiner, K());
    if (side == CGAL::ON_UNBOUNDED_SIDE) {
       // cerr << "Error: Steiner point is outside the region boundary." << endl;
        return false;
    }
    for (const auto& constraint : additional_constraints) {
        if (constraint.size() != 2) continue; // Αγνόηση μη έγκυρων constraints
        Point p1 = points[constraint[0]];
        Point p2 = points[constraint[1]];
        if (CGAL::collinear(p1, p2, steiner)) {
            return false;
        }
    }



    return true;
}

Point point_to_middle(Custom_CDT& cdt, CDT::Face_handle face, DATA data, int i ) {
   // cout<<"Stiner point to be inserted with: MIDDLE"<<endl;

    if (!face->is_valid()) {
        cerr << "Error: Face is invalid." << endl;
        return Point(-1.0,-1.0);
    }

    CDT::Vertex_handle v0=face->vertex((i+1)%3);
    CDT::Vertex_handle v1=face->vertex(i);
    CDT::Vertex_handle v2=face->vertex((i+2)%3);
    if (v0 == nullptr) {
        cerr << "Vertex 0 is null!" << endl;
        return Point(-1.0,-1.0);
    }
    if (v1== nullptr) {
        cerr << "Vertex 1 is null!" << endl;
        return Point(-1.0,-1.0);
    }
    if (v2== nullptr) {
        cerr << "Vertex 2 is null!" << endl;
        return Point(-1.0,-1.0);
    }

    Point a = v0->point();
    Point b = v1->point();
    Point c = v2->point();
    Point steiner((a.x() + c.x()) / 2.0, (a.y() + c.y()) / 2.0);
    if (!is_valid_steiner_point(cdt, face, steiner, data)) {
        return Point(-1.0,-1.0);
    }

    if (!face->is_valid()) {
        cerr << "Error: Face is invalid." << endl;
        return Point(-1.0,-1.0);
    }
    CDT::Vertex_handle vh = cdt.insert_no_flip(steiner);
    if (vh == nullptr) {
        cerr << "Error: Insertion returned a null vertex handle." << endl;
    } 

    return steiner ;
}

Point point_to_circumcenter( Custom_CDT& cdt, CDT::Face_handle face, DATA data, int i){
    

    CDT::Vertex_handle v0=face->vertex(0);
    CDT::Vertex_handle v1=face->vertex(1);
    CDT::Vertex_handle v2=face->vertex(2);
    if (v0 == nullptr) {
        cerr << "Vertex 0 is null!" << endl;
        return Point(-1.0,-1.0);
    }
    if (v1== nullptr) {
        cerr << "Vertex 1 is null!" << endl;
        return Point(-1.0,-1.0);
    }
    if (v2== nullptr) {
        cerr << "Vertex 2 is null!" << endl;
        return Point(-1.0,-1.0);
    }
    Point a = v0->point();
    Point b = v1->point();
    Point c = v2->point();
    Point steiner;
    try{
        steiner=CGAL::circumcenter(a,b,c);
    }
    catch(const exception& e){
        cout<<"Error finding the circumcenter, using Centroid instead: "<<e.what()<<endl;
        steiner = CGAL::centroid(a, b, c);
    }
    
    if (!is_valid_steiner_point(cdt, face, steiner, data)) {
        return Point(-1.0,-1.0);
    }
    if (cdt.is_infinite(face)) {
        cerr << "Warning: Circumcenter is outside. Using centroid instead." << endl;
        steiner = CGAL::centroid(a, b, c);
    }
    if (!face->is_valid()) {
        cerr << "Error: Face is invalid." << endl;
        return Point(-1.0,-1.0);
    }
    CDT::Vertex_handle vh = cdt.insert_no_flip(steiner);
    if (vh == nullptr) {
        cerr << "Error: Insertion returned a null vertex handle." << endl;
        
    }
    return steiner;
}