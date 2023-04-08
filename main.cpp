#include "includes.h"
#include "Card.hpp"
#include "Deck.hpp"
#include "Game.hpp"
#include "VerifyUserInput.hpp"


int main(){
    Game game;
    std::cout << "Welcome to Last Card. The Cards in your hand are {number}{suit} and jokers are represented by j. For more details on the rules visit https://newzealandcasinos.nz/card-games/last-card/" << std::endl;
    std::cout << "In order to win you must call 'Last Card' in order to do this you must type any character into the terminal when you have one card remaining. Penalty for not doing this within 5 seconds +1 card" << std::endl;
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
