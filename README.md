# Last Card Game

## Description

Last Card is a classic card game that is written in C++. The game is played with a standard deck of 54 cards (Includes jokers) and includes five power cards: Aces, Jacks, Eights, Twos, and Jokers, each with their own special abilities. The goal of the game is to be the first player to get rid of all their cards.

## Rules

The game is played with the following rules:

### Setup

1. A standard deck of 54 cards is used.
2. Each player is initially dealt 5 cards, and the remaining cards are placed face-down on the table to form the draw pile.
3. The top card of the draw pile is turned face-up and placed next to the draw pile to start the discard pile.

### Gameplay

1. The human player goes first
2. Players take turns one at a time.
3. On their turn, a player can play one card from their hand that matches either the rank or the suit of the top card on the discard pile.
4. If a player cannot play a card, they must draw one card from the draw pile instead.
5. Power cards have special abilities:
    - **Aces**: Change Suit - The player can choose a new suit for the next player to follow.
    - **Jacks & Eights**: Skip next turn - The next player in the turn order is skipped.
    - **Twos**: Pick up 2 - The next player in the turn order must pick up 2 cards from the draw pile and skip their turn. Unless the next player also has a two which can then be chanined to make it +4 which than then be played upon by another 2
    - **Jokers**: Pick up 6 & Change Suit - The next player in the turn order must pick up 6 cards from the draw pile and the player who played the Joker can choose a new suit for the next player to follow.
5. Once a player has only one card remaining they must call "Last Card" in order to play the card on their next turn. If they do not then they must pick up a card.
6. The game continues until one player has played all of their cards and is declared the winner.

### Winning

The first player to get rid of all their cards is declared the winner.

## Power Cards

| Card | Ability                 |
|------|-------------------------|
| Ace  | Change Suit             |
| Jack | Skip next turn          |
| Eight| Skip next turn          |
| Two  | Pick up 2               |
| Joker| Pick up 6 & Change Suit |

## Installation

1. Clone the repository to your local machine.
2. Compile the C++ code using a C++ compiler of your choice.
3. Run the compiled executable to start the game.

## Computer representation of the game

The program represents the cards in the deck as {Number}{Suit} so for example the 3 of spades would be represented as "3S". Jokers are represented as a lowercase j.

### Playing a card
When its is your turn to play a card you will be shown a list of cards in your hand. Such as:
>This is your hand:  
>0: 6C  
>1: 8D  
>2: 4S  
>The top card of the discard pile is 6D

In this example you would play a card by entering either 0 or 1 into the terminal as these are the playable cards in your hand. If the previous card was a two then you will see the additional line.
> It must be a two

If this is the case you can only enter the number which corresponds with a 2, which would chain the twos together to increase the pick up count.

If you play a special card requiring further actions (Ace or Joker) you will then be asked to make your selection in the same way. When chosing the new suit to be played on you will be shown:
>What suit do you wish to change it to?  
>0:H  
>1:S  
>2:D  
>3:C  

You will need to enter a number 0-3 which corresponds with which suit you would like to change the playable suit for future turns to.

### Last Card Calls
When the user has only one card remaining the computer will wait 3 seconds for this to be indicated
You would do this by entering anything (including just pressing enter) into the terminal within the 3 seconds. 
If 3 seconds go by without input then the user would be told that they didn't enter any indication and will result in having one card added to their hand before the next turn.

### Winning and playing again
When you have played all your cards and completed any special actions, such as when the last card is an Ace or Joker you have won the game. 
You will then be greeted with a question asking whether you want to play again. Entering y will result in the beginning of a new game with a new deck of cards.

Entering N will finish the game and close the compiled program.
