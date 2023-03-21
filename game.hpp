#include "includes.h"
#include "Deck.hpp"
#include "Card.hpp"
#ifndef GAME
#define GAME

class Game{
private:
    bool skipNextTurn = false;
    Card topCard;
public: 
    Deck DrawPile{true};
    Deck DiscardPile{false};
    Deck Player{false};
    Deck Computer{false};
    //Initilises the deck for the game
    const int StartingHand = 5;

    Game(){
        //class constructor deals cards to both player and computer
        DrawPile.shuffle();
        for(int i = 0; i < StartingHand; i++){
            //deals cards from stack as if you were physically dealing cards
            Player.gainCard(DrawPile.takeCard());
            Computer.gainCard(DrawPile.takeCard());
        }
    }

    bool gameloop(){
        //method to run all the steps in a game of last card
        Player.printCards("This is your hand:");
        topCard = DiscardPile.Cards.back(); //Takes the top card of the discard pile from the stack
        std::cout << "The top card of the discard pile is " << topCard.pictureValue << topCard.suit << std::endl;

        DiscardPile.gainCard(Player.playCard(topCard, false)); //Adds the played card to the top of the discard pile from the stack
        if(DiscardPile.Cards.back().pictureValue == topCard.pictureValue && DiscardPile.Cards.back().suit == topCard.suit){
            Card ToAdd = DrawPile.takeCard();
            Player.gainCard(ToAdd);
            std::cout << "You drew " << ToAdd.pictureValue << ToAdd.suit << std::endl;
        }
        topCard = DiscardPile.Cards.back();

        DiscardPile.gainCard(Computer.playCard(topCard, true)); //Computer plays a card onto the discard pile
        if(DiscardPile.Cards.back().pictureValue == topCard.pictureValue && DiscardPile.Cards.back().suit == topCard.suit){
            Card ToAdd = DrawPile.takeCard();
            Computer.gainCard(ToAdd);
        }
    }
};

#endif 