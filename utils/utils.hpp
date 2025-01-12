#ifndef UTILS_HPP
#define UTILS_HPP

#include <exception>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <vector>
#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/draw_surface_mesh.h>
#include<CGAL/draw_triangulation_2.h>

#include <bits/stdc++.h>
#include <CGAL/number_utils.h>
#include <CGAL/Gmpfr.h>



#include <fstream>
#include <string>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <sstream>
#include <CGAL/Gmpq.h>
#include <regex>
#include <fstream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <utility>
#include <map>
#include <CGAL/Line_2.h>

#include <set>
#include <unistd.h>
#include <pthread.h>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>
#include <CGAL/Arr_batched_point_location.h>
#include <CGAL/Lazy_exact_nt.h>


typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Exact_predicates_tag                              Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K> CDT;
typedef K::Point_2 Point;
typedef K::Line_2 Line;
typedef K::RT RT;

typedef CDT::Edge Edge;
typedef CGAL::Gmpq ExactType;
typedef CGAL::Lazy_exact_nt<CGAL::Epeck::FT> NT;
using namespace std; 
using namespace boost::property_tree;

/*Η δόμη struct DATA έχει φτίαχτει με βάση την μορφή του input.json, το οποίο περιέχει το πλήθος των σημείων,
΄ένα δίανυσμα x και ένα διάνυσμα y με τα σημέια, ένα διανύσμα με τα σημεία τα οποία βρίσκονται στο κυρτό περίβλημα , το πλήθος των σημείων 
που δεν επιτρέπεται να αλλάξουν και ένα διάνυσμα για αυτά τα σημεία*/

struct DATA{
    string instance_uid;
    int num_points;
    vector<int> points_x, points_y ;
    vector<int> region_boundary;
    int num_constraints;
    vector<vector<int>> additional_constraints;


};


struct DATA2{
    string instance_uid;
    int num_points;
    vector<int> points_x, points_y ;
    vector<int> region_boundary;
    int num_constraints;
    vector<vector<int>> additional_constraints;
    string method;
    map<string, double> parameters;
    bool delaunay;
 
    

};



template <class Gt, class Tds = CGAL::Default, class Itag = CGAL::Default>

class Custom_Constrained_Delaunay_triangulation_2

    : public CGAL::Constrained_Delaunay_triangulation_2<Gt, Tds, Itag> {

public:

    using Base = CGAL::Constrained_Delaunay_triangulation_2<Gt, Tds, Itag>;

    using typename Base::Face_handle;

    using typename Base::Point;

    using typename Base::Vertex_handle;

    using typename Base::Locate_type;



    // Constructors

    Custom_Constrained_Delaunay_triangulation_2(const Gt& gt = Gt())

        : Base(gt) {}



    Custom_Constrained_Delaunay_triangulation_2(typename Base::List_constraints& lc, const Gt& gt = Gt())

        : Base(lc, gt) {}



    template <class InputIterator>

    Custom_Constrained_Delaunay_triangulation_2(InputIterator it, InputIterator last, const Gt& gt = Gt())

        : Base(it, last, gt) {}



    // New insert method without flips

    Vertex_handle insert_no_flip(const Point& a, Face_handle start = Face_handle()) {

        // Call Ctr::insert without flip_around

        Vertex_handle va = this->Base::Ctr::insert(a, start); // Directly call Ctr::insert from the base

        return va;

    }



    // Another insert method with known location

    Vertex_handle insert_no_flip(const Point& a, Locate_type lt, Face_handle loc, int li) {

        Vertex_handle va = this->Base::Ctr::insert(a, lt, loc, li); // Directly call Ctr::insert from the base

        return va;

    }

};
typedef Custom_Constrained_Delaunay_triangulation_2<K> Custom_CDT;

//Συναρτήσεις για διαβασμα και εισαγωγή σε json files (input output) , συνάρτηση για σχεδίαση των σχημάτων και συνάρτηση για διαχείρηση ρητών
int READ_DATA2(DATA2& );
int READ_DATA(DATA&);
void extract_to_output(const vector<Point>& , Custom_CDT& , const string& , const string&) ;
void extract_to_output2(const vector<Point>& , Custom_CDT& , const string& , const string& , int ,map<string, double>, string ) ;
void draw(QGraphicsScene& , Custom_CDT& , double scale);
string rational_to_string(const K::FT& );

//Συναρτήσεις που χρησιμοποοιούνται στο project_1 για αρχική τριγωνοποίηση delaunay και edge-flipping
int Contrained_Delaunay(Custom_CDT& ,DATA); 
vector<pair<CDT::Face_handle, int>> check_for_obtuse(Custom_CDT& );
bool  check_obtuse_triangle(CDT::Face_handle );
bool is_obtuse_i(CDT::Face_handle , int);
bool is_flippable(Custom_CDT& , CDT::Face_handle , int);
void flip_edges(Custom_CDT &, vector<pair<CDT::Face_handle, int >>);

//Συναρτήσεις που υλοποιήθηκαν για το project_1 για την εισαγωγή steiner points σε ολοκληρη την τριγωνοποίηση
Point find_height_intersection(Point , Point  , Point);
vector<CDT::Vertex_handle> add_steiner_points_to_middle(Custom_CDT& ,vector<pair<CDT::Face_handle, int>> );
vector<Point> add_steiner_point_to_incenter(Custom_CDT& , const vector<pair<CDT::Face_handle, int>> );
vector<Point> add_steiner_point_to_circumcenter(Custom_CDT&, vector<pair<CDT::Face_handle, int>>);
vector<Point> add_steiner_point_to_h(Custom_CDT& , vector<pair<CDT::Face_handle, int>>);
bool has_constraints(CDT::Face_handle);
Point add_steiner_point_to_polygon_centroid(Custom_CDT& ,vector<CDT::Vertex_handle>);
vector< Point>add_steiner_point_to_polyg(Custom_CDT& , const vector<pair<CDT::Face_handle, int>>);






