#include "includes.h"
#include "Card.hpp"
#include "VerifyUserInput.hpp"
//Deck planning

#ifndef DECK
#define DECK
class Deck{
private:
    char Suits[4] = {'H','S','D','C'};
public:
    std::vector<Card> Cards;

    Deck(bool initialDeck){ //constructor, will initilise deck in here if intialDeck is true, else it wont
        if(initialDeck){ //If true then this deck will be the draw pile hence should begin with all cards -jokers
            for(int n = 1; n < 13; n++){
                for(int s = 0; s < 4; s++){
                    Card ToAdd(s,n);
                    Cards.push_back(ToAdd); //Creates a full deck of cards
                }
            }
        }
    }
    
    void shuffle(){ //deck will need a shuffling function.
        std::shuffle(Cards.begin(), Cards.end(),std::random_device());
    }
    Card takeCard(int index){ //Take a card from the deck, remove it and return the card value
        Card ChosenCard = Cards[index]; 
        Cards.erase(Cards.begin()+index); // removes the card at position index, 
        //vector.begin() returns an iterator at the start of the vector by adding index to it we get the position we want
        return ChosenCard;
    }
    Card takeCard(){ //Overloaded function to take from stack.
        Card TopCard = Cards.back(); //Sets top card to be a reference of the last element
        Cards.pop_back(); // Removes the last element of the vector
        return TopCard;
    }

