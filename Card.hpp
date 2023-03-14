#include "includes.h"
struct Card{
private:
public:
    char suit;
    char pictureValue;
    int number;
    bool Picture;
    Card(){ // Defines a constructor with no given values ie a blank card
    }
    Card(char Suit, int Number){ //Defines a constructor with the values of the card given
        suit = Suit;
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
    }
};
