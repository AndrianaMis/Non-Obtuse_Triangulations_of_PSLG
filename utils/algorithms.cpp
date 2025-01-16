
#include "utils.hpp"

/////////////////////////////////////////// PART 2 /////////////////////////////////////////////////

map<string, function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)>>map_of_functions;   //map που περιέχει [ονομα, συνάρτηση_sp] 
vector<Point> all_steiners_added;   //vector που καταγράφει όλα τα steiner points που μπαίνουν, το χρειαζόμαστε στο ex.cpp ώστε να τα τοποθετούμε στο output file
map<string, double> parameters_used; 

void create_map(){
    map_of_functions["Middle"]=point_to_middle;
    map_of_functions["Circumcenter"]=point_to_circumcenter;
    //map_of_functions["Centroid"]=point_to_centroid;
   // map_of_functions["Incenter"]=point_to_incenter;
    map_of_functions["Polygon"]=point_to_polyg;
    map_of_functions["Altitude"]=point_to_h;
}


void local_search(DATA2& data2, Custom_CDT& cdt) {
    DATA data;
    data.instance_uid=data2.instance_uid;
    data.num_points=data2.num_points;
    data.points_x=data2.points_x;
    data.points_y=data2.points_y;
    data.region_boundary=data2.region_boundary;
    data.num_constraints=data2.num_constraints;
    data.additional_constraints=data2.additional_constraints;

    Contrained_Delaunay(cdt, data);

    double alpha=data2.parameters["alpha"];
    double beta=data2.parameters["beta"];
    int L=data2.parameters["L"];
    parameters_used["alpha"]=alpha;
    parameters_used["beta"]=beta;
    parameters_used["L"]=L;
    int steiners=cdt.number_of_vertices();
    int iteration = 0;
    bool improved = true;
    double sum_pn=0.0;
    double pn, pn_old;
    int not_improved_for=0;
    bool helped=false;
    double randomization_sum_pn=0.0;
    while ( iteration < L ){


        if(not_improved_for>=50) {
            cout<<"\nΟ αλγόριθμος δεν συγκλίνει: Εκτέλεση τυχαιότητας"<<endl;
            randomization_sum_pn=randomization(cdt, data);
            break;
        }


        not_improved_for++;
        vector<pair<CDT::Face_handle, int>> obtuse_edges = check_for_obtuse(cdt);
        if (obtuse_edges.empty()){
           break;
        }
        function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)> best_method_function;
        int i=0;
        while(i<obtuse_edges.size() ){ //εξετάζουμε όλες τις αμβλείες
            string best_method_name=" ";

            const auto& trig=obtuse_edges[i];
            int min_obtuses = obtuse_edges.size();
            CDT::Face_handle face=trig.first;
            int i_of_face=trig.second;
            map<string, function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)>>::iterator it = map_of_functions.begin();
            helped=false;
            while (it != map_of_functions.end()){  //εξετάζουμε κάθε μια μέθοδο από το map_of_function για να βρούμε την καύτερη δυναρτή 
                function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)> chosen_func=it->second;
                Custom_CDT copy_cdt(cdt);  //αντιγράφουμε το cdt 
                Point steiner_copy=chosen_func(copy_cdt,face,data , i_of_face);  //βάζουμε steiner με την κάθε μεθοδο
                if(steiner_copy!=Point(-1.0,-1.0)){ //αν δεν είναι έγκυρο, δεν λαμ΄βανουμε υπόψιν την μέθοδο
                    int count_obtuses=check_for_obtuse(copy_cdt).size(); 
                    if(count_obtuses < min_obtuses){  //συγκρίνουμε τις αμβλείες 
                        min_obtuses = count_obtuses;
                        best_method_name=it->first;
                        best_method_function=chosen_func;
                        improved = true; 
                        not_improved_for=0;
                        helped=true;

                    }
                }  
                //η polygon δεν επιστρεφει valid sp
                ++it;

            }
            if(helped==true){  //Αφού έχουμε βρει την καλύτερη μέθοδο, με αυτήν βάζουμε steiner point 
                int obtuse_n=check_for_obtuse(cdt).size();
                Point steiner=best_method_function(cdt, face, data, i_of_face);
                if(steiner!=Point(-1.0 , -1.0)){
                    all_steiners_added.push_back(steiner);
                    int obt_next=check_for_obtuse(cdt).size();
                    if(obt_next==0) { 
                        obtuse_edges=check_for_obtuse(cdt);
                        break;
                    }

                    int n=all_steiners_added.size() -1;
                    if(n>1){
                        pn_old=pn;
                        pn= log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                        cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                        sum_pn+=pn;
                    }
                }
            }
            else{
                i++;
            }
        

            
            obtuse_edges = check_for_obtuse(cdt);
        }
        iteration ++;
        if(obtuse_edges.size()==0) break;

    }
    cout<<"iteration: "<<iteration<<" out of: "<<L<<endl;

    steiners=all_steiners_added.size();
    double p_avg=0;
   // cout<<"Randomization pn: "<<randomization_sum_pn<<endl;

    if(steiners>0) {
        p_avg=(sum_pn + randomization_sum_pn )/steiners;
    }
    if(p_avg>0){
        int obtuses_final=check_for_obtuse(cdt).size();
        double energy_final=alpha*obtuses_final+ beta*(all_steiners_added.size());
        cout<<"Ενέργεια τριγωνοποίσης που δεν συγκλίνει: "<<energy_final<<endl;
    }
    else{
        cout<<"Μέσος ρυθμός σύγκλισης: "<<p_avg<<endl;}
    cout<<"Method: Local search\n\tInserted: "<<steiners<<" Steiner points\nObtuse faces are now: "<<check_for_obtuse(cdt).size()<<"/"<<cdt.number_of_faces()<<endl;
}

