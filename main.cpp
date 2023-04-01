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
    std::cout << std::endl << "Would you like to play again? y/n" << std::endl; //TODO 
    char check;
    std::cin >> check;
    if(check == 'y' || check == 'Y'){ //Check if input was a capital or a lowercase y
        main(); //runs the code again
    }
    else{
      return 0;  
    }
}   
