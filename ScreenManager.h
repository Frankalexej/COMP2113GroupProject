#include "Map.h"
#include <string>
#pragma once

class ArrowCursor
{
	// this is the arrow cursor on game screen (only used in main game page)
public:
	string cursor;
	// position
	int x;
	int y;

	ArrowCursor();	// default, at (0, 0)
	ArrowCursor(bool posCur);	// used to new posCur (used in listenPos() layer of GameListener)
	ArrowCursor(int x, int y);	// specifies posision, not used

	// cursor movement, limit specifies the border
	// because posCur's border is not the whole map's border, therefore it should also be considered
	bool moveUp(int limit);
	bool moveDown(int limit);
	bool moveLeft(int limit);
	bool moveRight(int limit);
};

class ScreenManager
{
	// Not considering StartPage and Quit because they are simple in printing
private:
	Map* map;
public:
	ArrowCursor* cursor;
	ArrowCursor* posCur;

	ScreenManager();
	~ScreenManager();	// destructor, not needed because this will also live until end of program
	void bindMap(Map* map);	// must bind Map before usage

	void refreshMain(bool isTurn, int money);	// called after cursor move or troop operations
	void refreshShadow(bool isTurn);	// called in listenPos() layer, does partial refreshing

	void printMap();	// print map, including cursor
	void printPlayerInfo(bool isTurn, int money);	// prints side and money
	void printPointTerrainInfo();	// prints terrain productivity (and type, but also including Occupier types)
	bool printShadowedRegion(bool isTurn);	// prints accessible regions
	void printPointOccupierInfo(bool isTurn);	// prints available detailed info and operations at the point

	// true if move successful, else false
	// if pass in true, movement for posCur, if false, movement for cursor
	bool moveUp(bool isPosCur);
	bool moveDown(bool isPosCur);
	bool moveLeft(bool isPosCur);
	bool moveRight(bool isPosCur);

	void followCursor();	// update posCurs to position of cursor when called, because posCur is always based on cursor

	bool cursorsMeet();		// judge if cursor and posCur are at the same position

	bool canTo();	// judges if point at cursor's position can go to posCur's position

	// Game End
	void printEndInfo(bool whoWins);	// print result
	void printEndInfo();	// print result when both lose
};