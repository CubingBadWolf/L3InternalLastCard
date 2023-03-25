#include "includes.h"
#include "Deck.hpp"
#include "Card.hpp"
#ifndef GAME
#define GAME

/* TODO:
    1: Add "Last Card" Calls (done for computer)
    2: Add Play again features
    3: Format output nicer
    4: Clean up unnecessary code*/
    
class Game{
private:
    bool skipNextTurn = false;
    bool drawTwo = false;
    Card topCard;
    char upSuit;

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
        DiscardPile.gainCard(DrawPile.takeCard()); //Take the next card to be first card in the discard pile
        upSuit = DiscardPile.Cards.back().suit;
        topCard = DiscardPile.Cards.back(); //Takes the top card of the discard pile from the stack


    }

    bool gameloop(){
        //method to run all the steps in a game of last card
        if(DrawPile.Cards.size() <= 2){ //If the number of cards in the draw pile is less than or equal to 2 the pile should be turned over
            for(int i = 0; i < DiscardPile.Cards.size() -1; i++){ //leave one card left in the discard pile
                DrawPile.gainCard(DiscardPile.takeCard()); //move cards from discard pile stack to the drawpile in affect flipping the deck
            }
        }
        if(drawTwo){
            Player.gainCard(DrawPile.takeCard());
            Player.gainCard(DrawPile.takeCard());
            std::cout << "You drew 2 cards" << std::endl;
            //Draw two cards if the previous card was a 2
            skipNextTurn = false;
            drawTwo = false;
        }
        else if(skipNextTurn){
            skipNextTurn = false;
        }
        else{
            Player.printCards("This is your hand:");
            std::cout << "The top card of the discard pile is " << topCard.pictureValue << topCard.suit << std::endl;

            DiscardPile.gainCard(Player.playCard(topCard, skipNextTurn, drawTwo, upSuit, false)); //Adds the played card to the top of the discard pile from the stack
        
            if(DiscardPile.Cards.back().pictureValue == topCard.pictureValue && DiscardPile.Cards.back().suit == topCard.suit){
                Card ToAdd = DrawPile.takeCard();
                Player.gainCard(ToAdd);
                DiscardPile.Cards.pop_back(); //remove the duplicate card
                std::cout << "You drew " << ToAdd.pictureValue << ToAdd.suit << std::endl;
            }
            topCard = DiscardPile.Cards.back();

            if(Player.Cards.size() == 0){
                std::cout << "You have won!";
                return true; //checks if a player has no cards left
            }   
        }

        if(drawTwo){
            Computer.gainCard(DrawPile.takeCard());
            Computer.gainCard(DrawPile.takeCard());
            std::cout << "The computer drew two cards" << std::endl;
            skipNextTurn = false;
            drawTwo = false;
        }
        else if(skipNextTurn){
            skipNextTurn = false;
        }
        else{
            DiscardPile.gainCard(Computer.playCard(topCard, skipNextTurn, drawTwo, upSuit, true)); //Computer plays a card onto the discard pile
        
            if(DiscardPile.Cards.back().pictureValue == topCard.pictureValue && DiscardPile.Cards.back().suit == topCard.suit){
                Card ToAdd = DrawPile.takeCard();
                Computer.gainCard(ToAdd);
                DiscardPile.Cards.pop_back(); //remove the duplicate card

                std::cout << "The computer has drawn a card" << std::endl;
            }
            topCard = DiscardPile.Cards.back();

            if(Computer.Cards.size() == 0){
                std::cout << "The computer has won!";
                return true; //checks if a computer has no cards left
            }
            else if(Computer.Cards.size() == 1){
                std::cout << "Computer: LAST CARD" << std::endl;
            }
        }

        std::cout << std::endl; //add a new line in between cards
        return false; //No one has won yet if this is reached
    }
};

#endif 