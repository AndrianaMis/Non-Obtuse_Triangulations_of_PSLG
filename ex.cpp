#include "utils/utils.hpp"

int main(int argc , char* argv[]){
    create_map();
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-i" && i + 1 < argc) {
            input_file = argv[++i]; 
        } else if (arg == "-o" && i + 1 < argc) {
            output_file = argv[++i]; 
        } else {
            cerr << "Unknown argument: " << arg << endl;
            return 1; 
        }
    }
    cout << "Input file: " << input_file << endl;
    cout << "Output file: " << output_file << endl;

    DATA2 data2;
    int status2 =READ_DATA2(data2);
    Custom_CDT cdt;
    Custom_CDT cdt_check;
    int steiners = 0;
    DATA data;
    data.instance_uid=data2.instance_uid;
    data.num_points=data2.num_points;
    data.points_x=data2.points_x;
    data.points_y=data2.points_y;
    data.region_boundary=data2.region_boundary;
    data.num_constraints=data2.num_constraints;
    data.additional_constraints=data2.additional_constraints;

    Contrained_Delaunay(cdt_check, data);
    
   cout<<"Αρχικές αμβλείες: "<<check_for_obtuse(cdt_check).size()<<endl;
   cout<<"Αρχικά faces: "<<cdt_check.number_of_faces()<<endl;
  //CGAL::draw(cdt_check);

   analyze_boundary(data2);
   //hecking(cdt_check, data2);
   
    //we must also extract the parameters needed for each method
    if(data2.method=="sa"){
        simulated_annealing(data2, cdt);
    }
    else if(data2.method=="local_search" || data2.method=="local" ||data2.method=="ls"){
        local_search(data2, cdt);
    }
    else{
       ant_colony(data2, cdt);
     //   checking(data2, cdt);
    }
  //  CGAL::draw(cdt);
   cout<<"Τελικές αμβλείες: "<<check_for_obtuse(cdt).size()<<endl;
   cout<<"Τελικές faces: "<<cdt.number_of_faces()<<endl;

    CGAL::draw(cdt);
    return 0;
}