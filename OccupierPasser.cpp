#include "OccupierPasser.h"

OccupierPasser::OccupierPasser(bool side, string type, int attack, int life, int portability, string repres) :
	isASide(side), attack(attack), life(life), portability(portability), Passer(type, repres), was(0) {}

OccupierPasser::OccupierPasser(bool side, Occupier* oc) :
	isASide(side), attack(oc->attack), life(oc->life), portability(oc->portability), Passer(oc->type, oc->repres), was(0) {}

bool OccupierPasser::getSide() {
	return this->isASide;
}

int OccupierPasser::getAttack() {
	return this->attack;
}

int OccupierPasser::getLife() {
	return this->life;
}

void OccupierPasser::setLife(int life) {
	this->life = life;
	return;
}

int OccupierPasser::getPortability() {
	return this->portability;
}

int OccupierPasser::getWas() {
	return this->was;
}

void OccupierPasser::setWas(int was) {
	this->was = was;
	return;
}