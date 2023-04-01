#include "includes.h"
#include "Deck.hpp"
#include "Card.hpp"
#ifndef GAME
#define GAME

/* TODO:
    1: Add "Last Card" Calls (done for computer)
    2: Add Play again features
    3: Format output nicer
    4: Clean up unnecessary code
    5: Add chained pick up 2s*/
    
class Game{
private:
    bool skipNextTurn = false;
    bool drawTwo = false;
    bool jokerPlayed = false;
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
        DiscardPile.gainCard(DrawPile.takeCard()); //Take the next card to be first card in the discard pile
        DrawPile.Cards.push_back(Card(4,14));
        DrawPile.Cards.push_back(Card(4,14)); //Adds the two jokers to the deck
        DrawPile.shuffle(); //shuffle the jokers into the deck
        for(int i = 0; i < StartingHand; i++){
            //deals cards from stack as if you were physically dealing cards
            Player.gainCard(DrawPile.takeCard());
            Computer.gainCard(DrawPile.takeCard());
        }
        

        upSuit = DiscardPile.Cards.back().suit;
        topCard = DiscardPile.Cards.back(); //Takes the top card of the discard pile from the stack


    }
    void flipDiscardPile(){
        if(DrawPile.Cards.size() <= 2){ //If the number of cards in the draw pilei s less than or equal to 2 the pile should be turned over
            for(int i = 0; i < DiscardPile.Cards.size() -1; i++){ //leave one card left in the discard pile
                DrawPile.gainCard(DiscardPile.takeCard()); //move cards from discard pile stack to the drawpile in affect flipping the deck
            }
        }
    }
    bool gameloop(){
        //method to run all the steps in a game of last card
        flipDiscardPile();
        
        if(drawTwo){
            Player.gainCard(DrawPile.takeCard());
            Player.gainCard(DrawPile.takeCard());
            std::cout << "You drew 2 cards" << std::endl;
            //Draw two cards if the previous card was a 2
            drawTwo = false;
        }
        else if(jokerPlayed){
            for(int i = 0; i < 6; i++){
                Player.gainCard(DrawPile.takeCard());
                flipDiscardPile(); // If the draw pile becomes less than two cards flip it
            }
            jokerPlayed = false;
        }
        else if(skipNextTurn){
            skipNextTurn = false;
        }
        else{
            Player.printCards("This is your hand:");
            if(upSuit != topCard.suit){
                std::cout << "The suit was changed to " << upSuit << ". ";
            }
            std::cout << "The top card of the discard pile is " << topCard.pictureValue << topCard.suit << std::endl;
            

            DiscardPile.gainCard(Player.playCard(topCard, skipNextTurn, drawTwo, jokerPlayed, upSuit, false)); //Adds the played card to the top of the discard pile from the stack
        
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
        flipDiscardPile(); // If the draw pile becomes less than two cards flip it

        if(drawTwo){
            Computer.gainCard(DrawPile.takeCard());
            Computer.gainCard(DrawPile.takeCard());
            std::cout << "The computer drew two cards" << std::endl;
            drawTwo = false;
        }
        else if(jokerPlayed){
            for(int i = 0; i < 6; i++){
                Computer.gainCard(DrawPile.takeCard()); 
                flipDiscardPile(); // If the draw pile becomes less than two cards flip it

            }
            jokerPlayed = false;
        }
        else if(skipNextTurn){
            skipNextTurn = false;
        }
        else{
            DiscardPile.gainCard(Computer.playCard(topCard, skipNextTurn, drawTwo, jokerPlayed, upSuit, true)); //Computer plays a card onto the discard pile
        
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