void simulated_annealing(DATA2& data2, Custom_CDT& cdt){
    int steiners=0;
    DATA data;
    data.instance_uid=data2.instance_uid;
    data.num_points=data2.num_points;
    data.points_x=data2.points_x;
    data.points_y=data2.points_y;
    data.region_boundary=data2.region_boundary;
    data.num_constraints=data2.num_constraints;
    data.additional_constraints=data2.additional_constraints;
    Contrained_Delaunay(cdt, data);
    


    double alpha=data2.parameters["alpha"];
    double beta=data2.parameters["beta"];
    int L=data2.parameters["L"];
    parameters_used["alpha"]=alpha;
    parameters_used["beta"]=beta;
    parameters_used["L"]=L;
    int vertices_og=cdt.number_of_vertices();
    vector<pair<CDT::Face_handle, int>> obtuses=check_for_obtuse(cdt);  
    int number_of_obtuse=obtuses.size();  
    double energy=alpha*number_of_obtuse + beta*steiners;
    cout<<"Αρχική Ενέργεια: "<<energy<<endl;
    double T=1;
    parameters_used["T"]=T;

    int methodoi_size=map_of_functions.size();
    //cout<<methodoi_size<<endl;
    function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)> pinakas[methodoi_size];
    map<string, function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)>>::iterator it = map_of_functions.begin();
    int j=0;
    while (it != map_of_functions.end()){
        pinakas[j]=it->second;
        j++;
        ++it;

    }
    double sum_pn=0.0;
    double pn, pn_old;
    double randomization_sum_pn=0.0;
    int not_improved_for=0;
    bool helped=false;
    srand(time(0));

    while (T>=0 ){
        if(not_improved_for>=50){
            cout<<"\nΟ αλγόριθμος δεν συγκλίνει: Εκτέλεση τυχαιότητας"<<endl;
            randomization_sum_pn=randomization(cdt, data);
            break;
        }
        int i=0;
        int j=0;
        helped=false;
        while(j<obtuses.size() ){
            const auto& trig=obtuses[i];
            CDT::Face_handle face=trig.first;
            int i_of_face=trig.second;
            int random_i=rand()%(map_of_functions.size());
            function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)> random_func=pinakas[random_i];
            Custom_CDT copy_cdt(cdt);
            Point steiner=random_func(copy_cdt, face, data, i_of_face);
            if(steiner==Point(-1.0,-1.0)) {
               // cout<<"j= "<<j<<" not valid sp"<<endl;
                continue;}
            vector<pair<CDT::Face_handle, int>> obtuses_of_copy=check_for_obtuse(copy_cdt); 
            steiners=cdt.number_of_vertices()- vertices_og; 
            double new_energy=alpha*obtuses_of_copy.size() + beta*steiners;
            //cout<<"OBTUSES in copy: "<<obtuses_of_copy.size()<< " and energy new is: "<<new_energy<<endl;
            
            
            double de=new_energy-energy;
            if(de<0){   //αποδεχομαστε 
                int obtuse_n=check_for_obtuse(cdt).size();

                Point steiner=random_func(cdt, face, data, i_of_face);
                int obt_next=check_for_obtuse(cdt).size();
                if(steiner!=Point(-1.0, -1.0)){
                    all_steiners_added.push_back(steiner);
                
                    
                    if(obt_next==0) break;
                    int n=all_steiners_added.size() -1;
                    if(n>1){
                        pn_old=pn;
                        pn = log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                        cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                           // cout<<"ρυθμος¨"<<pn<<endl;
                        sum_pn+=pn;
                    }
                }
                if(obt_next<obtuse_n){
                    helped=true;
                }
  
            }
            else{    //αποδεχομαστε με πιθανοτητα
                double R = static_cast<double>(rand()) / static_cast<double>(RAND_MAX); // R ∈ [0, 1]
                if (exp(-de / T) >= R){
                    int obtuse_n=check_for_obtuse(cdt).size();

                    Point steiner=random_func(cdt, face, data, i_of_face);
                    int obt_next=check_for_obtuse(cdt).size();

                    if(steiner!=Point(-1.0, -1.0)){
                        all_steiners_added.push_back(steiner);
                    
                        if(obt_next==0) break;
                        int n=all_steiners_added.size() -1;
                        if(n>1){
                            pn_old=pn;
                             pn = log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                             cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                           
                            sum_pn+=pn;
                        }
                    }
                    if(obt_next<obtuse_n){
                        helped=true;
                    }
               }
               else{
              //  cout<<"δεν αποδεχομαστε λογω πιθανοτητασ"<<endl;
                    j++; //oxi apodoxh , αρα προχωραμε στο επομενο 
                    helped=false;
                }
               
            }
            if(helped==true){
                not_improved_for=0;
            }
            else{
                not_improved_for++;
            }
            obtuses=check_for_obtuse(cdt);
            if(not_improved_for>=50) break;

        }
        if(obtuses.size()==0) break;
        T=T-(1.0/(double)L);
    }
    steiners=all_steiners_added.size();
    double p_avg=0;
   // cout<<"Randomization pn: "<<randomization_sum_pn<<endl;

    if(steiners>0) {
        p_avg=(sum_pn + randomization_sum_pn)/steiners;
    }
    if(p_avg>0){
        int obtuses_final=check_for_obtuse(cdt).size();
        double energy_final=alpha*obtuses_final+ beta*(all_steiners_added.size());
        cout<<"Ενέργεια τριγωνοποίσης που δεν συγκλίνει: "<<energy_final<<endl;
    }
    else{
        cout<<"Μέσος ρυθμός σύγκλισης: "<<p_avg<<endl;}

    
    steiners=cdt.number_of_vertices() - vertices_og;
  //  cout<<"Method: Simulated Annealing: \n\tWe inserted "<<steiners<<" steiner points.\n\tObtuse faces are now: "<<check_for_obtuse(cdt).size()<<"/"<<cdt.number_of_faces()<<endl;

}



