#include "includes.h"
#include "Card.hpp"
#include "Deck.hpp"
#include "Game.hpp"
#include "VerifyUserInput.hpp"


int main(){
    Game game; //Initilises the game
    std::cout << "Welcome to Last Card. The Cards in your hand are {number}{suit} (example: the 3 of spades would be represented as 3S) and jokers are represented by j. For more details on the rules visit https://newzealandcasinos.nz/card-games/last-card/" << std::endl;
    std::cout << "In order to win you must call 'Last Card' in order to do this you must enter any character into the terminal when you have one card remaining. Penalty for not doing this within 3 seconds: +1 card" << std::endl;
    //Prints all the neccesary starting information.

    bool win = false;
    while(!win){
        win = game.gameloop(); //Runs the game
    }
            
    std::cout << std::endl << "Would you like to play again? y/n" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Resets the input buffer

    while(true){
        std::string check;
        std::cin >> check;
        if(check == "y" || check == "Y"){ //Check if input was a capital or a lowercase y
            main(); //runs the code again
        }
        else if(check == "n" || check == "N"){ //Check if input was a capital or lowercase n
            return 0;
        }
        else{
            std::cout << "You did not enter y or n, Please enter y or n" << std::endl; //restart the loop if neither y or n were entered
        }
    }
}   


