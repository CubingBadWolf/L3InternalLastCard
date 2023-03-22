#include "includes.h"
#ifndef IN
#define IN
using namespace std; //std namespace suitable for header file as unlikely to contain duplicate library names

int verifyInputs(string message, int min, int max){
    //message is the message to print, max is the max integer value for range, min is the minimum integer value for range, min/max inclusive
    string in;
    int num;
    cout << message;
    while (true){
        cnt: //goto redirects here to begin the loop again
        cin.clear();
        cin >> in; //Takes user input

        for(int i = 0; i < in.length(); i++){
            if (!isdigit(in[i])){ //Checks if all characters in the string are numeric
                cout << "Please enter an integer: ";
                goto cnt; //skips over the second check if non numeric character is found
            }
        }

        num = stoi(in); //converst the now checked for integer string to an int
        if (num < min || num > max){ //Check if the integer value is inside the range provided (inclusive)
            cout << in << " is not in range of values. Please enter a different integer: ";
            continue;
        }
        else {
            return num; //returns the integer value
        }
    } 
}

int verifyInputs(string message){
    //Overloading function to allow for no range of integer to purely check if an input is an integer
    string in;
    int num;
    cout << message;
    while (true){
        cin.clear();
        cin >> in;
        for(int i = 0; i < in.length(); i++){
            if (!isdigit(in[i])){ //Checks if all characters in the string are numeric
                cout << "Please enter an integer: ";
                break;
            }
        }
        num = stoi(in);
        return num;
    } 
}
#endif