//Shared Memory vector στο οποίο κάθε μυρμήγκι κάνει log την εργασία του. Χρειάζεται και Mutex. 
vector<ant_eval> ant_logs;
pthread_mutex_t  logs_lock;



//Συνάρτηση η οποία επιστρέφει το μέτρο αξιολόηγης performance (καθαρά για πειραματικούς λόγους , αντί για energy)
/*double compute_performance(const ant_eval& st){
    double w1 = -1.0;   //steiner points added
    double w2 = 2.0;    //obtuses improved
    double w3 = 1.5;    //radius changed
    double w4 = 1.0;    //aspect ratio changed 

    double p = st.steiner_point_added *w1 + st.number_of_obtuses * w2 + st.radius_improvment*w3 + st.aspect_ratio_change*w4;
    return p;
}*/



//vector που υπολογ΄΄ιζει και επιστρέφει τα η κάθε μεθόδου από τους τύπος που μας δώθηκαν, paired με το όνομα της μεθόδου 
vector<pair<string ,double>> compute_htta(double r){
    vector<pair<string , double>> vec;
    vec.push_back(make_pair("middle", middle_probabiliy(r)));
    vec.push_back(make_pair("altitude", altitude_probabiliy(r)));
    vec.push_back(make_pair("circumcenter", circumcenter_probabiliy(r)));
    return vec;
}



//Συνάρτηση που υπολογίζει και επιστρέφει ένα vector στο οποίο περιέχεται η πιθανότητα να διαλεχτεί κάποια από τις μεθόδους (projection - circumcenter - middle)
vector<pair<string, double>> compute_p(vector<pair<string, double>> httas, vector<pair<string, double>> pher, double x, double y){
    vector<pair<string ,double>> vec;
    double sum = 0;
    for(int i=0; i<httas.size(); i++){
        sum+= (pow((pher[i].second),x)) *(pow((httas[i].second),y) ); 
    }
    for(int i=0; i<httas.size(); i++){
        double htta=httas[i].second;
        string name=httas[i].first;
        double ph=pher[i].second;

        double prob = (pow(ph,x) * pow(htta,y)) / sum;
        vec.push_back(make_pair(name, prob));
    }
    return vec;
}




