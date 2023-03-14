#include "includes.h"
using namespace std; //std namespace suitable for header file as unlikely to contain duplicate library names

int verifyInputs(string message, int min, int max){
    //message is the message to print, max is the max integer value for range, min is the minimum integer value for range, min/max inclusive
    int in;
    cout << message;
    while (true){
        cin >> in; //Tries assigning the input to an integer variable
        if (!cin){ //If its not successful
            cout << "Please enter an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //tells the input to check all input until it reaches a newline character \n hence all characters entered.
            continue;
        }
        if (in < min || in > max){ //Check if the integer value is inside the range provided (inclusive)
            cout << in << " is not in range of values. Please enter a different integer: ";
            continue;
        }
        else break; //break from loop if all values are not met
    } 
    return in; //returns the interger value
}

int verifyInputs(string message){
    //Overloading function to allow for no range of integer to purely check if an input is an integer
    int in;
    cout << message;
    while (true){
        cin >> in;
        if (!cin){
            cout << "Please enter an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else break;
    } 
    return in;
}