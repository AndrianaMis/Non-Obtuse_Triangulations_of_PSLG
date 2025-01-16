#include "utils.hpp"

#include <unordered_set>
#include <unordered_map>

using namespace std;

bool dfs(int node, int parent, vector<vector<int>>& adj, bool* visited) {
    visited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, node, adj, visited)) {
                return true; // Cycle found
            }
        } else if (neighbor != parent) {
            return true; // Back edge detected
        }
    }

    return false;
}

// Function to check if there's a cycle in the graph
bool hasCycle(int numNodes, vector<vector<int>>& edges) {
    /*// Create adjacency list
    vector<vector<int>> adj(numNodes*2);
    cout<<numNodes<<endl;
    for (const auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]); // Since the graph is undirected
    }
    bool visited[numNodes];
    for(int i=0; i<numNodes; i++){
        visited[i]=false;
    }
    // Check for cycles in all connected components
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1, adj, visited)) {
                return true;
            }
        }
    }*/

    for(int i=0; i<numNodes; i++){
        if((edges[i])[0] >= (edges[i])[1]) return true;
    }

    return false;
}
bool closed(vector<vector<int>> cons){
    if(hasCycle(cons.size(),cons)){
        return true;
    }
    
    return false;
}

bool is_axis_aligned(const vector<int>& boundary_vert, const vector<int>& points_x, const vector<int>& points_y) {
    for (size_t i = 0; i < boundary_vert.size(); i++) {
        int curr = boundary_vert[i];
        int next = boundary_vert[(i + 1) % boundary_vert.size()];
        int x1 = points_x[curr], y1 = points_y[curr];
        int x2 = points_x[next], y2 = points_y[next];

        if (!(x1 == x2 || y1 == y2)) {
            return false; // Βρέθηκε ακμή που δεν είναι παράλληλη στους άξονες
        }
    }
    return true; 
}


int analyze_boundary(DATA2& data2){
    vector<Point> boundary_polyg;
    for(int j=0; j<data2.region_boundary.size(); j++){
        boundary_polyg.push_back(Point(data2.points_x[data2.region_boundary[j]],data2.points_y[data2.region_boundary[j]]) );
    //    cout<<data2.points_x[data2.region_boundary[j]]<<","<<data2.points_y[data2.region_boundary[j]] <<endl;
        
    }
    if(CGAL::is_convex_2(boundary_polyg.begin(), boundary_polyg.end())){
        if(data2.additional_constraints.size()==0) {
            cout<<"Α. ΚΥΡΤΟ ΠΕΡΙΒΛΗΜΑ ΧΩΡΙΣ ΠΕΡΙΟΡΙΣΜΟΥΣ"<<endl;
            return 1;
        }
        else if(closed(data2.additional_constraints)) {
            cout<<"Γ. ΚΥΡΤΟ ΠΕΡΙΒΛΗΜΑ (ΚΛΕΙΣΤΟ)"<<endl;
            return 3;
        }
        else{

         cout<<"Β. ΚΥΡΤΟ ΠΕΡΙΒΛΗΜΑ (ΑΝΟΙΧΤΟ)"<<endl;
         return 2;
        }

    }
    else if(is_axis_aligned(data2.region_boundary, data2.points_x, data2.points_y)){
        if(data2.num_constraints==0) {
            cout<<"Δ. Μη κυρτό boundary με ευθύγραμμα τμήματα παράλληλα στους άξονες χωρίςm περιορισμούς."<<endl;
            return 4;
        }
    }
    else {
        cout<<"Ε. Μη κυρτό boundary, ακανόνιστο, που δεν εντάσσεται στις κατηγορίες Α-Δ. "<<endl;
        return 5;
    }
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
   while(obtuses.size()>1 && i<1 ){
        Point steiner=point_to_polyg(cdt, obtuses[j].first, data, obtuses[j].second);
        if(steiner!=Point(-1.0,-1.0)){
            cout<<"βαλαμε με προτζεκτιον και έχουμε από "<<obtuses.size()<<" -> "<<check_for_obtuse(cdt).size()<<endl;
            i++;
        }
    
        obtuses=check_for_obtuse(cdt);

        j=rand()%obtuses.size();
        
        
   }
}



RT edge_length(Point &p1, Point& p2){
    return  CGAL::sqrt(CGAL::to_double(CGAL::squared_distance(p1, p2)));
}

bool is_point_inside_triangle(const Point& p, const Point& v1, const Point& v2, const Point& v3) {
    vector<Point> points={v1,v2,v3};
    CGAL::Bounded_side side =  CGAL::bounded_side_2(points.begin(), points.end(), p, K());
    return side == CGAL::ON_BOUNDED_SIDE;
}



Point compute_incenter(CDT::Face_handle face) {
    CDT::Vertex_handle v1=face->vertex(1);
    CDT::Vertex_handle v0=face->vertex(0);
    CDT::Vertex_handle v2=face->vertex(2);
    Point p1=v1->point();
    Point p0=v0->point();
    Point p2=v2->point();
    RT a=edge_length(p1, p2);
    RT b=edge_length(p0, p2);
    RT c=edge_length(p0, p1);
    if((a+b+c)==0) return Point(-1.0, -1.0);
    RT x=(a*p0.x() + b*p1.x() + c*p2.x() ) / (a+b+c);
    RT y=(a*p0.y() + b*p1.y() + c*p2.y() ) / (a+b+c);
    Point incenter(x,y);
   
  //  cout<<"incenter"<<incenter<<endl;
    return incenter;
}

Point gaussian_p(const Point& incenter, double sigma){
    random_device rd;
   mt19937 gen(rd());
   normal_distribution<> d_x(CGAL::to_double(incenter.x()), sigma);
   normal_distribution<> d_y(CGAL::to_double(incenter.y()), sigma);
    return Point(d_x(gen), d_y(gen));
}


