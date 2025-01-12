#include "utils/utils.hpp"

int main(int argc , char* argv[]){
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
    if(data2.delaunay){

        Contrained_Delaunay(cdt_check, data);
    }

    checking(cdt_check, data2);
    CGAL::draw(cdt_check);
    return 0;
}

