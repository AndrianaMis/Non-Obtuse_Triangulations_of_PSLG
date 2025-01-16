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
    int obtuses_initial=check_for_obtuse(cdt_check).size();

   double initial_energy= data2.parameters["alpha"] * obtuses_initial ;
  //CGAL::draw(cdt_check);

    int cat= analyze_boundary(data2);
    if(cat==1){
        ant_colony(data2, cdt);
    }
    else if(cat==2){
        ant_colony(data2, cdt);
    }
    else if(cat==3){
        ant_colony(data2, cdt);
    }
    else if(cat==4){
        ant_colony(data2, cdt);

    }
    else{
        local_search(data2, cdt);
    }
   //hecking(cdt_check, data2);
   int vert_before=cdt_check.number_of_vertices();
    //we must also extract the parameters needed for each method
    /*if(data2.method=="sa"){
        simulated_annealing(data2, cdt);
    }
    else if(data2.method=="local_search" || data2.method=="local" ||data2.method=="ls"){
        local_search(data2, cdt);
    }
    else{
       ant_colony(data2, cdt);
     //   checking(data2, cdt);
    }*/
  //  CGAL::draw(cdt_check);
  int obtuses_final=check_for_obtuse(cdt).size();
  int vert_after=cdt.number_of_vertices();
   steiners= vert_after-vert_before;
    cout<<"Αρχικές αμβλείες: "<<obtuses_initial<<endl;
   cout<<"Τελικές αμβλείες: "<<obtuses_final<<endl;

   cout<<"\nΑρχικά faces: "<<cdt_check.number_of_faces()<<endl;
   cout<<"Τελικές faces: "<<cdt.number_of_faces()<<endl;

   cout<<"\nΑρχική ενέργεια: "<<initial_energy<<endl;
    double final_energy=(data2.parameters["alpha"] * obtuses_final )+ (data2.parameters["beta"] * steiners);
    cout<<"Τελική ενέργεια: "<<final_energy<<endl;
    double per = (static_cast<double>(obtuses_initial) - static_cast<double>(obtuses_final)) / static_cast<double>(obtuses_initial) * 100;
   
    cout<<endl;
    if(per>=0) cout<<per<<"%"<<" μείωση αμβλείων"<<endl;
    else cout<<per<<"%"<< " αύξηση αμβλείων"<<endl;
  //  double metric=(data2.parameters["alpha"])*(obtuses_initial - obtuses_final)/(cdt.number_of_faces() - cdt_check.number_of_faces() + (data2.parameters["beta"] * steiners) );
  //  CGAL::draw(cdt);
  // cout<<"Metric: "<<metric<<endl;
    extract_to_output2(all_steiners_added, cdt,input_file,output_file,check_for_obtuse(cdt).size(), parameters_used,  data2.method  );
    return 0;
}

