#include "Point.h"
#include "Initialiser.h"
#include "ConfigInitiator.h"
#pragma once
class Map
{
	// it is basically an array of Point ptrs, with many functions
private:
	Initialiser* initialiser;	// this is used mainly for getting fullLife and Fee, sth ConfigInitiator doesn't cover
	ConfigInitiator* init;	// mainly used to pass new Troop infos
	int width;	// map width (columns)
	int height;	// map height (rows)
	Point*** map;	// start address of array with Point*
	// 存疑
public:
	Map();	// not used in our game
	Map(Initialiser* initialiser, ConfigInitiator* init);	// pass in Initialiser and ConfigInitiator
	~Map();	// destructor, deletes Point*** map (but in fact not a must, because Map will be created once only in an excution, and it lives until end of program)
	void bindConfigInitiator(ConfigInitiator* init);	// binder
	void bindInitialiser(Initialiser* initialiser);		// binder

	// this opens a .txt file to set up a map (an array of terrain points with two capital points)
	void initMap(ifstream& fin);	// please refer to definition for details

	// saves the map as .txt file
	// accepts GameMediator data as input, this is because saveMap(), unlike initMap(), will not run in main() and thus cannot be bridged to GameMediator directly
	void saveMap(ofstream& fou, bool isTurn, int AMoney, int BMoney);

	// simple getters
	int getWidth();
	int getHeight();

	// get Point at position, accepts coordination, return Point*
	Point* getPointAt(int x, int y);

	// set position, unlike addTo, does insertion only (simple assignment given array index)
	void setPointAt(Point* p);

	// judges whether point p can move to position (destinationX, destinationY), true if can
	bool canTo(Point* p, int destinationX, int destinationY);

	// part of canTo(), used to judge whether position (x, y) is out of the map
	// calling it beforehands can prevent array outOfBound errors
	bool notOutOfBound(int x, int y);

	// this function adds point to one position, returns the was of the occupier before move
	// return value passed to reconstruct orignial terrain at place just left
	// note that this function will add point to position as defined in its x and y
	int addTo(Point* p);	// no side check!

	// this is no more needed
	// void dieFrom(Point* p);	// only applicable to occupiers

	// this function moves point at origin to destination (applies to troops only)
	// input same as for canTo()
	bool moveTo(Point* p, int destinationX, int destinationY); // true if move successful, else false

	// below three are functional
	// engineer only, if called, change engineer to a factory, return false if not enough money, checker included
	int setFactory(Point* p, int money);

	// if called, add to full life, return false if not enough money or life already full, no checker
	int lifeRecover(Point* p, int money);

	// used for factory/capital's troop production
	// money: total money of player, used to judge whether production can proceed
	// side: to which side the troop belongs
	// type: troop type; (destinationX, destinationY): destination position
	int newTroopto(int money, bool side, string type, int destinationX, int destinationY);

	// battle, pass in two Point ptrs: attacker and original (defender)
	// includes randomness, please refer to definition for details
	bool battle(Point* attacker, Point* original);	// true if attacker wins, false if else

	// this should print to screen info and operations available at the point
	string getTerrainInfo(Point* p);
	// Point* p same as getTerrainInfo(), isTurn: if not your Occupiers, you cannot access any information
	string getOccupierInfo(Point* p, bool isTurn);
};
