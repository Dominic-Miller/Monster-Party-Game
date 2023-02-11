# Monster-Party-Game
This repository contains code for a 2D single player monster party game. 
This code uses DMA to keep track of alive players and monsters effectively.

***************************************************************************************************************************

In this game players are spawned in on a team that moves together to fight against a random amount of monster parties.
"X" on the map represents your parties current location, you can move around with WASD.
"M"s on the map are the location of all monster parties which when stepped on initiates a fight against a random number of monsters.
"T"s on the map are treasure chests. Once landed on a random amount of treasure will be added to your parties total and the chest will be removed.
"R"s on the map are traps and once landed on have a 50% chance of awarding treasure or damaging the whole team.

***************************************************************************************************************************

There are 5 files in this repository:
board.h contains code for the declaration of a board class which keeps track of the visuals of the game.
board.cpp contains the implementation of the board class which keeps track of the visuals of the game.
game.h contains code for the declaration of a character, party, monster, and monster party class.
game.cpp contains the implementation of all these classes and keeps track of memory using DMA.
main.cpp contains the driver file for the game which implements all above classes.
