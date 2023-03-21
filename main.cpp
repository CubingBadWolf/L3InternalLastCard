#include "includes.h"
#include "Card.hpp"
#include "Deck.hpp"
#include "VerifyUserInput.hpp"

void dealCards(Deck& draw, Deck& player, Deck& computer, int initialNumCards){
    //function to deal cards from the deck to both player and computer

    draw.shuffle();
    for(int i = 0; i < initialNumCards; i++){
        //deals cards from stack as if you were physically dealing cards
        player.gainCard(draw.takeCard());
        computer.gainCard(draw.takeCard());
    }
}

int main(){
    const int StartingHand = 5;
    Deck DrawPile(true);
    Deck DiscardPile(false);
    Deck Player(false);
    Deck Computer(false);
    //Initialised the 4 deck objects needed
    
    dealCards(DrawPile, Player, Computer, StartingHand);
    Player.printCards("Here are your cards");
    std::cout << std::endl;
    Computer.printCards("These are the computer's cards"); //Test to make sure both hands are being delt correctly

    return 0;
}   
