#pragma once
#include "Passer.h"
class TerrainPasser :
	public Passer
{
private:
	int productivity;	// terrain productivity, land positive, sea -1, hill -2
public:
	TerrainPasser(string type, int productivity, string repres);	// constructor with full info set
	TerrainPasser(Terrain* tr, int productivity);	// Terrain as passer

	int getWas();	// pass productivity
};

