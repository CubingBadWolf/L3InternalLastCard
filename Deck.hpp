#include "includes.h"
#include "Card.hpp"
#include "VerifyUserInput.hpp"
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

    Card playCard(Card facingCard, bool computer){
        int playableCards = 0;
        for(Card card: Cards){
            if(card.suit == facingCard.suit || card.pictureValue == facingCard.pictureValue){
                playableCards++;
            }
        }
        if(playableCards == 0){
            if(computer){
                std::cout << "The computer has no cards to play" << std::endl;
                return facingCard;
            }
            std::cout << "You don't have any playable cards" << std::endl;
            return facingCard;
        }
        else{
            if (computer){
                for(int i = 0; i < Cards.size(); i++){
                    if(Cards[i].suit == facingCard.suit || Cards[i].pictureValue == facingCard.pictureValue){
                        std::cout << "The computer has played " << Cards[i].pictureValue << Cards[i].suit << std::endl;
                        return takeCard(i);
            }
        }
            }
            while(true){
                int index = verifyInputs("Which card would you like to play?: ",0 , Cards.size());
                if(Cards[index].suit == facingCard.suit || Cards[index].pictureValue == facingCard.pictureValue){
                    std::cout << "You have played " << Cards[index].pictureValue << Cards[index].suit << std::endl;
                    return takeCard(index);
                }
                else{
                std::cout << "That card can not go on the facing card" << std::endl;
                }
            }
        }


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