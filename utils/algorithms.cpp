
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
    int counter_pn=0;
    bool energy_counting=false;
    bool not_improved_for=0;
    while (improved && iteration < L && energy_counting==false ){

        if(not_improved_for>=15) improved=false;
        not_improved_for++;
        vector<pair<CDT::Face_handle, int>> obtuse_edges = check_for_obtuse(cdt);
        if (obtuse_edges.empty()){
           break;
        }
        function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)> best_method_function;
        int i=0;
        while(i<obtuse_edges.size() && energy_counting==false ){ //εξετάζουμε όλες τις αμβλείες
            string best_method_name=" ";

            const auto& trig=obtuse_edges[i];
            int min_obtuses = obtuse_edges.size();
            CDT::Face_handle face=trig.first;
            int i_of_face=trig.second;
            map<string, function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)>>::iterator it = map_of_functions.begin();
            int j=0;
            while (it != map_of_functions.end()){  //εξετάζουμε κάθε μια μέθοδο από το map_of_function για να βρούμε την καύτερη δυναρτή 
                function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)> chosen_func=it->second;
                Custom_CDT copy_cdt(cdt);  //αντιγράφουμε το cdt 
                Point steiner_copy=chosen_func(copy_cdt,face,data , i_of_face);  //βάζουμε steiner με την κάθε μεθοδο
                if(steiner_copy!=Point(-1.0,-1.0)){ //αν δεν είναι έγκυρο, δεν λαμ΄βανουμε υπόψιν την μέθοδο
                    int count_obtuses=check_for_obtuse(copy_cdt).size(); 
                    if(count_obtuses <= min_obtuses){  //συγκρίνουμε τις αμβλείες 
                        min_obtuses = count_obtuses;
                        best_method_name=it->first;
                    //   printf("%s\n", it->first);
                        best_method_function=chosen_func;
                        improved = true; 
                        not_improved_for=0;
                    }
                }  
                j++;
                ++it;

            }
            if(best_method_name!= " "){  //Αφού έχουμε βρει την καλύτερη μέθοδο, με αυτήν βάζουμε steiner point 
                int obtuse_n=check_for_obtuse(cdt).size();
                Point steiner=best_method_function(cdt, face, data, i_of_face);
                if(steiner!=Point(-1.0 , -1.0)){
                    all_steiners_added.push_back(steiner);
                    int obt_next=check_for_obtuse(cdt).size();
                    int n=all_steiners_added.size() -1;
                    if(n>1){
                        pn_old=pn;
                        pn= log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                        cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                        if(pn>pn_old){
                            counter_pn++;
                           // cout<<counter_pn<<endl;
                            if(counter_pn==15){
                                energy_counting=true;
                            }
                           
                        }
                        else{
                            counter_pn=0;
                        }
                     
                        sum_pn+=pn;
                    }
               
                }

            }

            i++;
            obtuse_edges = check_for_obtuse(cdt);
        }
        iteration ++;
        cout<<"iteration: "<<iteration<<" out of: "<<L<<endl;
        if(improved==false && not_improved_for>=15) cout<<"Stopping cause triangulation was not improved"<<endl;
    }
    steiners=cdt.number_of_vertices() - steiners;  
    if(energy_counting==false) {
        double p_avg=sum_pn/all_steiners_added.size();
        cout<<"Μέσος ρυθμός σύγκλισης: "<<p_avg<<endl;
    }
    else{
        int obtuses=check_for_obtuse(cdt).size();
        double energy=alpha*obtuses + beta*(all_steiners_added.size());
        cout<<"Ενέργεια τριγωνοποίσης που δεν συγκλίνει: "<<energy<<endl;
    }
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
    int counter_pn=0;
    bool energy_counting=false;
    while (T>=0 && energy_counting==false){
        srand(time(0));
        int i=0;
        int j=0;
        while(obtuses.size()>0 && j<=number_of_obtuse && energy_counting==false){
            const auto& trig=obtuses[i];
            CDT::Face_handle face=trig.first;
            int i_of_face=trig.second;
            int random_i=rand()%(map_of_functions.size());
            function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)> random_func=pinakas[random_i];
            Custom_CDT copy_cdt(cdt);
            random_func(copy_cdt, face, data, i_of_face);
            
            vector<pair<CDT::Face_handle, int>> obtuses_of_copy=check_for_obtuse(copy_cdt); 
            steiners=cdt.number_of_vertices()- vertices_og; 
            double new_energy=alpha*obtuses_of_copy.size() + beta*steiners;
            //cout<<"OBTUSES in copy: "<<obtuses_of_copy.size()<< " and energy new is: "<<new_energy<<endl;
            
            
            double de=new_energy-energy;
            if(de<0){
                int obtuse_n=check_for_obtuse(cdt).size();

                Point steiner=random_func(cdt, face, data, i_of_face);
                if(steiner!=Point(-1.0, -1.0)){
                    all_steiners_added.push_back(steiner);
                
                    int obt_next=check_for_obtuse(cdt).size();
                    int n=all_steiners_added.size() -1;
                    if(n>1){
                        pn_old=pn;
                        pn = log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                        cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                        if(pn>pn_old){
                            counter_pn++;
                            if(counter_pn==8){
                                energy_counting=true;
                            }
                             
                        }
                        else{
                            counter_pn=0;
                        }
                           // cout<<"ρυθμος¨"<<pn<<endl;
                        sum_pn+=pn;
                    }
                }
  
            }
            else{
                double pr=exp((-de/T));
                if (rand()/RAND_MAX < pr){
                    int obtuse_n=check_for_obtuse(cdt).size();

                    Point steiner=random_func(cdt, face, data, i_of_face);
                    if(steiner!=Point(-1.0, -1.0)){
                        all_steiners_added.push_back(steiner);
                    
                        int obt_next=check_for_obtuse(cdt).size();
                        int n=all_steiners_added.size() -1;
                        if(n>1){
                            pn_old=pn;
                             pn = log(static_cast<double>(obt_next) / obtuse_n) / (log(static_cast<double>(n + 1) / (n)));
                             cout<<"pn:"<<pn<<" obtuses:"<<obt_next<<" steiners:"<<n+1<<endl;
                            if(pn>pn_old){
                                counter_pn++;
                                if(counter_pn==6){
                                    energy_counting=true;
                                }
                             
                             }
                            else{
                                counter_pn=0;
                            }
                           
                            sum_pn+=pn;
                        }
                    }
               }
               
            }

            
            vector<pair<CDT::Face_handle, int>> new_obtuses=check_for_obtuse(cdt);
            if(new_obtuses==obtuses){
                i++;
            }
            else{ 
                i=0;
            }
            if(j==(number_of_obtuse/2)){
                i=new_obtuses.size()/2;
            }
            obtuses=new_obtuses;
            j++;

        }
        T=T-(1.0/(double)L);
    }
    if(energy_counting==false){
        double p_avg=sum_pn/all_steiners_added.size();
        cout<<"Μέσος ρυθμός σύγκλισης: "<<p_avg<<endl;
    }
    else{
        int obtuses_final=check_for_obtuse(cdt).size();
        double energy_final=alpha*obtuses_final+ beta*(all_steiners_added.size());
        cout<<"Ενέργεια τριγωνοποίσης που δεν συγκλίνει: "<<energy_final<<endl;
    }
    steiners=cdt.number_of_vertices() - vertices_og;
  //  cout<<"Method: Simulated Annealing: \n\tWe inserted "<<steiners<<" steiner points.\n\tObtuse faces are now: "<<check_for_obtuse(cdt).size()<<"/"<<cdt.number_of_faces()<<endl;

}