//Function που διαλέγει τυχαία μια μέθοδο κάνοντας χρήση των πιθανοτήτων που έχουμε υπολογίσει. Στην συγκεκριμένη συνάρτση κάνουμε generate ένα τυχαίο αριθμό στο 
//διάστημα [0, sum of probabilities] και διαλέγει τη μέθοδο που αντιστοιχχεί σε αυτόν τον αριθμο. 
int select_method(const vector<pair<string, double>>& probabilities) {
    double total = 0.0;
    for (const auto& p : probabilities) {
        total += p.second;
    }
    thread_local mt19937 rng(random_device{}()); 
    uniform_real_distribution<double> dist(0.0, total);
    double r = dist(rng); 

    double cumulative = 0.0;
    for (size_t i = 0; i < probabilities.size(); ++i) {
        cumulative += probabilities[i].second;
        if (r <= cumulative) {
            return i; 
        }
    }
    return probabilities.size() - 1; //default (αν δεν έχει ήδη επιλεγεί κάποια μέθοδος -πράγμα σπάνιο)
}




//Η συνάρτηση που ξεκινάει κάθε thread (=ant) και είναι η δουλειά κάθε μυρμηγκιού. 
void* ant_work(void* inp){
    thr_inp* input=(thr_inp*)inp;  
    Custom_CDT copy_cdt(input->cdt);   //Αντίγραφοτ του cdt για να δουλέψουμε πάνω σε αυτό 
    DATA data=input->data;
    int i=input->i;
    vector<pair<string, double>> pherormones=input->pheror;
    vector<pair<CDT::Face_handle, int>> all_obtuse_faces=check_for_obtuse(copy_cdt); 
    int init_obtuses = all_obtuse_faces.size();    //Μαζεύουμε κάποια αρχικά δεδομένα για να συγκρίνουμε στο τέλος 
 //   double init_radius = compute_average_radius(copy_cdt);
    int init_vertices=copy_cdt.number_of_vertices();
 //   double init_aspect_ratio = compute_aspect_ratio_change(copy_cdt);
    double a=input->a;
    double b=input->b;
    double x=input->x;
    double y=input->y;
    double energy;
    string method;

    if (all_obtuse_faces.empty()) {
   //     cout << "No faces available in thread " << i << endl;
        return NULL;
    }

    // Δημιουργία τυχαίου αριθμού για την επιλογή face
    unsigned int seed = time(0) + i;   
    unsigned int thread_id = hash<thread::id>()(this_thread::get_id()); 
    mt19937 rng(seed ^ thread_id); 
    uniform_int_distribution<int> dist(0, all_obtuse_faces.size() - 1); 
    int random_index = dist(rng);
    //Επιλογή τυχαίου αμβλυγώνιου face 
    CDT::Face_handle face = all_obtuse_faces[random_index].first;
    int obtuse_index=all_obtuse_faces[random_index].second;

    ant_eval ant;
    if(face==nullptr || copy_cdt.is_infinite(face)) {
 //       cout<<"invalid face "<<endl;
        delete inp;
        return NULL;
    }
    ant.face=face;  // Κάνουμε log το face που θα δουλέψει το ant 
    for (int i = 0; i < 3; ++i) {
        ant.vertices.push_back(face->vertex(i)->point());   //λόγω προβλήμάτων του προέκυψαν με το Face_handle , κάνουμε log και όλα τα σημεία των vertices του face 
    }
    int obt_v=all_obtuse_faces[random_index].second;  
    double r=compute_r(face, obt_v);   //
    if(r==0.0) {
        delete inp;
        return NULL;
    }
    if(find_neigh(face)>=2){
       // cout<<"Face with id "<<random_index<<" has mre than 2 obtuse neighbors"<<endl;
        point_to_polyg(copy_cdt, face, data,0);
        method="Polygons";
    }
    else{
        vector<pair<string, double>> httas=compute_htta(r);
        vector<pair<string, double>> probabilities = compute_p(httas,pherormones, x,y);
            
        int selected_method = select_method(probabilities);

        // Χρησιμοποιήστε την επιλεγμένη μέθοδο
        if (probabilities[selected_method].first == "altitude") {
            point_to_h(copy_cdt,face,data, obtuse_index);
            method="Altitude";
        } else if (probabilities[selected_method].first == "circumcenter") {
            point_to_circumcenter(copy_cdt, face, data, 0);
            method="Circumcenter";

        } else if (probabilities[selected_method].first == "middle") {
            point_to_middle(copy_cdt, face, data, obtuse_index);
            method="Middle";

        }
    }
   // cout<<"Ant "<<i<<" chose method: "<<method<<"\n"<<endl;
    int steiners=copy_cdt.number_of_vertices() - init_vertices;
    int obtuses_after= check_for_obtuse(copy_cdt).size();
    int obtuses_fixed= init_obtuses - obtuses_after;
 
    ant.obtuse_index=obtuse_index;
    ant.ant_id = i;
    ant.method = method;
    ant.number_of_obtuses=obtuses_fixed;

    ant.steiner_point_added=steiners;
    ant.energy=a*(check_for_obtuse(copy_cdt).size()) + b*steiners;
    if(obtuses_fixed>=1) ant.helped=true;
    else ant.helped=false;


    pthread_mutex_lock(&logs_lock);
    ant_logs.push_back(ant);
    pthread_mutex_unlock(&logs_lock);

    delete inp;

    return NULL;
}





