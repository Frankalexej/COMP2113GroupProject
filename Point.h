#include <string>
#include "OccupierPasser.h"
#include "TerrainPasser.h"
using namespace std;
#pragma once

class Map;	// this is to overcome the problem of self-inclusion

class Point
{
	// this represents one point on the map
	// we didn't choose to organise different types of Points as a family of classes
	// because C++ doesn't support polymorphism well
	// problems may occur when objects of differnt sizes are put into the same array
private:
	// common variables
	bool isOcc;	// specifies whether it is an Occupier or not (false if is Terrain)

	// union can save some memory, because a Point is either an Occupier or a Terrain
	union Pass
	{
		OccupierPasser* op;	// occupier only
		TerrainPasser* tp;	// terrain only
	};
	Pass* info;
	Map* map;
public:
	int x;	// horizontal position
	int y;	// vertical position

	Point(int x, int y, OccupierPasser* op);	// new an occupier
	Point(int x, int y, TerrainPasser* tp);		// new a terrain
	~Point(); // destructer, to handle deletion of Passers

	bool isOccupier();	// returns isOcc

	string getType();	// returns type
	string getPrint();	// returned string includes side colour (Red for A, Yellow for B)
	bool getSide();	// if a point Terrain calls it, it would cause problem
	// simple getters
	int getAttack();
	int getLife();
	int getPortability();
	int getWas();	// pass was if isOccupier, else pass productivity

	void setWas(int was);	// sets the was property of Occupiers
	void setLife(int life); // sets the life property of Occupiers

	bool canEnter(Point* p);	// return whether p can enter this Point (this)
};

