#include "Point.h"
#include "Map.h"	// avoid self-inclusion, in co-operation with class Map in Point.h
#include <string>
using namespace std;

Point::Point(int x, int y, OccupierPasser* op) : x(x), y(y) {
	this->info = new Pass();
	this->isOcc = true;
	this->info->op = op;
}

Point::Point(int x, int y, TerrainPasser* tp) : x(x), y(y) {
	this->info = new Pass();
	this->isOcc = false;
	this->info->tp = tp;
}

Point::~Point() {
	// delete the Passers
	if (this->isOccupier()) delete this->info->op;
	else delete this->info->tp;
	delete this->info;
}

bool Point::isOccupier() {
	return this->isOcc;
}

string Point::getType() {
	return this->isOccupier() ? this->info->op->getType() : this->info->tp->getType();
}

bool Point::getSide() {
	return this->info->op->getSide();
}

int Point::getAttack() {
	return this->isOccupier() ? this->info->op->getAttack() : 0;
}

int Point::getLife() {
	return this->isOccupier() ? this->info->op->getLife() : 1000;	// very large is impossible
}

int Point::getPortability() {
	return this->isOccupier() ? this->info->op->getPortability() : 0;
}

int Point::getWas() {
	if (this->isOccupier()) return this->info->op->getWas();
	else return this->info->tp->getWas();
}

void Point::setWas(int was) {
	if (this->isOccupier()) this->info->op->setWas(was);
	return;
}

void Point::setLife(int life)
{
	if (!this->isOccupier()) return;
	this->info->op->setLife(life);
}

string Point::getPrint() {
	//if (this->isOccupier()) {
	//	string x = this->info->op->getRepres();
	//	return this->getSide() ? KRED + x + RST : KYEL + x + RST;
	//}
	//else return this->info->tp->getRepres();

	return this->isOccupier() ? ((this->getSide() ? KRED : KYEL) + this->info->op->getRepres() + RST) : this->info->tp->getRepres();
}

bool Point::canEnter(Point* p) {
	if (this->isOccupier()) return (this->getSide() != p->getSide());	// cannot enter if of same side
	else return this->getWas() > 0;	// cannot enter if is Terrain but is hill or sea
}