CDT::Face_handle find_face_by_vertices(Custom_CDT& cdt,const vector<Point>& vertices) {
    if (vertices.size() != 3) {
        throw invalid_argument("The input vector must contain exactly 3 vertices.");
    }
    for (auto face = cdt.all_faces_begin(); face != cdt.all_faces_end(); ++face) {
        vector<Point> face_vertices;
        for (int i = 0; i < 3; ++i) {
            face_vertices.push_back(face->vertex(i)->point());
        }
        sort(face_vertices.begin(), face_vertices.end());
        vector<Point> sorted_input = vertices;
        sort(sorted_input.begin(), sorted_input.end());
        if (face_vertices == sorted_input) {
            return face; 
        }
    }
    return CDT::Face_handle();
}

map<string, int> results_log;
double sum_pn_ants=0.0;

void create_results_map(){
    results_log["middle"]=0;
    results_log["altitude"]=0;
    results_log["polygon_centroid"]=0;
    results_log["circumcenter"]=0;

}

int not_improved_for_ants=0; //metavliti poy metraei poses synexomenes fores den voithane ta ants

//Στην συνάρτηση αυτή εξετάζουμε τα logs του κάθε μυρμηγκιού ώστε να βρούμε αυτό που έκανε την καλύτερη δουλειά
// δηλαδή αυτό που επέλεξε το βέλτιστο face και την βέλτιστη μέθοδο. Αρχικά, κάνουμε
//sort τα structs που υπάρχουν στο shared vector με βάση το performance (μεγαλύτερο performance, καλύτερη τριγωνοποίηση)
//Με αυτόν τον τρόπο, τα μυρμήγκια εξετάζονται με την σειρά από το "καλύτερο"
//στο "χειρότερο", και τα conflicts λύνονται πολύ πιο εύκολα. ΄
//Υστερα, μαζεύουμε τα μυρμήγκια που θα εξεταστούν και θα βοηθησουν στην τριγωνοποίηση.
//Επιλέξαμε να συνδυάζουμε τις δουλειές των μυρμηγκιών που δεν δημιουργούν conflicts, έτσι εισάγουμε steiner points σε διαφορετικά faces κάθε φορά.
void save_best_tring(Custom_CDT& cdt, vector<ant_eval> logs, DATA data ){
    sort(logs.begin(), logs.end(), [](const ant_evaluation& a, const ant_evaluation& b) {
        return a.energy < b.energy;  // Sort σε φθίνουσα σειρά
    });
   vector<ant_eval> ants_used;
   vector<CDT::Face_handle> faces;
   for(int i=0; i<logs.size(); i++){
        CDT::Face_handle f=find_face_by_vertices(cdt,logs[i].vertices);
        if(f!=nullptr && f!=CDT::Face_handle()){
            logs[i].face=f;
            ants_used.push_back(logs[i]);
    
          //  cout<<"Will be using ant: "<<logs[i].ant_id<<" with face of [("<<logs[i].face->vertex(0)->point().x()<<","
           // <<logs[i].face->vertex(0)->point().y()<<") , ("<<logs[i].face->vertex(1)->point().x()<<","<<logs[i].face->vertex(1)->point().y()<<"),("<<logs[i].face->vertex(2)->point().x()<<","<<logs[i].face->vertex(2)->point().y()<<")]"<<endl;
        }
        
   }
    sort(ants_used.begin(), ants_used.end(), [](const ant_evaluation& a, const ant_evaluation& b) {
        return a.energy < b.energy;  // Sort σε φθίνουσα σειρά
    });
    
    
    double pn, pn_old;
    int k=0;
    int counter_pn=0;
    int obtuses_before=check_for_obtuse(cdt).size();
    for(const auto& item: ants_used){
        if(item.steiner_point_added==0) continue;
        if(item.face==nullptr || cdt.is_infinite(item.face) ){
            continue;
        }
        string method=item.method;
        int vert_before=cdt.number_of_vertices();
        int vert_after;
        int steiners;
       // if(item.helped==false) continue;
 //       if(method!="Altitude") continue;   //ΕΔΩ ΘΑ ΕΞΑΙΡΟΥΜΕ ΜΕΘΟΔΟΥΣ
        if(method=="Middle"){

            int obtuse_n=check_for_obtuse(cdt).size();
            Point the_steiner=point_to_middle(cdt, item.face, data, item.obtuse_index);
            if(the_steiner!=Point(-1.0, -1.0)){
                    all_steiners_added.push_back(the_steiner);
                    
                    int obt_next=check_for_obtuse(cdt).size();
                    if(obt_next==0) break;
                    int n=all_steiners_added.size() -1;
                    if(n>1){
                        pn_old=pn;
                        pn = log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                        cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                       
                        
                        sum_pn_ants+=pn;
                    }
            }
            vert_after=cdt.number_of_vertices();
            steiners=vert_after - vert_before;
            if(steiners!=0) results_log["middle"]++;
        }
        else if(method=="Altitude"){
            int obtuse_n=check_for_obtuse(cdt).size();
            Point the_steiner=point_to_h(cdt, item.face, data, item.obtuse_index);
            if(the_steiner!=Point(-1.0, -1.0)){
                    all_steiners_added.push_back(the_steiner);
                    
                    int obt_next=check_for_obtuse(cdt).size();
                    if(obt_next==0) break;

                    int n=all_steiners_added.size() -1;
                    if(n>1){
                        pn_old=pn;
                        pn = log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                        cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                        
                        
                        sum_pn_ants+=pn;
                    }
            }
            vert_after=cdt.number_of_vertices();
            steiners=vert_after - vert_before;
            if(steiners!=0) results_log["altitude"]++;
        }
        else if(method=="Circumcenter"){
            int obtuse_n=check_for_obtuse(cdt).size();
            Point the_steiner=point_to_circumcenter(cdt, item.face, data,0);
            if(the_steiner!=Point(-1.0, -1.0)){
                    all_steiners_added.push_back(the_steiner);
                    
                    int obt_next=check_for_obtuse(cdt).size();
                    if(obt_next==0) break;

                    int n=all_steiners_added.size() -1;
                    if(n>1){
                        pn_old=pn;
                        pn = log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                        cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                       
                        
                        sum_pn_ants+=pn;
                    }
            }
            vert_after=cdt.number_of_vertices();
            steiners=vert_after - vert_before;
            if(steiners!=0) results_log["circumcenter"]++;
        }
        else if(method=="Polygons"){
            int obtuse_n=check_for_obtuse(cdt).size();
            Point the_steiner=point_to_polyg(cdt, item.face, data,0);
            if(the_steiner!=Point(-1.0, -1.0)){
                    all_steiners_added.push_back(the_steiner);
                    
                    int obt_next=check_for_obtuse(cdt).size();
                    if(obt_next==0) break;

                    int n=all_steiners_added.size() -1;
                    if(n>1){
                        pn_old=pn;
                        pn = log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                        cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                       
                        sum_pn_ants+=pn;
                    }
            }
            vert_after=cdt.number_of_vertices();
            steiners=vert_after - vert_before;
            if(steiners!=0) results_log["polygon_centroid"]++;
        }

        k++;
        if(k==1) break;   //μονο το πρωτο steinner 

    }
    int obtuses_after=check_for_obtuse(cdt).size();
    if(obtuses_before<=obtuses_after){
        not_improved_for_ants++;
     //   cout<<"Not improved for: "<<not_improved_for_ants<<endl;

    }
    else{
        not_improved_for_ants=0;
    }





    return;
}


