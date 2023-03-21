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
    return 0;
}   
