#include "includes.h"
#include "Card.hpp"
//Deck planning

#ifndef DECK
#define DECK
class Deck{
private:
public:
    std::vector<Card> Cards;

    Deck(bool initialDeck){ //constructor, will initilise deck in here if intialDeck is true, else it wont
        if(initialDeck){
            for(int n = 1; n < 13; n++){
                for(int s = 0; s < 4; s++){
                    Card ToAdd(s,n);
                    Cards.push_back(ToAdd); //Creates a full deck of cards
                }
            }
        }
    }
    
    void shuffle(){ //deck will need a shuffling function.
        std::random_shuffle(Cards.begin(), Cards.end());
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
    void gainCard(Card newCard){ //get passed a card to add to the deck
        Cards.push_back(newCard);
    }
    void printCards(std::string message){
        std::cout << message << std::endl;
        for (int i = 0; i < Cards.size(); i++){
            std::cout << i << ": " << Cards[i].pictureValue << Cards[i].suit << std::endl;
        }
    }
    void RecieveSpecialAction(Card playedCard){ // this will handle what happens when the user recieves a power card

    }
};
#endif