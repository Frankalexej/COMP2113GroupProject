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
This is a simple round-based strategy, player-versus-player game. Setting in a war background, player acts as the commander of a country, who controls the army and factories.  
Once the game starts, it will display a 2D grid map. Each grid has a terrain feature which is not changable. Different types of terrain have different features, one of which could be occupied by troops or buildings (which are called Occupier in game setting) 
Two players could act in turn, including moving troops(maybe starting a battle), healing soldiers/building, gernerating troops, updating factories.  
Note: The player can just choose make one change. i.e. He cannot do two things in one round.  
Players should try his best to manage his army and factories to occupy enermy's capital.

## Rules: 
### New game and load previous record:  
Before starting playing, players can choose to start a new game or reload previous record.  
Whatever, the players need to enter the map/record file name.  
When one playing ends, status of one game can be chosed to store as .txt files.  

### Control:
-use w, s, a, d to move up, down, left, right your cursor respectively.  
-press "e" to confirm.  
-press esc to quit game.  
-press q to step backwards????

### Terrain:
There will be three types of terrains.   
-Land(`地`): normal area that can be occupied with troops or factories. Each land has its peoductivity level. 
-Sea(`海`): forbidden area. 
-Hill(`山`): forbidden area.  
-Note: forbiiden area means it is ineffective to choose its as destination. Nothing can access this area.

### Building:
-Factory(`厰`) is build with an engineer with 1000 money. It has the function of gernerating troops. Factories have an attack point of 1 and life point of 20.  
-Capital(`都`）is the heart of one country(one player). It also has the function of gernerating troops. Capitals have an attack point of 1 and life point of 20.  
More importantly, Once the capital is occupied by this enermy（the other player), you lose.  
-Note: Players can choose to generate new troops in one building's neighbouring area: 3*3 grids whose center is the building.  
-Attack point: the hurt level it can cause to its attacher in each winning round.  
-Life: How many losing round it can bear before its destroy. e.g. Life point is 20. If it is beaten for twenty rounds, it dies.

### Money:
-Money is accumulatively gernerated each round by the sum of the productivity of this player's capital and factories. 
-Two players each will have 200 money initially.  

### Troops:
There are four types of troops with different functions or capabilities.  
-Soldier(`兵`) soldiers have an attack point of 2, a life of 2, and a portability of 1. A soldier costs 100 money to train.  
-Engineer(`工`): engineers have an attack point of 1, a life of 2, and a portability of 1. An engineer costs 150 money to train.  
Enigeeer' s primary function is to build factory (spend money to update `工` to `厰` in the same location)  
-Light Armoured Vehicle(LAV) (`車`): LAVs have an attack point of 4, a life of 3, and a portability of 2 block. One LAV costs 300 money to build. 
-Tank (`炮`): Tanks have an attack point of 6, a life of 5, and a portability of 1. A tank costs 600 money to build.  
-Attack point: the hurt level it can cause to his enermy in each winning round.  
-Life: How many failing round it can bear before death. e.g. Life point is 2. If it is beaten for two rounds, it dies.  
-Portability:  
1: it can move to 3*3 grids whose center is the troops' location.  
2: it can move to 5*5 grids whose center is the troops' location.

### Battle procedure:
In a certain battle, it could have several rounds to cause one's death.  
Each round's result is a random event gernerated by computer.
In rach round, the winer will cause the loser's life decrease by the attack point of the winner.
Once one side's life is 0 (or < 0 in coding level), it dies. The other side wins and occupy this grid.

### Recover Life:
Both Buildings and troops' life level can be recovered to its maximum level with certain cost. 

### Winning condition:
One player occupy the other one's capital.

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
