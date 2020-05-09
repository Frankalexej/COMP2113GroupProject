#include "SaveReadWriter.h"
// model: "x y type side attack life portability repres"

SaveReadWriter::SaveReadWriter(Initialiser* init) :init(init) {}

Point* SaveReadWriter::occupierRead(string line) {
	this->ins.str(line);
	int x, y, attack, life, portability;
	string type, repres;
	bool side;
	this->ins >> x >> y >> type >> side >> attack >> life >> portability;
	this->ins.clear();
	return new Point(x, y, new OccupierPasser(side, type, attack, life, portability, this->init->getRepres(type)));

	//this->ss.str(line);
	//int x, y, attack, life, portability;
	//string type, repres;
	//bool side;
	//this->ss >> x >> y >> type >> side >> attack >> life >> portability;
	//this->ss.str("");
	//return new Point(x, y, new OccupierPasser(side, type, attack, life, portability, this->init->getRepres(type)));
}

string SaveReadWriter::occupierWrite(Point* p) {
	this->os.str("");
	this->os << p->x << " " << p->y << " " << p->getType() << " " << p->getSide() << " " << p->getAttack() << " " << p->getLife() << " " << p->getPortability() << "\n";
	string toWrite = this->os.str();
	return toWrite;
}