#include "includes.h"
#include "Card.hpp"
#include "Deck.hpp"
#include "Game.hpp"
#include "VerifyUserInput.hpp"


int main(){
    Game game;
    bool win = false;
    while(!win){
        win = game.gameloop();
    }
    std::cout << "Would you like to play again?" << std::endl; //TODO 
    return 0;
}   
