// This Is Earthquake Class Containing Header Parts

#include <iostream>
#include <stdlib.h>
#include "earthquake.h"
#include "print.h"
using namespace std;

string message;

// Set and Get Functions For Earthquake Struct

void earthquake :: set_Event_ID ( string s ) {
    Event_ID = s;
    return;
}

string earthquake :: get_Event_ID () {
    return Event_ID;
}

string earthquake :: set_date ( string s, ofstream & logfile ) {
    
    // Variables
    
    int value;
    string tempa, tempb, tempc, month;
    months month_name;
    
    date = s;
    check_date ( date, logfile );
    
    // Finding and Checking Validity of the Month
    
    tempa =  tempa.append ( date.begin (), date.begin () + 2 );
    value = atoi( tempa.c_str () );
    check_month ( value, logfile );
    month_name = months(value);
    month = monthstring ( month_name );
    
    // Finding and Checking Validity of the day
    
    tempb =  tempb.append ( date.begin () + 3, date.begin () + 5 );
    value = atoi( tempb.c_str () );
    check_day ( value, logfile );
    
    // Finding and Checking Validity of the year
    
    tempc =  tempc.append ( date.begin () + 6, date.end () );
    value = atoi( tempc.c_str () );
    check_year ( value, logfile );
    
    // Returning Month

    return month;
}

string earthquake :: get_date () {
    return date;
}

void earthquake :: set_time ( string s, ofstream & logfile ) {
    time = s;
    check_time ( time, logfile );
    return;
}

string earthquake :: get_time () {
    return time;
}

void earthquake :: set_time_zone ( string s, ofstream & logfile ) {
    time_zone = s;
    check_time_zone ( time_zone, logfile );
    return;
}

string earthquake :: get_time_zone () {
    return time_zone;
}

void earthquake :: set_earthquake_name ( string s ) {
    earthquake_name = s;
    return;
}

string earthquake :: get_earthquake_name () {
    return earthquake_name;
}

void earthquake :: set_latitude ( string s ) {
    latitude = s;
    return;
}

string earthquake :: get_latitude () {
    return latitude;
}

void earthquake :: set_longitude ( string s ) {
    longitude = s;
    return;
}

string earthquake :: get_longitude () {
    return longitude;
}

void earthquake :: set_depth ( string s ) {
    depth = s;
    return;
}

string earthquake :: get_depth () {
    return depth;
}

void earthquake :: set_magnitude_type_string ( string s, ofstream & logfile ) {
    magnitude_type_string = s;
    check_magnitude_type ( magnitude_type_string, logfile );
    return;
}

string earthquake :: get_magnitude_type_string () {
    return magnitude_type_string;
}

void earthquake :: set_magnitude_size ( float s, ofstream & logfile ) {
    magnitude_size = s;
    check_magnitude_size ( magnitude_size, logfile );
    return;
}

float earthquake :: get_magnitude_size () {
    return magnitude_size;
}

// Other Functions

// This "check_date" Function Checks the Validity of Date Entry.

