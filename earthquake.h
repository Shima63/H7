#include <iostream>
#include "print.h"

using namespace std;

string message;
enum months { 
    January = 1, February, March, April, May, June,
    July, August, September, October, November, December
};

class earthquake {
    public:
    
        // Set and Get Functions
    
        void set_Event_ID ( string);
        string get_Event_ID ();
        string set_date ( string, ofstream & );
        string get_date ();
        void set_time ( string, ofstream & );
        string get_time ();
        void set_time_zone ( string, ofstream & );
        string get_time_zone ();
        void set_earthquake_name ( string );
        string get_earthquake_name ();
        void set_latitude ( string );
        string get_latitude ();
        void set_longitude ( string );
        string get_longitude ();
        void set_depth ( string );
        string get_depth ();
        void set_magnitude_type_string ( string, ofstream & );
        string get_magnitude_type_string ();
        void set_magnitude_size ( float, ofstream & );
        float get_magnitude_size ();
        
        // Other Functions
        
        void check_date ( string, ofstream & );
        void check_month ( int, ofstream & );
        void check_day ( int, ofstream & );
        void check_year ( int, ofstream & );
        void check_time ( string, ofstream & );
        void check_time_zone ( string, ofstream & );
        void check_magnitude_type ( string, ofstream & );
        void check_magnitude_size ( float, ofstream & );
        string monthstring ( months );

    private:
    
            string Event_ID;
            string date;
            string time;
            string time_zone;
            string earthquake_name;
            string longitude;
            string latitude;
            string depth;
            string magnitude_type_string;
            float magnitude_size;

};