//Extern μεταβλητές
extern map<string, function<Point(Custom_CDT&, CDT::Face_handle, DATA, int)>>map_of_functions;  //map με όλες τις μεθόδους [ονομα, συνάρτηση], χρησιμοποιείται στην local
extern vector<Point> all_steiners_added;   //vector με όλα τα steiner point που εισάγονται στο cdt, το χρησιμοποιούμε στο main προγραμμα για extract to json
extern string input_file;  //όνοματα input-output file τα οποία λαμβάνουμε από command line arguments 
extern string output_file;
extern map<string, double> parameters_used;  //map με τις παραμέτρους που όντως χρησιμοποιεί ο κάθε αλγόριθμος χρειάζεται για να κάνουμε extract τις σωστές παραμέτους στο output.json

//Συναρτήσεις που δημιουργήθηκαν για το project_2 , οι οποίες εισάγουν το πολύ ένα sp στο δωσμένο face, αλλίως επιστρέφουν του τετρημμένο P(-1.0,-1.0)
Point point_to_middle(Custom_CDT& , CDT::Face_handle, DATA, int);
Point point_to_circumcenter( Custom_CDT& , CDT::Face_handle, DATA , int);
Point point_to_incenter(Custom_CDT& ,CDT::Face_handle, DATA,int );
Point point_to_centroid(Custom_CDT &,CDT::Face_handle , DATA,int);
Point point_to_polyg(Custom_CDT& , CDT::Face_handle, DATA,int );
Point point_to_h(Custom_CDT& , CDT::Face_handle , DATA, int);
bool is_valid_point(const Custom_CDT& , const Point&);
Point add_to_polygon_centroid(Custom_CDT& , vector<CDT::Vertex_handle> );

Point project_point_on_line(const Point& p, const Line& l);
int project1(Custom_CDT&);
void create_map();

//Οι main αλγόριθμοι που μας ζηητήθηκαν 
void local_search(DATA2& , Custom_CDT& );
void ant_colony(DATA2& , Custom_CDT& );
void simulated_annealing(DATA2&, Custom_CDT&);



void checking(Custom_CDT&, DATA2&);




typedef struct thread_input
{
    Custom_CDT cdt;    //ώστε να δημιορυγούμε copy_cdt
    DATA data;         //Ώστε να δώσει τη δομή DATA ως είσοδο στις μεθόδους steiner point
    int i;             //Το ant_id
    vector<pair<string, double>> pheror;   //Οι φερορμόνες κάθε μεθόδου , ανανεωμένες (ξεκινώντας από 1.0)
    double a,b,x,y;   //Ορίσματα που είναι αναγκαία για υπολογισμούς (ενέργειας και πιθανοτήτων)
}thr_inp ;



//Struct που δημιουργεί κάθε μυρμήγκι με τα δεδομένα που έχει και τα αποτελέσματα που βγάζει, είναι ουσιαστικά ένα log της εργασίας του
typedef struct ant_evaluation
{
    int ant_id;
    int steiner_point_added;  //1 ή 0 αν το μυρμληγκι καλέιται να βάλει steiner σε ένα face
    int number_of_obtuses;   //Πόσες αμβλείες βελτίωσε
    string method;   //Ποια μέθοδο χρησιμοποίησε (ονοματικά)
    double perfomance;   //ένα μέτρο αξιολόγηης, στο οποίο χρησιμοποιούμε radius imporenment - aspect ratio - number of obtuses - steiner point και βάρη
    double radius_improvment;
    double aspect_ratio_change;
    CDT::Face_handle face;   //Το τυχαίο face στο οποίο δούλεψε
    vector<Point> vertices;  //vector από 3 Points (χρειάστηκε διότι είχαμε προβλήματα με τη μεταφορά Face_handle)
    double energy;    //Ενέργεια 
    bool helped;   //Αν μείωσε τις αμβλείες ή οχι
    int obtuse_index;
}ant_eval ;


//Βοηθητικές συναρτήσεις για τον αλγόριθμο ant_colony 
double compute_r(CDT::Face_handle, int);
double middle_probabiliy(double );
double altitude_probabiliy(double );
double circumcenter_probabiliy(double );
int find_neigh(CDT::Face_handle );
double compute_aspect_ratio(const CDT::Face_handle& );
double compute_aspect_ratio_change(const Custom_CDT& );
double compute_average_radius(const Custom_CDT& );
double compute_performance(const ant_eval&);
vector<pair<string ,double>> compute_htta(double);
vector<pair<string, double>> compute_p(vector<pair<string, double>> , vector<pair<string, double>> , double , double );
int select_method(const vector<pair<string, double>>&);
void* ant_work(void* );
bool face_exists_in_cdt(Custom_CDT& , CDT::Face_handle );
CDT::Face_handle find_face_by_vertices(Custom_CDT& ,const vector<Point>&);
void create_results_map();
void save_best_tring(Custom_CDT& , vector<ant_eval> , DATA );
void update_pherormones(vector<pair<string, double>> &, double , double , int , int , double );

void analyze_boundary(DATA2&);
#endif // UTILS_HP