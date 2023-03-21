#include "includes.h"
#include "Card.hpp"
#include "Deck.hpp"
#include "Game.hpp"
#include "VerifyUserInput.hpp"


int main(){
    Game game;
    game.Player.printCards("Here are your cards");
    std::cout << std::endl;
    game.Computer.printCards("These are the computer's cards"); //Test to make sure both hands are being delt correctly

    return 0;
}   