    Card playCard(Card facingCard, bool& skip, int& pick2, bool& havePlay2, bool& pick6, char& nextSuit, bool computer){ //contains references for boolean values for skipping / picking up 2/6 cards next turn
        int playableCards = 0;
        for(Card card: Cards){
            if(card.suit == nextSuit || card.pictureValue == facingCard.pictureValue || card.pictureValue == 'j'){
                playableCards++; //Increases the number of playable cards
            }
        }
        if(playableCards == 0){ //If you don't have any playable cards you must draw a card. If this occurs return the top card of the pile so the game knows no card was played
            if(computer){
                std::cout << "The computer has no cards to play" << std::endl;
                return facingCard;
            }
            std::cout << "You don't have any playable cards" << std::endl;
            return facingCard;
        }
        else{
            if (computer){ //Logic for computer differes slightly from the players logic hence defined differently
                for(int i = 0; i < Cards.size(); i++){
                    if(havePlay2){ //If the computer must play a two it will iterate through vector until it finds a 2. Safetied by fact that it only sets havePlay2 to true if computer does have a two
                        if(Cards[i].pictureValue == '2'){
                            std::cout << "The computer has played " << Cards[i].pictureValue << Cards[i].suit << std::endl;
                            std::cout << "Computer: \"Pick up 2 cards\"" << std::endl;
                            pick2++; //Add to the pick 2 operator
                            havePlay2 = false; //Resets the mustPlay2 flag
                            nextSuit = Cards[i].suit; //Changes the suit to be played on
                            return takeCard(i);
                        }
                    }
                    else if(Cards[i].suit == nextSuit || Cards[i].pictureValue == facingCard.pictureValue || Cards[i].pictureValue == 'j'){
                        std::cout << "The computer has played " << Cards[i].pictureValue << Cards[i].suit << std::endl;

                        switch(Cards[i].pictureValue){
                        case 'A':{ //Computer must pick a random suit to change the suit to
                            std::random_device rng;
                            std::uniform_int_distribution<int> dist(0, 3); //Generates random numbers to pick which suit

                            nextSuit = Suits[dist(rng)];
                            std::cout << "The computer has changed the suit to " << nextSuit << std::endl;
                            return takeCard(i);
                        }
                        case '2': //Next player picks up two cards
                            std::cout << "Computer: \"Pick up 2 cards\"" << std::endl;
                            pick2++; //Add to the pick 2 operator
                            havePlay2 = false; // Resets the mustPlay2 flag
                            nextSuit = Cards[i].suit;
                            return takeCard(i);

                        case '8'://Next player skips their next turn
                            std::cout << "Computer: \"Skip next turn\"" << std::endl;
                            skip = true;
                            nextSuit = Cards[i].suit;
                            return takeCard(i);

                        case 'J': //play again (For 2 players this is the same as an 8)
                            std::cout << "Computer: \"Skip next turn\"" << std::endl;
                            skip = true;
                            nextSuit = Cards[i].suit;
                            return takeCard(i);

                        case 'j':{
                            std::random_device rng;
                            std::uniform_int_distribution<int> dist(0, 3); //Generates random numbers to pick which suit

                            nextSuit = Suits[dist(rng)];
                            std::cout << "The computer has changed the suit to " << nextSuit << ". Pick up 6" << std::endl;
                            pick6 = true; //next player pick up 6
                            return takeCard(i);
                        }
                        default:
                            nextSuit = Cards[i].suit;
                            return takeCard(i);
                    }
                }
            }
            }
            while(true){
                if(havePlay2){ //If the player must play a two it will iterate through vector until it finds a 2. Safetied by fact that it only sets havePlay2 to true if player does have a two
                    std::cout << "It must be a two. ";
                    while (true){
                        int index = verifyInputs("Which card would you like to play?: ", 0 , Cards.size()-1);
                        if(Cards[index].pictureValue == '2'){
                            std::cout << "You played " << Cards[index].pictureValue << Cards[index].suit << std::endl << "You: \"Pick up 2 cards!\"" << std::endl;
                            pick2++; //Add to the pick 2 operator
                            havePlay2 = false;
                            nextSuit = Cards[index].suit;
                            return takeCard(index);
                        }
                        else{
                            std::cout << "That card is not a two" << std::endl;
                        }
                    }
                }
                int index = verifyInputs("Which card would you like to play?: ", 0 , Cards.size()-1);
                if(Cards[index].suit == nextSuit || Cards[index].pictureValue == facingCard.pictureValue || Cards[index].pictureValue == 'j'){
                    std::cout << "You have played " << Cards[index].pictureValue << Cards[index].suit << std::endl;
                    switch(Cards[index].pictureValue){
                        case 'A':{ //Change suit to your chosing
                            int suitNum = verifyInputs("What suit do you wish to change it to?\n0:H\n1:S\n2:D\n3:C\n",0,3);
                            nextSuit = Suits[suitNum];
                            return takeCard(index);
                        }
                        case '2': //Next player picks up to cards
                            std::cout << "You: \"Pick up 2 cards!\"" << std::endl;
                            pick2++; // Add another list of +2
                            havePlay2 = false;
                            nextSuit = Cards[index].suit;
                            return takeCard(index);

                        case '8'://Next player skips their next turn
                            std::cout << "You: \"Skip next turn\"" << std::endl;
                            skip = true;
                            nextSuit = Cards[index].suit;
                            return takeCard(index);

                        case 'J': //play again (For 2 players this is the same as an 8)
                            std::cout << "You: \"Skip next turn\"" << std::endl;
                            skip = true;
                            nextSuit = Cards[index].suit;
                            return takeCard(index);
                        
                        case 'j':{ //Change suit to your chosing
                            int suitNum = verifyInputs("What suit do you wish to change it to?\n0:H\n1:S\n2:D\n3:C\n",0,3);
                            nextSuit = Suits[suitNum]; //change the suit
                            pick6 = true; //make the next player pick up 6
                            std::cout << "You: \"Pick Up 6!\"" << std::endl;
                            return takeCard(index);
                        }
                        default:
                            nextSuit = Cards[index].suit;
                            return takeCard(index);
                    }
                }
                else{
                std::cout << "That card can not go on the facing card" << std::endl;
                }
            }
        }
    }

    void gainCard(Card newCard){ //get passed a card to add to the deck
        Cards.push_back(newCard); // Adds the new card to the deck via stack
    }

    void printCards(std::string message){
        // Prints all the cards in the deck
        std::cout << message << std::endl;
        for (int i = 0; i < Cards.size(); i++){
            std::cout << i << ": " << Cards[i].pictureValue << Cards[i].suit << std::endl;
        }
    }
    
};
#endif