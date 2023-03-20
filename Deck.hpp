#include "includes.h"
#include "Card.hpp"
//Deck planning

class Deck{
private:
public:
    std::vector<Card> Cards;
    Deck(bool initialDeck){ //constructor, will initilise deck in here
        if(initialDeck){
            for(int n = 1; n < 13; n++){
                for(int s = 0; s < 4; s++){
                    Card ToAdd(s,n);
                    Cards.push_back(ToAdd); //Creates a full deck of cards
                }
            }
        }
    }

    Deck(){} //Overloads the constructor. Allows for creating a new deck class without creating a new set of cards
    
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
    void RecieveSpecialAction(Card playedCard){ // this will handle what happens when the user recieves a power card

    }

};