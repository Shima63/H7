#include <iostream>
#include "station.h"
#include "print.h"
using namespace std;

// Set and Get Functions For Earthquake Struct

// Function set_network_code
        
int station :: set_network_code (  int num_of_input, string temp_network_code, ofstream & logfile, int flag) {
    flag = check_network_code ( num_of_input, temp_network_code, logfile, flag );
    network_code = temp_network_code;
    return flag;
}
        
// Function get_network_code
        
string station :: get_network_code () {
    return network_code;
}
                
// Function set_station_code
        
int station :: set_station_code (  int num_of_input, string temp_station_code, ofstream & logfile, int flag ) {
    flag = check_station_code ( num_of_input, temp_station_code, logfile, flag );
    station_code = temp_station_code;
    return flag;
}
        
// Function get_station_code
        
string station :: get_station_code () {
    return station_code;
}

// Function set_type_of_band
        
int station :: set_type_of_band ( int num_of_input, string temp_type_of_band, ofstream & logfile, int flag ) {
    flag = check_type_of_band ( num_of_input, temp_type_of_band, logfile, flag );
    type_of_band = temp_type_of_band;
    return flag;
}
        
// Function get_type_of_band
        
string station :: get_type_of_band () {
    return type_of_band;
}
        
// Function set_type_of_instrument
        
int station :: set_type_of_instrument ( int num_of_input, string temp_type_of_instrument, ofstream & logfile, int flag ) {
    flag = check_type_of_instrument ( num_of_input, temp_type_of_instrument, logfile, flag );
    type_of_instrument = temp_type_of_instrument;
    return flag;
}
        
// Function get_type_of_instrument
        
string station :: get_type_of_instrument () {
    return type_of_instrument;
}

// Function set_orientation
        
int station :: set_orientation ( int num_of_input, string temp_orientation, ofstream & logfile, 
string & temp1, string & temp2, string & temp3, int flag ) {
    temp1 = "";
    temp2 = "";
    temp3 = "";              
    if ( ( temp_orientation.length() < 1 ) ||  ( temp_orientation.length() > 3 ) ) {
        flag = 5;
    }
    else {
        temp1 = temp_orientation[0];
        if ( ( temp1 != "1" ) && ( temp1 != "2" ) && ( temp1 != "3" ) ) {
            if ( ( uppercase ( temp1 ) != uppercase ( "N" ) ) && ( uppercase ( temp1 ) != uppercase ( "E" ) ) 
            && ( uppercase ( temp1 ) != uppercase ( "Z" ) ) ) { 
                flag = 5;
            }
            else {
                if ( temp_orientation.length() > 1 ) {
                    temp2 = temp_orientation[1];
                    if ( ( temp2 != "N" ) && ( temp2 != "E" ) && ( temp2 != "Z" ) ) {
                        flag = 5;
                    }
                    else {
                        if ( temp_orientation.length() > 2 ) {
                            temp3 = temp_orientation[2];
                            if ( ( temp3 != "N" ) && ( temp3 != "E" ) && ( temp3 != "Z" ) ) {
                                flag = 5;
                            } 
                        }
                    }
                }
            }
        }
        else {
            if ( temp_orientation.length() > 1 ) {
                temp2 = temp_orientation[1];
                if ( ( temp2 != "1" ) && ( temp2 != "2" ) && ( temp2 != "3" ) ) {
                    flag = 5;
                }
                else {
                    if ( temp_orientation.length() > 2 ) {
                        temp3 = temp_orientation[2];
                        if ( ( temp3 != "1" ) && ( temp3 != "2" ) && ( temp3 != "3" ) ) {
                            flag = 5;
                        } 
                    }
                }
            }
        }
    }                     
    if ( flag == 5 ) {
        print_file ( "Entry # ", logfile );
        print_file ( num_of_input, logfile );
        print_file ( " ignored. Invalid orientation. ", logfile ); 
        print_file ( "\n", logfile );  
    }
    return flag;
}
        
// Function get_orientation
        
string station :: get_orientation () {
    return  orientation;
} 

// Other Functions

// Function to Check Network Code

int station :: check_network_code ( int num_of_input, string code, ofstream & logfile, int flag ) {
    if ( ( code.length() != 2 ) || ( ( code != "CE" ) && ( code != "CI" ) && ( code != "FA" ) 
    && ( code != "NP" ) && ( code != "WR" ) ) ) {
        flag = 1;
    }
    if ( flag == 1) {
        print_file ( "Entry # ", logfile );
        print_file ( num_of_input, logfile );
        print_file ( " ignored. Invalid network. ", logfile );
        print_file ( "\n", logfile );
    }
    return flag;
}

// Function to Check Station Code

int station :: check_station_code ( int num_of_input, string code, ofstream & logfile, int flag ) {
    if ( code.length() != 3 ) {
        if ( code.length() != 5 ) {
            flag = 2;
        }
        else {
            if ( ( !isdigit ( code[0] ) ) || ( !isdigit ( code[1] ) ) || ( !isdigit ( code[2] ) ) 
            || ( !isdigit ( code[3] ) ) || ( !isdigit ( code[4] ) ) ) {
                flag = 2;
            }    
        }
    }
    else {
        if ( ( !isalpha ( code[0] ) ) || ( !isalpha ( code[1] ) ) || ( !isalpha ( code[2] ) ) ) {
            flag = 2;
        }
        else {
            if ( uppercase ( code ) != code ) {
                flag = 2;
            }    
        }
    }
    if ( flag == 2) {
        print_file ( "Entry # ", logfile );
        print_file ( num_of_input, logfile );
        print_file ( " ignored. Invalid station code. ", logfile ); 
        print_file ( "\n", logfile );
    }
    return flag;
}            
    
// Function to Check Type of Band

int station :: check_type_of_band ( int num_of_input, string band, ofstream & logfile, int flag ) {
    if ( ( uppercase ( band ) != uppercase ( "Long-period" ) ) && ( uppercase ( band ) != uppercase ( "Short-period" ) ) 
    && ( uppercase ( band ) != uppercase ( "Broadband" ) ) ) {
        flag = 3;
    }
    if ( flag == 3 ) {
        print_file ( "Entry # ", logfile );
        print_file ( num_of_input, logfile );
        print_file ( " ignored. Invalid type of band. ", logfile ); 
        print_file ( "\n", logfile );
    }
    return flag;
}    
       
int station :: check_type_of_instrument ( int num_of_input, string instrument, ofstream & logfile, int flag ) {
    if ( ( uppercase ( instrument ) != uppercase ( "High-Gain" ) ) && ( uppercase ( instrument ) != uppercase ( "Low-Gain" ) ) 
    && ( uppercase ( instrument ) != uppercase ( "Accelerometer" ) ) ) {
        flag = 4;
    }
    if ( flag == 4 ) {
        print_file ( "Entry # ", logfile );
        print_file ( num_of_input, logfile );
        print_file ( " ignored. Invalid type of instrument. ", logfile ); 
        print_file ( "\n", logfile );
    }
    return flag;
}
