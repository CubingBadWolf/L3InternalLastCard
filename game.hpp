#include "includes.h"
#include "Deck.hpp"
#include "Card.hpp"
#ifndef GAME
#define GAME

/* TODO:
    1: Clean up unnecessary code
   */
    
class Game{
private:
    const int StartingHand = 5;
    Card twos[4] = {Card(0,2), Card(1,2), Card(2,2), Card(3,2)}; //Create an array of the valid 2s

    bool skipNextTurn = false;
    int drawTwo = 0;
    bool mustPlayTwo = false;
    bool jokerPlayed = false;
    char upSuit;
    //Defines all the flags needed for determining the special actions cards do

    Card topCard;

    bool MultiThread_TimedInput(){
        //Uses multithreading to handle last card input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Resets the input buffer so it doesn't auto detect input when there isn't any
        std::atomic<bool> inputReceived(false);
        std::atomic<bool> timeoutReached(false);
        //Sets up flags for the two criteria
        std::thread inputThreadObj(&Game::InputThread, this, std::ref(inputReceived)); //Sets up the seperate thread for managing inputs

        auto startTime = std::chrono::steady_clock::now(); //Sets up the timeout counter
        std::chrono::duration<int> timeout(3);
        bool called;
        while (true) {
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - startTime); //Counts the time elapsed since the check started
            if(elapsedTime >= timeout){
                called = false;
                std::cout << "You did not enter any indication you have last card, enter any key to continue" << std::endl;
                break;
            }
            else if(inputReceived.load()){ //If input was recieved before timeout set called to true
                called = true;
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); //Prevents high CPU useage by taking a short break in between checks
        }
        inputThreadObj.join(); //rejoins the other thread
        return called;
    }

    void InputThread(std::atomic<bool>& inputDetected){ //The logic for the seperate thread defined in the function above
        char c;
        c = std::getchar(); //takes the next char in the input stream and waits if there is none.
        inputDetected.store(true); //stores true if input is reached
    }

    void flipDiscardPile(){
        if(DrawPile.Cards.size() <= 2){ //If the number of cards in the draw pile is less than or equal to 2 the pile should be turned over
            for(int i = 0; i < DiscardPile.Cards.size() -2; i++){ //leave one card left in the discard pile
                DrawPile.gainCard(DiscardPile.takeCard()); //move cards from discard pile stack to the drawpile in effect flipping the deck
            }
            std::cout << "Due to low amount of cards in the draw pile the discard pile has been flipped to create a new draw pile" << std::endl;
        }
    }
