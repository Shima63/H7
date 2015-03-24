#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "print.h"

using namespace std;

// This "print_file" function Prints Messages on Files and Terminal. Message Is of String Type.

void print_file ( string message, ofstream & ofs ) {
    ofs << message << flush;
    cout << message << flush;
    return;
}

// This "print_file" function Prints numbers on Files and Terminal. Number Is of Int Type.

void print_file ( int number, ofstream & ofs ) {
    ofs << number << flush;
    cout << number << flush;
    return;
}

// This "string uppercase" function changes all the letters of the input string to upper case. ( For string )

string uppercase ( string s ) {
    string result = s;
    for (int i=0; i < (int)s.size(); i++)
        result[i] = toupper(s[i]);
    return result;
}    


