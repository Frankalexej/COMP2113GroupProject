#include "ConfigInitiator.h"

ConfigInitiator::ConfigInitiator(Initialiser* init) :init(init) {}

TerrainPasser* ConfigInitiator::passTerrain(int productivity) {
	Terrain* tr;
	if (productivity == -1) tr = this->init->getSea();
	else if (productivity == -2) tr = this->init->getHill();
	else if (productivity > 0) tr = this->init->getLand();
	else tr = NULL;	// other cases not defined

	return new TerrainPasser(tr, productivity);
}

OccupierPasser* ConfigInitiator::passTroop(string type, bool side)
{
	if (type == "sol") return this->passSoldier(side);
	if (type == "eng") return this->passEngineer(side);
	if (type == "lav") return this->passLAV(side);
	if (type == "tank") return this->passTank(side);
	if (type == "fbrk") return this->passFactory(side);
	if (type == "cap") return this->passCapital(side);
	return NULL;
}



OccupierPasser* ConfigInitiator::passSoldier(bool side) {
	return new OccupierPasser(side, this->init->getSoldier());
}

OccupierPasser* ConfigInitiator::passEngineer(bool side) {
	return new OccupierPasser(side, this->init->getEngineer());
}

OccupierPasser* ConfigInitiator::passLAV(bool side) {
	return new OccupierPasser(side, this->init->getLAV());
}

OccupierPasser* ConfigInitiator::passTank(bool side) {
	return new OccupierPasser(side, this->init->getTank());
}

OccupierPasser* ConfigInitiator::passFactory(bool side) {
	return new OccupierPasser(side, this->init->getFactory());
}

OccupierPasser* ConfigInitiator::passCapital(bool side) {
	return new OccupierPasser(side, this->init->getCapital());
}

KeyboardSetting* ConfigInitiator::passKeyboardSetting() {
	return this->init->getKeyboardSetting();
}
