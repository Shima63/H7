#include <iostream>
#include <string>
#include "print.h"
using namespace std;
    
class station {
    
    public:
    
        // Set and Get Functions

        int set_network_code ( int, string, ofstream &, int );
        string get_network_code ();
        int set_station_code ( int, string, ofstream &, int );
        string get_station_code ();
        int set_type_of_band ( int, string, ofstream &, int );
        string get_type_of_band ();
        int set_type_of_instrument ( int, string, ofstream &, int );
        string get_type_of_instrument ();
        int set_orientation ( int, string, ofstream &, string &, string &, string &, int );
        string get_orientation ();
    
        // Other Functions

        int check_network_code ( int, string, ofstream &, int );
        int check_station_code ( int, string, ofstream &, int );
        int check_type_of_band ( int, string, ofstream &, int );
        int check_type_of_instrument ( int, string, ofstream &, int );

    private:
    
        string network_code;
        string station_code;
        string type_of_band;
        string type_of_instrument;
        string orientation;

};