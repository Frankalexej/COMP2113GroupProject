#include "Map.h"
#include "SaveReadWriter.h"
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;

Map::Map() {}

Map::Map(Initialiser* initialiser, ConfigInitiator* init) :
	initialiser(initialiser), init(init) {}

Map::~Map()
{
	for (int i = 0; i < this->getHeight(); i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

void Map::bindConfigInitiator(ConfigInitiator* init) {
	this->init = init;
}

void Map::bindInitialiser(Initialiser* initialiser)
{
	this->initialiser = initialiser;
}

// map format (saving is the same)

//isTurn AMoney BMoney
//height width
//lines of productivity (matrix-like)
//...
//lines of Occupiers
//(example: x y type side attack life portability)


void Map::initMap(ifstream &fin) {
	SaveReadWriter* saver = new SaveReadWriter(this->initialiser);
	fin >> this->height >> this->width;
	int productivity = 0;
	this->map = new Point ** [this->height];
	for (int i = 0; i < this->height; i++)
	{
		this->map[i] = new Point * [this->width];
	}
	for (int y = 0; y < this->getHeight(); y++)
	{
		for (int x = 0; x < this->getWidth(); x++)
		{
			fin >> productivity;
			this->setPointAt(new Point(x, y, this->init->passTerrain(productivity)));
		}
	}
	string line;
	while (getline(fin, line))
	{
		if (line == "") continue;
		this->addTo(saver->occupierRead(line));
	}
	fin.close();

	// old comment
	// 该函数用来打开一个.txt文件，读取其中保存的地图信息来新建一个地图

	// 我目前的想法是地图、存档用统一格式来保存
	// 第一行写地图的宽、高
	// 后面数行按顺序写每个位点的terrain
	// 再后面每一行写一个位点上的有occupier的point相关信息

	// 另外一个想法就是地图（单纯的地图，不包含老巢位点）单独存放在一个文件夹
	// 然后附带老巢信息的地图另存文件，第一行引入对应地图的文件名
	// 存档做法和存老巢方法一样
}

void Map::saveMap(ofstream& fou, bool isTurn, int AMoney, int BMoney) {
	// save format for saving
	SaveReadWriter* saver = new SaveReadWriter(this->initialiser);
	fou << isTurn << " " << AMoney << " " << BMoney << "\n";
	fou << this->getHeight() << " " << this->getWidth() << "\n";
	for (int y = 0; y < this->getHeight(); y++)
	{
		for (int x = 0; x < this->getWidth(); x++)
		{
			fou << this->getPointAt(x, y)->getWas();
			if (x == this->getWidth() - 1) fou << "\n";
			else fou << " ";
		}
	}
	for (int y = 0; y < this->getHeight(); y++)
	{
		for (int x = 0; x < this->getWidth(); x++)
		{
			Point* p = this->getPointAt(x, y);
			if (p->isOccupier()) fou << saver->occupierWrite(p);
		}
	}
	fou.close();
}


int Map::getWidth() {
	return this->width;
}

int Map::getHeight() {
	return this->height;
}

Point* Map::getPointAt(int x, int y) {
	return this->map[y][x];
}

void Map::setPointAt(Point* p) {
	this->map[p->y][p->x] = p;
	return;
}

bool Map::canTo(Point* p, int destinationX, int destinationY) {
	if (this->notOutOfBound(destinationX, destinationY)) {
		return this->getPointAt(destinationX, destinationY)->canEnter(p);
	}
	else return false;
}

bool Map::notOutOfBound(int x, int y) {
	return (x >= 0) && (x < this->getWidth()) && (y >= 0) && (y < this->getHeight());
}

int Map::addTo(Point* p) {
	int atWas = p->getWas();	// trace back productivity of p's original position
	Point* original = this->getPointAt(p->x, p->y);	// get current position Point (can be Terrain / Occupier)
	p->setWas(original->getWas());	// after this line p and original have the same "was" attribute
	if (original->isOccupier()) {
		bool attackerWin = this->battle(p, original); 
		sleep(3);
		if (!attackerWin) {	// if attacker loses, attacker Point will be assigned to original and then be deleted
			Point* temp = p;
			p = original;
			original = temp;
		}
		system("clear");
	}
	delete original;	// original is always either the terrain or the loser
	this->setPointAt(p);
	return atWas;
}

//void Map::dieFrom(Point* p) {
//	int atWas = p->getWas();
//	Point* np = new Point(p->x, p->y, this->init->passTerrain(atWas));
//	this->setPointAt(np);
//	delete p;
//	return;
//}

bool Map::moveTo(Point* p, int destinationX, int destinationY) {
	if (!this->canTo(p, destinationX, destinationY)) return false;	// if cannot enter, retuen false
	// save old position
	int nx = p->x;
	int ny = p->y;
	// update position
	p->x = destinationX;
	p->y = destinationY;
	// "was" for reconstruction
	int was = this->addTo(p);
	Point* tr = new Point(nx, ny, this->init->passTerrain(was));	// terrain reconstruction
	this->setPointAt(tr);	// put new Point to position
	return true;
}

int Map::setFactory(Point* p, int money)
{
	if (p->getType() != "eng") return money;	// if not engineer
	int fee = this->initialiser->getFactory()->fee;
	if (money < fee) return money;	// if not enough money

	// else
	Point* np = new Point(p->x, p->y, this->init->passFactory(p->getSide()));
	np->setWas(p->getWas());
	delete p;
	this->setPointAt(np);
	return (money - fee);
}

int Map::lifeRecover(Point* p, int money)
{
	int fullLife = this->initialiser->getFullLife(p->getType());
	int fee = this->initialiser->getFee(p->getType());
	if (p->getLife() >= fullLife) return money;
	if (money < fee) return money;

	// else
	p->setLife(fullLife);
	return (money - fee);
}

int Map::newTroopto(int money, bool side, string type, int destinationX, int destinationY)
{
	int fee = this->initialiser->getFee(type);
	if (money < fee) return money;
	addTo(new Point(destinationX, destinationY, this->init->passTroop(type, side)));
	return (money - fee);
}

bool Map::battle(Point* attacker, Point* original)
{
	int attacker_a = attacker->getAttack();
	int attacker_l = attacker->getLife();
	int defender_a = original->getAttack();
	int defender_l = original->getLife();
	srand(time(NULL));	// rendomness seed (present time)
	int fightresult = 0;
	system("clear");
	printf("Battle start: \n");
	int i = 0;
	// fight until one side dies
	while (1)
	{
		++i;
		fightresult = rand() % 2;	// half-half probability
		if (fightresult == 1) {
			defender_l = (defender_l > attacker_a ? (defender_l - attacker_a) : 0);
			printf("Round %d, defender life - %d\n", i, attacker_a);
		}
		else {
			attacker_l = (attacker_l > defender_a ? (attacker_l - defender_a) : 0);
			printf("round %d, attacker life - %d\n", i, defender_a);
		}

		if (attacker_l == 0) {
			printf("Attacker died, attack fail.\n");
			original->setLife(defender_l);
			return false;
		}
		else if (defender_l == 0) {
			printf("Defender died, attack success.\n");
			attacker->setLife(attacker_l);
			return true;
		}
	}
}

string Map::getTerrainInfo(Point* p) {
	KeyboardSetting* keyboard = this->init->passKeyboardSetting();
	string information = "\33[2KPress " + keyboard->nextStep->repres + " for more info.\n\33[2K";
	information += ("Terrain Productivity: " + to_string(p->getWas()) + "\n\33[2K");
	information += p->getType() + "\n\33[2K";
	return information;
}

string Map::getOccupierInfo(Point* p, bool isTurn) {
	KeyboardSetting* keyboard = this->init->passKeyboardSetting();
	string information = "";
	if (p->isOccupier() && (p->getSide() == isTurn)) {
		information += "Life: " + to_string(p->getLife()) + " / " + to_string(this->initialiser->getFullLife(p->getType())) + "\n\33[2K";
		if (p->getType() == "fbrk" || p->getType() == "cap") {
			information += "\x1B[42mProduction Control:\x1B[0m\n\33[2K"
				+ keyboard->soldier->repres + " Soldier $" + to_string(this->initialiser->getSoldier()->fee) + "\n\33[2K"
				+ keyboard->engineer->repres + " Engineer $" + to_string(this->initialiser->getEngineer()->fee) + "\n\33[2K"
				+ keyboard->lav->repres + " LAV $" + to_string(this->initialiser->getLAV()->fee) + "\n\33[2K"
				+ keyboard->tank->repres + " Tank $" + to_string(this->initialiser->getTank()->fee) + "\n\33[2K"
				+ "\x1B[42mProduce troop to shadowed regions\x1B[0m\n\33[2K";
		}
		else information += "\x1B[42mMove troop to shadowed regions\x1B[0m\n\33[2K";
		information += "\x1B[42mStay on Chosen Occupier to";
		information += ((p->getType() == "eng") ? (" Set Factory $" + to_string(this->initialiser->getFactory()->fee) + "\x1B[0m")
			: " Recover Life $" + to_string(this->initialiser->getFee(p->getType())) + "\x1B[0m");
	}

	return information;
}