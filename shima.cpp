/*
 * H7 Program
 * Use of Classes and Their Associate Concepts of Scope, Privacy and Encapsulation.
 * By Shima Azizzadeh-Roodpish
 * 23 March 2015
 * No Copyright
 * Github account: https://github.com/Shima63/H7.git
 */
 
// External Libraries

#include <stdlib.h>
#include <cstdlib> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctype.h>
#include <locale>
using namespace std;

// Defined Libraries

#include "earthquake.h"
#include "print.h"

// Global Variables

string inputfilename, outputfilename = "shima.out", logfilename = "shima.log";
int flag;
string mymessage;

// Defining Struct

struct station {
    string network_code;
    string station_code;
    string type_of_band;
    string type_of_instrument;
    string orientation;
};    
    
// Defining Enumerators

enum magnitude_type {
    ML, Ms, Mb, Mw
};

enum network_code {
    CE, CI, FA, NP, WR
};

enum band_type {
    longperiod, shortperiod, broadband
};

enum instrument_type {
    highgain, lowgain, accelerometer
};
     
station entry_array [ 300 ];
station entry_temp;

// ********************************************************************************************************************

// Function Prototype

void open_input ( ifstream & );
void open_file ( string, ofstream & );
void produce_signal ( ofstream &, string, string, string, string, string, string );
void check_network_code ( int, string, ofstream & );
void check_station_code ( int, string, ofstream & );
void check_type_of_band ( int, string , ofstream & );
void check_type_of_instrument ( int, string, ofstream & );
string magnitude_type_to_string ( magnitude_type );
magnitude_type string_to_magnitude_type ( string );
string network_code_to_string ( network_code );
network_code string_to_network_code ( string );
string band_type_to_string ( band_type );
band_type string_to_band_type ( string );
string instrument_type_to_string ( instrument_type );
instrument_type string_to_instrument_type ( string );


// Set and Get Functions

void set_network_code ( int, string, station &, ofstream & );
string get_network_code ();
void set_station_code ( int, string, station &, ofstream & );
string get_station_code ();
void set_type_of_band ( int, string, station &, ofstream & );
string get_type_of_band ();

// ********************************************************************************************************************

// Main Program.
// Return Zero on Success, Non-Zero in case of Failure.

