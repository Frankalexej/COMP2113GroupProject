#pragma once
#include "Passer.h"
class OccupierPasser :
	public Passer
{
	// extends Passer
private:
	bool isASide;	// true for Player A, false for Player B
	int attack;		// attack value
	int life;		// life value

	// how far it can move (now only 0, 1, or 2)
	// 0 for cannot move, 1 for can move to 8 neighbouring positions, 2 for 15 positions in the region
	int portability;
	int was;
	// this is used to store info about the terrain it occupies
	// positive = land, 0 = newly produced occupier (not used), -1 = sea, -2 = hill
public:
	OccupierPasser(bool side, string type, int attack, int life, int portability, string repres);	// constructor with full info set
	OccupierPasser(bool side, Occupier* oc);	// Occupier as passer

	bool getSide(); // get side, true if A, else B
	int getAttack();	// get attack value
	int getLife();	// get life value
	void setLife(int life);	// set life value (for updating)
	int getPortability();	// get portability

	int getWas();	// pass was
	void setWas(int was);	// sets was
};

