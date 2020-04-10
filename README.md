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
This is a simple round-based strategy, player-versus-player game. Set in a war background, player acts as the commander of a country, who controls the army and factories.  
Once the game starts, it will display a 2D map, consisting of different areas that can be occupied by troops of a country.  
If two different armies (several soldiers) meet (that is, troops of two sides on one area), they can start a battle. The battle result is determined by the troops power (amount and type
of soldiers) and the luck (determined by a random dice). Once all the soldiers in one area are
killed, this area becomes empty and can be occupied by either side.  
With an engineer, players can also choose to build a factory in any empty area, which can generate soldiers in neighboring areas.  
  
The key controlling part of this game is moving troops. In one round, player A can choose to move certain amount of its soldiers 
to neighboring areas, which could lead to a fight or just a change of army/factory arrangement,then player B has the same chance to 
make a decision. The game ends if one beats all troops of its enemy (or if one occupies the capital, depending on the setting).  
Status of one game can be stored as .txt files and when loaded, can be restored.  

## Rules: 
### Control:
-method1: use ↑、↓、←、→ to move your cursor. Once decided, press "enter". Then enter the number of soldiers you want to move and press ↑、↓、←、→ to select a direction or choose to set up a factory, if an engineer is chosen.  
-method2: enter the coordinates of the area you decide to make changes. Then enter the number of soldiers you want to move and enter "left" "right" "up" "down" to select a direction or choose to set up a factory, if an engineer is chosen.  

### Troops:
There are several types of troops with different functions or capabilities.  
-Soldier(兵) soldiers have an attack point of 1, a life of 1, and a portability of 1 block. A soldier costs 100 money to train.  
-Engineer(工): engineers have an attack point of 0.5, a life of 1, and a portability of 1 block. An engineer costs 150 money to train.  
-Light Armoured Vehicle(LAV) (車): LAVs have an attack point of 2, a life of 1.5, and a portability of 2 block. One LAV costs 300 money to build. 
-Tank (炮): Tanks have an attack point of 3, a life of 2, and a portability of 1 block. A tank costs 500 money to build.  
-More could be added accordingly.  

### Factories:
Factories(⌂) are build with an engineer and 1000 money. Players can choose to add new troops in areas within one block from the factories.  
### Terrain:
There will be three types of terrains.   
-Land(■, colored normal): normal area that can be occupied with troops or factories.  
-Sea(■, colored blue): areas for sea troops only (to be designed later).  
-Mountains(■, colored green): forbidden area.  

## Features
Use an stuct array to respent the coordinates of each position.
stuct area should contain the country occpied and soldiers number of different countries(players).

move soldiers: 
once related data are read. if the targeted postion have different countries' troops, call "fight" function.
if not, change the num of soldiers in targeted area.

fight mode:
the dice number is generated randomly. It is a raodom event in this game.
maybe we can cout some strings e.g. "This time, your war material is not enough, bad luck. Combat effectiveness of each soldier:" ...（the random number of dice).
death:?

File input/output
input: map setting and maybe game record
output: to achieve player can read the record of last time and continue working on it.

1. Random game events:
2. Data structures for storing game status
3. Dynamic memory management 
5. Program codes in multiple files

