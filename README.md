# COMP2113GroupProject
This is the repo for COMP2113 Group Project (group 157)
## Group Member
Tan Lihui
Yuan Jing
## Requirements (temporal)
1. Generation of random game sets or events
2. Data structures for storing game status
3. Dynamic memory management
4. File input/output (e.g., for loading/saving game status)
5. Program codes in multiple files
6. Proper indentation and naming styles
7. In-code documentation

-Commit comment should not be empty and should be written sensibly.

-For each function, comments on “what it does”, “what the inputs are” and “what the outputs are” are needed.

-You may use any of the C/C++ libraries.
## Game Description
It is a simple turn-based strategy, player versus player game. Set in a war background, one user acts one country and own its army and factories. 
Once the game start, it will display a 2D map, consists of different areas occupied by different countries. every area is occupied by several amount of soldiers belonging to one country. 
If two different armies (several soldiers) meet, they have to start a fight. The fighting result is determined by the amount of soldiers and the luck(determined by a dice), which will lead to deaths of soldiers. Once all the soldiers in one area are killed, this area will occupied by its emery (who won this fight). 
Player can still choose to build a factory in one empty and possessed area, which can generate soldiers in neighbor areas.
The key part of this game is moving troops by users. In one turn, player A can choose to move certain amount of its soldiers to neighbor areas, which could lead to a fight or just a change of army arrangement, and then player B has the same chance to make a decision. The game ends if one occupy all areas.
The status of this play can be stored and then next time, players can continue to work on its previous status.

## Features
xxx