void earthquake :: check_date ( string date, ofstream & logfile ) {
    message = "Date format is not right.";
    if ( date.length() != 10 ) {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    else {
        if ( ( ( date[2] != "-"[0] ) && ( date[2] != "/"[0] ) ) || ( ( date[5] != "-"[0] ) && ( date[5] != "/"[0] ) ) ) {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }
        else {
            if ( ( !isdigit ( date[0] ) ) || ( !isdigit ( date[1] ) ) || ( !isdigit ( date[3] ) ) || ( !isdigit ( date[4] ) ) ) {
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }  
            if ( ( !isdigit ( date[6] ) ) || ( !isdigit ( date[7] ) ) || ( !isdigit ( date[8] ) ) || ( !isdigit ( date[9] ) ) ) {
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }
        }
    }
    return;
}    

// This "check_month" Function Checks the Validity of Month Entry.

void earthquake :: check_month ( int month, ofstream & logfile ) {
    if ( ( month > 12 ) || ( month < 1 ) ) {
        message = "Month format is not right.";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}

// This "check_day" Function Checks the Validity of Day Entry.

void earthquake :: check_day ( int day, ofstream & logfile ) {
    if ( ( day > 31 ) || ( day < 1 ) ) {
        message = "Day is not right.";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}

// This "check_year" Function Checks the Validity of Year Entry.

void earthquake :: check_year ( int year, ofstream & logfile ) {
    if ( year < 0 ) {
        message = "Year is not right.";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}

// This "check_time" Function Checks the Validity of Time Entry.

void earthquake :: check_time ( string time, ofstream & logfile ) {
    message = "Time format is not right.";
    if ( time.length() != 12 ) {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    else {
        if ( ( time[2] != ":"[0] ) || ( time[5] != ":"[0] ) || ( time[8] != "."[0] ) ) {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }
        else {
            if ( ( !isdigit ( time[0] ) ) || ( !isdigit ( time[1] ) ) || ( !isdigit ( time[3] ) ) || ( !isdigit ( time[4] ) ) ) {
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }  
            if ( ( !isdigit ( time[6] ) ) || ( !isdigit ( time[7] ) ) || ( !isdigit ( time[9] ) ) 
            || ( !isdigit ( time[10] ) ) || ( !isdigit ( time[11] ) ) ) {
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }
        
            // Defining Temporary Variables
        
            string temp0, temp1, temp2;
            double value;
        
            // Finding and Checking Validity of the Hour
  
            temp0 =  temp0.append ( time.begin (), time.begin () + 2 );
            value = atoi(temp0.c_str());
            if ( ( value < 0 ) || ( value > 23 ) ) {
                message = "Hour is not right.";
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }
        
            // Finding and Checking Validity of the Minute
  
            temp1 =  temp1.append ( time.begin () + 3, time.begin () + 5 );
            value = atoi(temp1.c_str());
            if ( ( value < 0 ) || ( value > 59 ) ) {
                message = "Minute is not right.";
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }
        
            // Finding and Checking Validity of the Second
  
            temp2 =  temp2.append ( time.begin () + 6, time.begin () + 8 );
            value = atoi(temp2.c_str());
            if ( ( value < 0 ) || ( value > 59.999 ) ) {
                message = "Second is not right.";
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }                    
        }
    }
    return;
}    

// This "check_time_zone" Function Checks the Validity of Time Zone Entry.

void earthquake :: check_time_zone ( string time_zone, ofstream & logfile ) {
    message = "Time_zone format is not right.";
    if ( ( time_zone.length() != 3 ) || ( !isalpha ( time_zone[0] ) ) || ( !isalpha ( time_zone[1] ) ) || ( !isalpha ( time_zone[2] ) ) ) {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    
    return;
}    

// This "check_magnitude_type" Function Checks the Validity of Magnitude Type Considering It Case Insensitive.

void earthquake :: check_magnitude_type ( string magnitude_type, ofstream & logfile ) {
    message = "magnitude_type is not right.";
    string mt = uppercase ( magnitude_type );
    if ( ( mt != uppercase ( "ml" ) ) && ( mt != uppercase ( "ms" ) ) && ( mt != uppercase ( "mb" ) ) && ( mt != uppercase ( "mw" ) ) ) {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}

// This "check_magnitude_size" Function Checks the Validity of Magnitude Size as a Positive Real Number ( > 0 ).

void earthquake :: check_magnitude_size ( float magnitude_size, ofstream & logfile ) {
    message = "magnitude_size is not right.";
    if ( magnitude_size <= 0 ) {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}

// Function to Convert from "month" to a String...

string earthquake :: monthstring ( months month ) {
    switch ( month ) {
        case January:
            return "January";
        case February:
            return "February";
        case March:
            return "March";
        case April:
            return "April";
        case May:
            return "May";
        case June:
            return "June";
        case July:
            return "July";
        case August:
            return "August";
        case September:
            return "September";
        case October:
            return "October";
        case November:
            return "November";
        case December:
            return "December";
        default:
            return "ILLEGAL";
    }
}

