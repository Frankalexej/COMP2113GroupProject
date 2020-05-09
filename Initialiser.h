#include "OccupierTerrain.h"
#include "KeyboardSetting.h"
#pragma once
class Initialiser
{
	// could be set using .txt configuration file
	// now only set config
private:
	Terrain* land, * hill, * sea;
	Occupier* soldier, * engineer, * lav, * tank, * factory, * capital;
	KeyboardSetting* keyboard;
public:
	Initialiser();	// initialisation without reading
	Initialiser(bool readFromTxt);	//initialisation with reading, not implemented, not important
	~Initialiser();

	// simple getters
	Terrain* getLand();
	Terrain* getHill();
	Terrain* getSea();

	Occupier* getSoldier();
	Occupier* getEngineer();
	Occupier* getLAV();
	Occupier* getTank();
	Occupier* getFactory();
	Occupier* getCapital();

	KeyboardSetting* getKeyboardSetting();

	// search getters, must run through all 6 Occupuier types (and 3 Terrain types)
	int getFee(string type);
	int getFullLife(string type);
	string getRepres(string type);
	// no setter, never set after initialisation
};

