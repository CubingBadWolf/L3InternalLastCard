#include "includes.h"

#ifndef CARD
#define CARD
struct Card{
private:
public:
    char suit;
    char pictureValue;
    Card(){ // Defines a constructor with no given values ie a blank card
    }
    Card(int Suit, int Number){ //Defines a constructor with the values of the card given
        switch(Number){ //This switch allows for assigning whether a card is a picture card/ace or not. 
            case 1:
                pictureValue = 'A';
                break;
            case 10:
                pictureValue = 'T';
                break;
            case 11:
                pictureValue = 'J';
                break;
            case 12:
                pictureValue = 'Q';
                break;
            case 13:
                pictureValue = 'K';
                break;
            case 14:
                pictureValue = 'j'; //Joker will be represented with a lowercase j
                break;
                
            default: //If it is not then the char value will not be a letter hence Picture should be false
                pictureValue = '0' + Number;
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
            case 4:
                suit = ' '; //Jokers have no suit type
                break;
            default: // Throws an error if the suit is not valid
                throw("Invalid Suit");
            
        }
    }
    bool operator==(const Card& rhs) const { //manually define operator ==, to fix a bug
        return pictureValue == rhs.pictureValue && suit == rhs.suit;
    }
};
#endif