void update_pherormones(vector<pair<string, double>> &pherormones, double a, double b, int steiners, int obtuses, double lambda){
    int i=0;
    for(const auto& item: pherormones){
        string method=item.first;
        int factor=0;
        for(const auto& ant: ant_logs){
            if(ant.method==method && ant.helped==true){
                factor=1/(a*steiners + b*obtuses);
                cout<<"method "<<method<<" helped so we are updating with: "<<factor<<endl;
                break;
            }
        }
        pherormones[i].second= (1.0 - lambda)*pherormones[i].second + factor;
        i++;
        
    }
}







void ant_colony(DATA2& data2, Custom_CDT& cdt){
    DATA data;
    data.instance_uid=data2.instance_uid;
    data.num_points=data2.num_points;
    data.points_x=data2.points_x;
    data.points_y=data2.points_y;
    data.region_boundary=data2.region_boundary;
    data.num_constraints=data2.num_constraints;
    data.additional_constraints=data2.additional_constraints;
  //  for(int i=0; i<data.points_x.size(); i++){
    //    cout<<data.points_x[i]<<","<<data.points_y[i]<<endl;
    //}
    double alpha=data2.parameters["alpha"];
    parameters_used["alpha"]=alpha;
    double beta=data2.parameters["beta"];
    parameters_used["beta"]=beta;
    double L=data2.parameters["L"];
    parameters_used["L"]=L;
    double K=data2.parameters["kappa"];
    parameters_used["kappa"]=K;
    double lambda=data2.parameters["lambda"];
    parameters_used["lambda"]=lambda;
    double x=data2.parameters["xi"];
    parameters_used["xi"]=x;
    double y=data2.parameters["psi"];
    parameters_used["psi"]=y;
 //   cout<<"L is: "<<L<<" K is: "<<K<<" x is: "<<x<<" y is: "<<y<<endl;

    Contrained_Delaunay(cdt, data);
   
    
    int vert_before=cdt.number_of_vertices();
    int face_before=cdt.number_of_faces();
    int obtuses_before=check_for_obtuse(cdt).size();
//    cout<<"Vertices: "<<vert_before<<" faces: "<<face_before<<" obtuses: "<<obtuses_before<<endl;
    vector<pair<CDT::Face_handle, int>> obtuses=check_for_obtuse(cdt); 

  
   create_results_map();
    double randomization_sum_pn=0.0;
    pthread_mutex_init(&logs_lock, NULL);
    vector<pair<string, double>> pherormones;
    pherormones.push_back(make_pair("middle", 1.0));
    pherormones.push_back(make_pair("altitude", 1.0));
    pherormones.push_back(make_pair("circumcenter", 1.0));
    for(int cycle =1 ; cycle < L; cycle ++){
        if(not_improved_for_ants>=50){
            cout<<"\nΟ αλγόριθμος δεν συγκλίνει: Εκτέλεση τυχαιότητας"<<endl;
            randomization_sum_pn=randomization(cdt, data);
            break;
        }
        //cout<<"\n\nCycle: "<<cycle<<endl;
        //cout<<"verteces: "<<cdt.number_of_vertices()<<" and faces: "<<cdt.number_of_faces()<<endl;
       int steiners=cdt.number_of_vertices();
        pthread_t thread_pool[(int)K];


        for (int i = 0; i < K; i++) {
            thr_inp* inp = new thr_inp();  // Δυναμική δέσμευση
            inp->cdt = cdt;
            inp->i = i;
            inp->data=data;
            inp->pheror=pherormones;
            inp->a=alpha;
            inp->b=beta;
            inp->x=x;
            inp->y=y;

            pthread_create(&thread_pool[i], nullptr, ant_work, (void*)inp);
        }

        for (int i = 0; i < K; i++) {
            pthread_join(thread_pool[i], nullptr);
        }

        //save best triangulation
        save_best_tring(cdt, ant_logs, data);
        steiners=cdt.number_of_vertices()-steiners;
        int obtuses=check_for_obtuse(cdt).size();
        update_pherormones(pherormones, alpha, beta,steiners, obtuses, lambda  );
        if(obtuses==0) break;
        ant_logs.clear();
    }
    pthread_mutex_destroy(&logs_lock);
    int steiners=all_steiners_added.size();
    double p_avg=0;
  //  cout<<"Randomization pn: "<<randomization_sum_pn<<endl;
    if(steiners>0) {
        p_avg=(sum_pn_ants + randomization_sum_pn)/steiners;
    }
    if(p_avg>0){
        int obtuses_final=check_for_obtuse(cdt).size();
        double energy_final=alpha*obtuses_final+ beta*(all_steiners_added.size());
        cout<<"Ενέργεια τριγωνοποίσης που δεν συγκλίνει: "<<energy_final<<endl;
    }
    else{
        cout<<"Μέσος ρυθμός σύγκλισης: "<<p_avg<<endl;}
    
    cout<<"Method: Ant Colony: \n"<<"\tOriginal CDT had: "<<obtuses_before<<"/"<<face_before<<" obtuse faces\n"<<"\tWe inserted "<<steiners<<" steiner points:\n"<<
    "\t\tMiddle of largest edge: "<<results_log["middle"]<<"\n\t\tCircumcenter: "<<results_log["circumcenter"]<<"\n\t\tProjection: "<<results_log["altitude"]<<
    "\n\t\tPolygon Cnetroid: "<<results_log["polygon_centroid"]<<"\nFinal obtuse faces: "<<check_for_obtuse(cdt).size()<<"/"<<cdt.number_of_faces()<<endl;
    return;
}





