#include "Symbol.h"
#include "OccupierPasser.h"
#include "TerrainPasser.h"
#include "Initialiser.h"
#pragma once
class ConfigInitiator
{
private:
	Initialiser* init;
public:
	// must pass Initialiser ptr when constructed
	ConfigInitiator(Initialiser* init);

	TerrainPasser* passTerrain(int productivity);	// productivity as identifier, -1 sea, -2 hill, >0 land

	// general troop passer, used when we don't know what troop type will come
	// pass in type and side
	OccupierPasser* passTroop(string type, bool side);

	// specific passers, pass in side
	OccupierPasser* passSoldier(bool side);
	OccupierPasser* passEngineer(bool side);
	OccupierPasser* passLAV(bool side);
	OccupierPasser* passTank(bool side);
	OccupierPasser* passFactory(bool side);
	OccupierPasser* passCapital(bool side);

	// just a passer bridging Initialiser with others that don't have access to the Initialiser
	KeyboardSetting* passKeyboardSetting();
};

