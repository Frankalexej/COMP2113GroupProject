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

### Money:
Money is accumulated each round according to the productivity in the areas occupied by the player.  Each player will have 500 money at the beginning.  

### Troops:
There are several types of troops with different functions or capabilities.  
-Soldier(`兵`) soldiers have an attack point of 1, a life of 1, and a portability of 1 block. A soldier costs 100 money to train.  
-Engineer(`工`): engineers have an attack point of 0.5, a life of 1, and a portability of 1 block. An engineer costs 150 money to train.  
-Light Armoured Vehicle(LAV) (`車`): LAVs have an attack point of 2, a life of 1.5, and a portability of 2 block. One LAV costs 300 money to build. 
-Tank (`炮`): Tanks have an attack point of 3, a life of 2, and a portability of 1 block. A tank costs 500 money to build.  
-More could be added accordingly.  

### Factories:
Factories(`⌂`) are build with an engineer and 1000 money. Players can choose to add new troops in areas within one block from the factories.  
### Terrain:
There will be three types of terrains.   
-Land(`■, colored normal`): normal area that can be occupied with troops or factories.  
-Sea(`■, colored blue`): areas for sea troops only (to be designed later).  
-Mountains(`■, colored green`): forbidden area.  

## Features
Presumably, we use objects to represent the troops, factories and terrains. They all derive from one base class.  
Use a two-dimensional array of the base class to respent map (each element, or point, represents one area).  

The base class (`Point`) has `int x` and `int y`, representing the coordinates of this point, and a `string representation`, defining the representation of this point on the map. It has a `toLocation()` method, which updates the responsive location in the map.  

`Terrain` derives from `Point`, it has a string attribute (`string type`), defining the type of terrain; it also has a `int productivity` attribute that provides information about how much money this area can generate each round. It also has a `toStorage()` method, which returns a storage object to an occupier (a troop or a factory) for storing the original type of terrain and its productivity.  

`Occupier` derives from `Point` as well, it has a `Storage was` attribute, storing the terrain information of the area it occupies. It also has a `range` attribute, denoting the range it covers (ex. 1 for soldiers, engineers, tanks and factories, 2 for LAVs). In addition, it has `attackPoint` (refers to max amount of troops produceable by factories) and `life` attributes. It has `enter()` and `leave()` method that deals with the occupier moving to and leaving one point. It has a virtual `die()` method that requires further implementation accordingly.  

`Troop` derives from `Occupier`. It has an additional attribute `int number`, denoting the number of troops on one point (note that only one type of troops is allowed on one point). It has `moveTo(int x, int y)` method, which changes the `x` and `y`, restores the original terrain from `was`, calls `leave()` and goes to the new point by calling `toLocation()`. There is also an `initiateBattle(int x, int y)`, which is called automatically upon the order of moving to a point with an `Occupier`. This method calls a `BattleManager` to draw a random number representing luck and calculate the total attack power of this troop and passes it to the `receiveBattle(type enemyAttackPower)` method of the enemy `Occupier`. Upon receiving the attack, the `receiveBattle()` does the same as the former and passes the `enemyAttackPower` to the `die()` method of the initiater, and then calls `die()` of itself. (**this requires further designing**). Note that `die()` of Troops counts down the `number` first and when `number = 0`, calls `leave()`.  

`Factory` derives from `Occupier` as well. It has a series `makeX()` methods for producing new troops in the neiboring regions. It should also implement a `die()` method.  

#### Random game settings and events:
Random productiviy of areas and luck in battles.  

#### Data structures for storing game status: 
Maps, points, etc. as mentioned above.  

#### Dynamic memory management: 
The map size will be determined by the argument stored in .txt files and will be created dynamically. 
Unused data will be `delete`d to free the memory. 

#### File input/output
-input: maps and game status records (from archive at last exit time).  
-output: to archive game status when exiting or upon choose "save".  

#### Program codes in multiple files: 
Different functions and classes will be packed in different .cpp files. 