double compute_r(CDT::Face_handle face, int v) {
    // Πάρε τις συντεταγμένες των κορυφών του τριγώνου
    Point v1 = face->vertex((v + 1) % 3)->point();
    Point v2 = face->vertex(v)->point();
    Point v3 = face->vertex((v + 2) % 3)->point();

    // Υπολόγισε τις αποστάσεις (χωρίς sqrt, παραμένουμε σε RT)
    RT a2 = CGAL::squared_distance(v2, v3);
    RT b2 = CGAL::squared_distance(v1, v3);
    RT c2 = CGAL::squared_distance(v1, v2);

    // Υπολόγισε το εμβαδόν του τριγώνου με RT
    RT area2 = 
        CGAL::square(v1.x() * (v2.y() - v3.y()) +
                     v2.x() * (v3.y() - v1.y()) +
                     v3.x() * (v1.y() - v2.y())) / RT(4);

    // Έλεγξε αν το τρίγωνο έχει μηδενικό εμβαδόν
    if (area2 == RT(0)) {
        return 0.0;
    }

    // Υπολόγισε το τετράγωνο της ακτίνας του περιγεγραμμένου κύκλου
    RT abc2 = a2 * b2 * c2;
    RT R2 = abc2 / (16 * area2);

    // Βρες το ύψος (h) και υπολόγισε την απόσταση
    Point h = find_height_intersection(v1, v2, v3);
    RT height2 = CGAL::squared_distance(v2, h);

    // Αν το ύψος είναι μηδενικό, επέστρεψε 0
    if (height2 == RT(0)) {
        return 0.0;
    }

    // Υπολόγισε το r = R / height χωρίς να χρησιμοποιείς sqrt
    RT r2 = R2 / height2;

    // Επιστροφή του αποτελέσματος
    return CGAL::sqrt(CGAL::to_double(r2));
}




