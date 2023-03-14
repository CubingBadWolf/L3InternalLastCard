#include "includes.h"
#include "Card.hpp"
#include "Deck.hpp"
#include "VerifyUserInput.hpp"


int main(){
    Card card; //testing empty card
    card.suit = 'S';
    card.number = verifyInputs("Enter what number for the card: ",1,13); //testing taking in card values from input

    Card card2('D', 2); //testing predefined cards
    Card Picture('D' ,verifyInputs("Enter a number for a picture card:",1,13)); //Testing whether the picture card switch works

    std::cout << "The first card is " << card.number << card.suit << std::endl; 
    std::cout << "The second card is " << card2.number << card2.suit << std::endl;

    if(Picture.Picture){ //checking whether assigning picture cards work
        std::cout << "The picture card is " << Picture.pictureValue << Picture.suit << std::endl;
    }
    else{
        std::cout << "That card is not a picture card. It is " << Picture.pictureValue << Picture.suit << ". Which is the same as " << Picture.number << Picture.suit << std::endl;
    }

    //outputting the cards to test
}   
