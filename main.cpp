#include "includes.h"
#include "Card.hpp"
#include "Deck.hpp"
#include "VerifyUserInput.hpp"


int main(){
    int numTest = verifyInputs("Enter an integer: ");
    std::cout << numTest << std::endl;

    int numTestRange = verifyInputs("Enter an integer between 0 and 10: ", 0,10);
    std::cout << numTestRange << std::endl;
}   
