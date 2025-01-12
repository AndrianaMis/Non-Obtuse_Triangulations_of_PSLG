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


void analyze_boundary(DATA2& data2){
    vector<Point> boundary_polyg;
    for(int j=0; j<data2.region_boundary.size(); j++){
        boundary_polyg.push_back(Point(data2.points_x[data2.region_boundary[j]],data2.points_y[data2.region_boundary[j]]) );
    //    cout<<data2.points_x[data2.region_boundary[j]]<<","<<data2.points_y[data2.region_boundary[j]] <<endl;
        
    }
    if(CGAL::is_convex_2(boundary_polyg.begin(), boundary_polyg.end())){
        if(data2.additional_constraints.size()==0) cout<<"Α. ΚΥΡΤΟ ΠΕΡΙΒΛΗΜΑ ΧΩΡΙΣ ΠΕΡΙΟΡΙΣΜΟΥΣ"<<endl;
        else if(closed(data2.additional_constraints)) cout<<"Γ. ΚΥΡΤΟ ΠΕΡΙΒΛΗΜΑ (ΚΛΕΙΣΤΟ)"<<endl;
        else cout<<"Β. ΚΥΡΤΟ ΠΕΡΙΒΛΗΜΑ (ΑΝΟΙΧΤΟ)"<<endl;

    }
    else if(is_axis_aligned(data2.region_boundary, data2.points_x, data2.points_y)){
        if(data2.num_constraints==0) cout<<"Δ. Μη κυρτό boundary με ευθύγραμμα τμήματα παράλληλα στους άξονες χωρίςm περιορισμούς."<<endl;
    }
    else cout<<"Ε. Μη κυρτό boundary, ακανόνιστο, που δεν εντάσσεται στις κατηγορίες Α-Δ. "<<endl;
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
