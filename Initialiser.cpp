#include "Initialiser.h"
#include "Symbol.h"

Initialiser::Initialiser() {	// default setting
	// land
	this->land = new Terrain("land", LAND);
	//hill
	this->hill = new Terrain("hill", HILL);
	//sea
	this->sea = new Terrain("sea", SEA);

	//soldier
	this->soldier = new Occupier("sol", 2, 2, 1, SOL, 100);
	//engineer
	this->engineer = new Occupier("eng", 1, 2, 1, ENG, 150);
	//lav
	this->lav = new Occupier("lav", 4, 3, 2, LAV, 300);
	//tank
	this->tank = new Occupier("tank", 6, 5, 1, TANK, 600);
	//factory
	this->factory = new Occupier("fbrk", 1, 20, 1, FBRK, 1000);
	//capital
	this->capital = new Occupier("cap", 1, 20, 1, CAP, 1000);

	//keyboadrd settings
	this->keyboard = new KeyboardSetting();
}
Initialiser::Initialiser(bool readFromTxt) {
	if (readFromTxt) {
		// 若需要，请添加从外部文件读取设置参数的代码，否则请删掉这个构造器
	}
	else Initialiser();
}

Initialiser::~Initialiser()
{
	delete land, hill, sea;
	delete soldier, engineer, lav, tank, factory, capital;
	delete keyboard;
}

Terrain* Initialiser::getLand() {
	return this->land;
}
Terrain* Initialiser::getHill() {
	return this->hill;
}
Terrain* Initialiser::getSea() {
	return this->sea;
}

Occupier* Initialiser::getSoldier() {
	return this->soldier;
}
Occupier* Initialiser::getEngineer() {
	return this->engineer;
}
Occupier* Initialiser::getLAV() {
	return this->lav;
}
Occupier* Initialiser::getTank() {
	return this->tank;
}
Occupier* Initialiser::getFactory() {
	return this->factory;
}
Occupier* Initialiser::getCapital() {
	return this->capital;
}

KeyboardSetting* Initialiser::getKeyboardSetting() {
	return this->keyboard;
}

int Initialiser::getFee(string type)
{
	// sol, eng, lav, tank, fbrk, cap
	if (type == "sol") return this->soldier->fee;
	if (type == "eng") return this->engineer->fee;
	if (type == "lav") return this->lav->fee;
	if (type == "tank") return this->tank->fee;
	if (type == "fbrk") return this->factory->fee;
	if (type == "cap") return this->factory->fee;

	return 0;
}

int Initialiser::getFullLife(string type)
{
	// sol, eng, lav, tank, fbrk, cap
	if (type == "sol") return this->soldier->life;
	if (type == "eng") return this->engineer->life;
	if (type == "lav") return this->lav->life;
	if (type == "tank") return this->tank->life;
	if (type == "fbrk") return this->factory->life;
	if (type == "cap") return this->capital->life;

	return 0;
}

string Initialiser::getRepres(string type)
{
	// sol, eng, lav, tank, fbrk, cap
	if (type == "sol") return this->soldier->repres;
	if (type == "eng") return this->engineer->repres;
	if (type == "lav") return this->lav->repres;
	if (type == "tank") return this->tank->repres;
	if (type == "fbrk") return this->factory->repres;
	if (type == "cap") return this->capital->repres;
}
