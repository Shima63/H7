#include <iostream>
#include <string>
#include "print.h"
using namespace std;
    
// Defining Struct

struct myentry {
    string network_code;
    string station_code;
    string type_of_band;
    string type_of_instrument;
    string orientation;
};

int flag, num_of_valid_entries = 0, num_of_signal = 0;

class station {
    
    public:
    
        // Set and Get Functions

        void set_network_code ( int, string, ofstream & );
        string get_network_code ();
        void set_station_code ( int, string, ofstream & );
        string get_station_code ();
        void set_type_of_band ( int, string, ofstream & );
        string get_type_of_band ();
        void set_type_of_instrument ( int, string, ofstream & );
        string get_type_of_instrument ();
        void set_orientation ( int, string, ofstream &, myentry  entry_array[] );
        string get_orientation ();
    
        // Other Functions

        void check_network_code ( int, string, ofstream & );
        void check_station_code ( int, string, ofstream & );
        void check_type_of_band ( int, string , ofstream & );
        void check_type_of_instrument ( int, string, ofstream & );
        void make_Print ( ofstream &, int );

    private:
    
        string network_code;
        string station_code;
        string type_of_band;
        string type_of_instrument;
        string orientation;

};