int main () {

    // Defining Variables' Type
    
    earthquake header;
    
    string Event_ID, date, time, time_zone, earthquake_name, latitude, longitude, depth, magnitude_type_string;
    string earthquake_name_continue, day, month, year;
    string temp1, temp2, temp3;
    string temp_network_code, temp_station_code, temp_type_of_band;
    int num_of_valid_entries = 0, num_of_input = 0, num_of_signal = 0;
    float magnitude_size;
    
    // Prompt User for Input File Name.

    ifstream inputfile;
    open_input ( inputfile );
    
    // Preparing log file
    
    ofstream logfile;
    open_file ( logfilename, logfile );
    
    print_file ( "Opening file: shima.in", logfile );
    print_file ( "\n", logfile );
    print_file ( "Processing input ...", logfile );
    print_file ( "\n", logfile );
    
    // Reading and Checking Header
        
    inputfile >> Event_ID;
    header.set_Event_ID ( Event_ID );
    inputfile >> date;
    month = header.set_date ( date, logfile );
    date = header.get_date ();
            
    inputfile >> time;
    header.set_time ( time, logfile );
    inputfile >> time_zone;
    header.set_time_zone ( time_zone, logfile );    
    inputfile >> earthquake_name;
    getline(inputfile, earthquake_name_continue);
    earthquake_name.append ( earthquake_name_continue ); 
    header.set_earthquake_name ( earthquake_name );
    
    // Epicenter Location
    
    inputfile >> longitude;
    header.set_longitude ( longitude );
    inputfile >> latitude;
    header.set_latitude ( latitude );
    inputfile >> depth;
    header.set_depth ( depth );
        
    // Magnitude Information
    
    inputfile >> magnitude_type_string;
    header.set_magnitude_type_string ( magnitude_type_string, logfile );
    inputfile >> magnitude_size;
    header.set_magnitude_size ( magnitude_size, logfile );

    mymessage = "Header read correctly!";
    print_file ( mymessage, logfile );
    print_file ( "\n\n", logfile );

    // Preparing output file
    
    ofstream outputfile;
    open_file ( outputfilename, outputfile );
    
    outputfile << "# " << day.append( date.begin () + 3, date.begin () + 5 ) << " " << month << " " 
    << year.append( date.begin () + 6, date.end () );
    outputfile << " " << header.get_time () << " " <<  header.get_time_zone () << " " << 
    magnitude_type_to_string ( string_to_magnitude_type ( header.get_magnitude_type_string () ) ) 
    << " " << header.get_magnitude_size () << " " << header.get_earthquake_name () << " ";
    outputfile << "[" << header.get_Event_ID () << "]  (" << header.get_longitude () << ", " 
    << header.get_latitude () << ", " << header.get_depth () << ")" << endl;

    // Reading Entries

    while ( ( inputfile >> temp_network_code ) && ( num_of_valid_entries < 300 ) ) {
        flag = 0;
        num_of_input = num_of_input + 1;
        
        // Checking
            
        set_network_code ( num_of_input, temp_network_code, entry_temp, logfile);
        temp_network_code = get_network_code ();
        inputfile >> temp_station_code;
        set_station_code ( num_of_input, temp_station_code, entry_temp, logfile);
        temp_station_code = get_station_code ();              
        inputfile >> temp_type_of_band;
        set_type_of_band ( num_of_input, temp_type_of_band, entry_temp, logfile);
        temp_type_of_band = get_type_of_band ();
        inputfile >> entry_temp.type_of_instrument;        
        check_type_of_instrument ( num_of_input, entry_temp.type_of_instrument, logfile );

       // Checking Orientation
        
        temp1 = "";
        temp2 = "";
        temp3 = "";
        inputfile >> entry_temp.orientation;        
        if ( ( entry_temp.orientation.length() < 1 ) ||  ( entry_temp.orientation.length() > 3 ) ) {
            flag = 5;
        }
        else {
            temp1 = entry_temp.orientation[0];
            if ( ( temp1 != "1" ) && ( temp1 != "2" ) && ( temp1 != "3" ) ) {
                if ( ( uppercase ( temp1 ) != uppercase ( "N" ) ) && ( uppercase ( temp1 ) != uppercase ( "E" ) ) 
                && ( uppercase ( temp1 ) != uppercase ( "Z" ) ) ) { 
                    flag = 5;
                }
                else {
                    if ( entry_temp.orientation.length() > 1 ) {
                        temp2 = entry_temp.orientation[1];
                        if ( ( temp2 != "N" ) && ( temp2 != "E" ) && ( temp2 != "Z" ) ) {
                            flag = 5;
                        }
                        else {
                            if ( entry_temp.orientation.length() > 2 ) {
                                temp3 = entry_temp.orientation[2];
                                if ( ( temp3 != "N" ) && ( temp3 != "E" ) && ( temp3 != "Z" ) ) {
                                    flag = 5;
                                } 
                            }
                        }
                    }
                }
            }
            else {
                if ( entry_temp.orientation.length() > 1 ) {
                    temp2 = entry_temp.orientation[1];
                    if ( ( temp2 != "1" ) && ( temp2 != "2" ) && ( temp2 != "3" ) ) {
                        flag = 5;
                    }
                    else {
                        if ( entry_temp.orientation.length() > 2 ) {
                            temp3 = entry_temp.orientation[2];
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
        if ( flag == 0 ) {   
            num_of_valid_entries = num_of_valid_entries + 1;
            entry_temp.orientation = temp1;
            entry_array [ num_of_signal ] = entry_temp;
            num_of_signal = num_of_signal + 1;
            if ( temp2 != "" ) {
                entry_temp.orientation = temp2;
                entry_array [ num_of_signal ] = entry_temp;
                num_of_signal = num_of_signal +1;
                if ( temp3 != "" ) {
                    entry_temp.orientation = temp3;
                    entry_array [ num_of_signal ] = entry_temp;
                    num_of_signal = num_of_signal +1;
                }
            }
        }            
    }

    print_file ( "Total invalid entries ignored: ", logfile );
    print_file ( ( num_of_input - num_of_valid_entries ), logfile );
    print_file ( "\n", logfile );
    print_file ( "Total valid entries read: ", logfile );
    print_file ( num_of_valid_entries, logfile );
    print_file ( "\n", logfile );
    print_file ( "Total signal names produced: ", logfile );
    print_file ( num_of_signal, logfile );
    print_file ( "\n", logfile );
    print_file ( "Finished!", logfile );
 
    // Printing Outputs
    
    outputfile << ( num_of_signal ) << endl;
    for (int i = 0; i < ( num_of_signal ); i++) {
        
        // Producing Signal
        
        produce_signal ( outputfile, header.get_Event_ID (), network_code_to_string ( string_to_network_code ( entry_array[i].network_code ) ), 
        entry_array[i].station_code, band_type_to_string ( string_to_band_type ( entry_array[i].type_of_band ) ), 
        instrument_type_to_string ( string_to_instrument_type ( entry_array[i].type_of_instrument ) ), entry_array[i].orientation );    
    }
    
    return 0;
}

// ********************************************************************************************************************

// Functions

// "open_input" Function Will Ask the Name of the Input File and Will Check Its Validity. 

void open_input ( ifstream & ifs ) {

    // Prompt User for Input File Name.

    cout << "Enter input file name: ";
    cin >> inputfilename;
 
    ifs.open(inputfilename.c_str());

    // Check to Make Sure the File Is Opened Properly

    if ( !ifs.is_open() ) {
        mymessage = "Input file does not exist!";
        
        // Making log file When There Is Error

        ofstream logfile;
        open_file ( logfilename, logfile );
        print_file ( mymessage, logfile );
        exit (EXIT_FAILURE);
    }   
    return;
} 

// "open_file" Function Will Make a New File.
    
void open_file ( string filename, ofstream & ofs ) {
    ofs.open(filename.c_str());
    if ( !ofs.is_open() ) {
        mymessage = "File does not exist!";
            
        // Making log file When There Is Error

        ofstream logfile;
        open_file ( logfilename, logfile );
        print_file ( mymessage, logfile );
        exit (EXIT_FAILURE);
    }
    return;
} 

// Function to Produce Signal Name as an String
        
void produce_signal ( ofstream & outputfile, string Event_ID, string network_code, string station_code, 
string type_of_band, string type_of_instrument, string orientation ) { 
    string temp= "";
    temp.append( Event_ID );
    temp.append( "." );
    temp.append( network_code );
    temp.append( "." );
    temp.append( station_code );
    temp.append( "." );
    temp.append( type_of_band );
    temp.append( type_of_instrument );
    temp.append( orientation );
    outputfile << temp << endl;
    return;
}       

// Function to Check Network Code

void check_network_code ( int num_of_input, string code, ofstream & logfile ) {
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
    return;
}

// Function to Check Station Code

void check_station_code ( int num_of_input, string code, ofstream & logfile ) {
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
    return;
}            
    
// Function to Check Type of Band

void check_type_of_band ( int num_of_input, string band, ofstream & logfile ) {
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
    return;
}    
       
void check_type_of_instrument ( int num_of_input, string instrument, ofstream & logfile ) {        
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
} 
   
// Function to Change Magnitude Type to String

string magnitude_type_to_string ( magnitude_type M ) {
    switch ( M ) {
        case ML:
            return "ML";
        case Ms:
            return "Ms";
        case Mb:
            return "Mb";
        case Mw:
            return "Mw";
    }
    exit(EXIT_FAILURE);
}

// Function to Change String to Magnitude Type

magnitude_type string_to_magnitude_type ( string NN ) {
    NN = uppercase ( NN );
    if ( NN == "ML" ) {
        return ML;
    }    
    if ( NN == "MS" ) {
        return Ms;
    }
    if ( NN == "MB" ) {
        return Mb;
    }
    if ( NN == "MW" ) {
        return Mw;
    }
    exit(EXIT_FAILURE);
}

// Function to Change Network Code to String

string network_code_to_string ( network_code MM ) {
    switch ( MM ) {
        case CE:
            return "CE";
        case CI:
            return "CI";
        case FA:
            return "FA";
        case NP:
            return "NP";
        case WR:
            return "WR";
    }
    exit(EXIT_FAILURE);
}

// Function to Change String to Network Code

network_code string_to_network_code (string NN) {
    NN = uppercase (NN);
    if ( NN == "CE" ) {
        return CE;
    }    
    if ( NN == "CI" ) {
        return CI;
    }
    if ( NN == "FA" ) {
        return FA;
    }
    if ( NN == "NP" ) {
        return NP;
    }
    if ( NN == "WR" ) {
        return WR;
    }
    exit(EXIT_FAILURE);
}

// Function to Change Band Type to String

string band_type_to_string ( band_type MMM ) {
    switch ( MMM ) {
        case longperiod:
            return "L";
        case shortperiod:
            return "B";
        case broadband:
            return "H";
    }
    exit(EXIT_FAILURE);
}

// Function to Change String to Band Type

band_type string_to_band_type (string NN) {
    NN = uppercase (NN);
    if ( NN == uppercase ( "Long-Period" ) ) {
        return longperiod;
    }    
    if ( NN == uppercase ( "Short-Period" ) ) {
        return shortperiod;
    }
    if ( NN == uppercase ( "Broadband" ) ) {
        return broadband;
    }
    exit(EXIT_FAILURE);
}

// Function to Change Instrument Type to String

string instrument_type_to_string ( instrument_type MMMM ) {
    switch ( MMMM ) {
        case highgain:
            return "H";
        case lowgain:
            return "L";
        case accelerometer:
            return "N";
    }
    exit(EXIT_FAILURE);
}

// Function to Change String to Instrument Type

instrument_type string_to_instrument_type (string NN) {
    NN = uppercase (NN);
    if ( NN == uppercase ( "High-Gain" ) ) {
        return highgain;
    }    
    if ( NN == uppercase ( "Low-Gain" ) ) {
        return lowgain;
    }
    if ( NN == uppercase ( "Accelerometer" ) ) {
        return accelerometer;
    }
    exit(EXIT_FAILURE);
}

// ***********************************************************************************

// Set and Get Functions For Station Struct

// Function set_network_code
        
void set_network_code (  int num_of_input, string temp_network_code, station & entry_temp, ofstream & logfile) {
    check_network_code ( num_of_input, temp_network_code, logfile );
    entry_temp.network_code = temp_network_code;
    return;
}
        
// Function get_network_code
        
string get_network_code () {
    return  entry_temp.network_code;
}
                
// Function set_station_code
        
void set_station_code (  int num_of_input, string temp_station_code, station & entry_temp, ofstream & logfile) {               
    check_station_code ( num_of_input, temp_station_code, logfile );
    entry_temp.station_code = temp_station_code;
    return;
}
        
// Function get_station_code
        
string get_station_code () {
    return  entry_temp.station_code;
}

// Function set_type_of_band
        
void set_type_of_band (  int num_of_input, string temp_type_of_band, station & entry_temp, ofstream & logfile) {               
    check_type_of_band ( num_of_input, temp_type_of_band, logfile );
    entry_temp.type_of_band = temp_type_of_band;
    return;
}
        
// Function get_type_of_band
        
string get_type_of_band () {
    return  entry_temp.type_of_band;
}
        
               