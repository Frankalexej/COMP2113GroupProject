#include "TerrainPasser.h"

TerrainPasser::TerrainPasser(string type, int productivity, string repres) :
	productivity(productivity), Passer(type, repres) {}

TerrainPasser::TerrainPasser(Terrain* tr, int productivity) :
	productivity(productivity), Passer(tr->type, tr->repres) {}

int TerrainPasser::getWas() {
	return this->productivity;
}