public: 
    Deck DrawPile{true};
    Deck DiscardPile{false};
    Deck Player{false};
    Deck Computer{false};
    //Initilises the decks for the game
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

    bool gameloop(){
        //method to run all the steps in a game of last card
        flipDiscardPile();
        //Players Turn:
        if(drawTwo != 0){ //check if the player must draw 2 cards. (Computer played a 2)
            for (Card two : twos){
                vector<Card>::iterator flag = find(Player.Cards.begin(),Player.Cards.end(), two); //defines a interator to where the struct is located
                if(flag != Player.Cards.end()){ //if the interator is present then player can play a two on top
                    mustPlayTwo = true;
                    goto PlayPlayer; //goto where the player can play

                }
            }
            if(!mustPlayTwo){ //Play can't play a 2 on top hence must pick up
                for(int i = 0; i < drawTwo*2; i++){ //if multiple plus twos were played you must pick up chained pluses
                    Player.gainCard(DrawPile.takeCard());
                }
                std::cout << "You drew " << drawTwo*2 << " cards" << std::endl;
                //Draw two cards if the previous card was a 2
                drawTwo = 0; 
            }
        }
        else if(jokerPlayed){ //Computer played a joker so player must pick up 6.
            for(int i = 0; i < 6; i++){
                Player.gainCard(DrawPile.takeCard());
                flipDiscardPile(); // If the draw pile becomes less than two cards flip it
            }
            jokerPlayed = false;
        }
        else if(skipNextTurn){ //Computer played a J or 8 so the next turn was skipped
            skipNextTurn = false;
        }
        else{
            mustPlayTwo = false; //Resets the mustPlayTwo flag

            PlayPlayer: //Label where goto leads to if the player can play a 2.
            Player.printCards("This is your hand:");
            if(upSuit != topCard.suit){
                std::cout << "The suit was changed to " << upSuit << ". "; //When the suit was changed the suit available =/= the suit of the top card, so inform the player
            }
            std::cout << "The top card of the discard pile is " << topCard.pictureValue << topCard.suit << std::endl;
            
            DiscardPile.gainCard(Player.playCard(topCard, skipNextTurn, drawTwo, mustPlayTwo, jokerPlayed, upSuit, false)); //Adds the played card to the top of the discard pile from the stack, Pass through all flags
        
            if(DiscardPile.Cards.back().pictureValue == topCard.pictureValue && DiscardPile.Cards.back().suit == topCard.suit){ //If the card played is equal to the previous top card it means the player did not play
                Card ToAdd = DrawPile.takeCard();
                Player.gainCard(ToAdd); //Makes the player pick up
                DiscardPile.Cards.pop_back(); //remove the duplicate card
                std::cout << "You drew " << ToAdd.pictureValue << ToAdd.suit << std::endl;
            }
            topCard = DiscardPile.Cards.back(); //Resets the top card

            if(Player.Cards.size() == 0){
                std::cout << "You have won!";
                return true; //checks if a player has no cards left
            }
            else if(Player.Cards.size() == 1){
                if(MultiThread_TimedInput()){ //Runs the multi threading
                    std::cout << "You: \"Last card!\"" << std::endl;
                }
                else{
                    std::cout << "Pick up a card" << std::endl;
                    Card ToAdd = DrawPile.takeCard();
                    Player.gainCard(ToAdd); //Makes the player pick up a card
                    std::cout << "You drew " << ToAdd.pictureValue << ToAdd.suit << std::endl;
                }
            }
        }
        flipDiscardPile(); // If the draw pile becomes less than two cards flip it

        if(drawTwo != 0){ //Checks if the player previously played a 2 and whether the computer must now play a two or pick up
            for (Card two : twos){
                vector<Card>::iterator flag = find(Computer.Cards.begin(),Computer.Cards.end(), two); //defines a interator to where the class is located and checks if a 2 is in the class
                if(flag != Computer.Cards.end()){ //if the interator is present 
                    mustPlayTwo = true;
                    goto playComp; //goto where the computer can play because it can play a 2 on a 2
                }
            }
            if(!mustPlayTwo){//If you can not play a two
                for(int i = 0; i < drawTwo*2; i++){ //if multiple plus twos were played you must pick up chained pluses
                    Computer.gainCard(DrawPile.takeCard());
                }
                std::cout << "The computer drew " << drawTwo*2 << " cards" << std::endl;
                drawTwo = 0; 
            }
        }
        else if(jokerPlayed){ //If the player played a joker previously
            for(int i = 0; i < 6; i++){
                Computer.gainCard(DrawPile.takeCard()); 
                flipDiscardPile(); // If the draw pile becomes less than two cards flip it
            }
            jokerPlayed = false;
        }
        else if(skipNextTurn){ //If the player played a 8 or J
            skipNextTurn = false;
        }
        else{ // If the player can play normally
            mustPlayTwo = false; //Reset plustwo flag
            playComp: //goto line 119 directs here if a computer can play over a 2 {MustPlayTwo} would still be true
            DiscardPile.gainCard(Computer.playCard(topCard, skipNextTurn, drawTwo, mustPlayTwo, jokerPlayed, upSuit, true)); //Computer plays a card onto the discard pile pass through all flags
        
            if(DiscardPile.Cards.back().pictureValue == topCard.pictureValue && DiscardPile.Cards.back().suit == topCard.suit){ //Checks if the computer couldn't play a card, uses the fact that we returned the top card in deck.hpp if this was the case
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
                std::cout << "Computer: \"LAST CARD\"" << std::endl; //Inform the play the computer has one card remaining
            }
        }

        std::cout << std::endl; //add a new line in between cards
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); //wait 500ms before starting next turn, adds a delay for user legibility
        return false; //No one has won yet if this is reached
    }
};

#endif 