#include "OccupierTerrain.h"
#pragma once
class Passer
{
private:
	string type;
	// land, sea, hill
	// sol, eng, lav, tank, fbrk, cap
	string repres;	// symbol (probably with escape sequence for on-screnn printing)
public:
	Passer(string type, string repres);
	//simple getters
	string getRepres();
	string getType();
};

