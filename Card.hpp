#include "includes.h"

#ifndef CARD
#define CARD
struct Card{
private:
public:
    char suit;
    char pictureValue;
    int number;
    bool Picture;
    Card(){ // Defines a constructor with no given values ie a blank card
    }
    Card(int Suit, int Number){ //Defines a constructor with the values of the card given
        number = Number; //assigns the values to the class
        switch(Number){ //This switch allows for assigning whether a card is a picture card/ace or not. 
            case 1:
                pictureValue = 'A';
                Picture = true;
                break;
            case 10:
                pictureValue = 'T';
                Picture = true;
                break;
            case 11:
                pictureValue = 'J';
                Picture = true;
                break;
            case 12:
                pictureValue = 'Q';
                Picture = true;
                break;
            case 13:
                pictureValue = 'K';
                Picture = true;
                break;
            default: //If it is not then the char value will not be a letter hence Picture should be false
                pictureValue = '0' + number;
                Picture = false;
        }
        switch(Suit){ //Takes in an interger and generates the suit of the card based on this
            case 0:
                suit = 'S';
                break;
            case 1:
                suit = 'D';
                break;
            case 2:
                suit = 'C';
                break;
            case 3:
                suit = 'H';
                break;
            default: // Throws an error if the suit is not valid
                throw("Invalid Suit");
            
        }
    }
};
#endif