double middle_probabiliy(double R){
    return max(0.0,(3.0-2.0*R)/3.0);
}

double altitude_probabiliy(double R){
    return max(0.0,(R-1)/R);
}

double circumcenter_probabiliy(double R){
    return R/(2+R);
}


int find_neigh(CDT::Face_handle face){
    int count = 0;
    for(int i=0; i<3; i++){
        CDT::Face_handle neighbor=face->neighbor(i);
        if(!check_obtuse_triangle(neighbor)) continue;
        if(has_constraints(neighbor)) continue;
        count ++ ;
    }
    return count;
}





double randomization(Custom_CDT& cdt, DATA& data){
    vector<pair<CDT::Face_handle , int>> obtuses=check_for_obtuse(cdt);
    int i=0;
    double sigma=0.5;
    int not_improved_for=0;
    double sum_pn=0.0;
    double pn_old , pn=0.0;
    while(i < obtuses.size()){
        if(not_improved_for >= 30){
            cout<<"\nΗ μέθοδος της τυχαιοποίησης δεν συγκλίνει. Σταματάει η διαδικασία"<<endl;
            break;}
        CDT::Face_handle face=obtuses[i].first;
        int index=obtuses[i].second;
        int obtuses_before=obtuses.size();
        Point p0=(face->vertex(0))->point();
        Point p1=(face->vertex(1))->point();
        Point p2=(face->vertex(2))->point();
        Point incenter=compute_incenter(face);
        Point steiner;
        do{
            Point steiner=gaussian_p(incenter, 0.5);
    

        }while( !is_point_inside_triangle(steiner, p0,p1,p2)&&steiner==Point(-1.0, -1.0) && !is_valid_steiner_point(cdt, face, steiner, data)  );
       
        int obtuse_before=obtuses.size();
        CDT::Vertex_handle vh = cdt.insert_no_flip(steiner);
        if(steiner!=Point(-1.0 , -1.0)){
            all_steiners_added.push_back(steiner);
            int obt_next=check_for_obtuse(cdt).size();
            if(obt_next==0) { 
                obtuses=check_for_obtuse(cdt);
                break;
            }

            int n=all_steiners_added.size() -1;
            if(n>1){
                pn_old=pn;
                pn= log(static_cast<double>(obt_next) / obtuse_before) / (log(static_cast<double>(n + 1) / (n)));
                cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                sum_pn+=pn;
            }
        }
        obtuses=check_for_obtuse(cdt);
        int obtuses_after=obtuses.size();
        if(obtuses_after < obtuses_before) {
            not_improved_for=0;
            i=0;
        }else{
            not_improved_for++;
            i++;
        }
       


    }
    return sum_pn;
}