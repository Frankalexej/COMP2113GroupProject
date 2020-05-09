#include "ScreenManager.h"
#include <iostream>

ArrowCursor::ArrowCursor() :cursor(CURSOR), x(0), y(0) {}
ArrowCursor::ArrowCursor(bool posCur)
{
	if (posCur) {
		this->cursor = FGRN(CURSOR);
		this->x = 0;
		this->y = 0;
	}
	else ArrowCursor();
}

ArrowCursor::ArrowCursor(int x, int y) :cursor(CURSOR), x(x), y(y) {}

bool ArrowCursor::moveUp(int limit)
{
	return this->y > limit ? this->y-- : false;
}
bool ArrowCursor::moveDown(int limit)
{
	return this->y < limit ? ++this->y : false;
}
bool ArrowCursor::moveLeft(int limit)
{
	return this->x > limit ? this->x-- : false;
}
bool ArrowCursor::moveRight(int limit)
{
	return this->x < limit ? ++this->x : false;
}


ScreenManager::ScreenManager()
{
	this->cursor = new ArrowCursor();
	this->posCur = new ArrowCursor();
}

ScreenManager::~ScreenManager()
{
	delete this->cursor;
	delete this->posCur;
}

void ScreenManager::bindMap(Map* map)
{
	this->map = map;
}


void ScreenManager::refreshMain(bool isTurn, int money) {
	printf("\033[1;1H");
	this->printMap();
	this->printPlayerInfo(isTurn, money);
	this->printPointTerrainInfo();
}

void ScreenManager::refreshShadow(bool isTurn)
{
	this->printShadowedRegion(isTurn);
	printf("\033[%d;%dH", this->posCur->y + 1, 2 * this->posCur->x + 1);
	printf(FGRN(CURSOR));
}


void ScreenManager::printMap() {
	for (int y = 0; y < this->map->getHeight(); y++)
	{
		for (int x = 0; x < this->map->getWidth(); x++)
		{
			cout << this->map->getPointAt(x, y)->getPrint();
		}
		printf("\n");
	}

	printf("\033[%d;%dH", (this->cursor->y) + 1, 2 * (this->cursor->x) + 1);
	cout << this->cursor->cursor;


	//for (int i = 0; i < this->cursor->y; i++)
	//{
	//	for (int j = 0; j < this->map->getWidth(); j++)
	//		cout << this->map->getPointAt(j, i)->getPrint();
	//	printf("\n");
	//}

	//for (int j = 0; j < this->cursor->x; j++)
	//	cout << this->map->getPointAt(j, this->cursor->y)->getPrint();
	//cout << this->cursor->cursor;
	//for (int j = this->cursor->x + 1; j < this->map->getWidth(); j++)
	//	cout << this->map->getPointAt(j, this->cursor->y)->getPrint();
	//printf("\n");

	//for (int i = this->cursor->y + 1; i < this->map->getHeight(); i++)
	//{
	//	for (int j = 0; j < this->map->getWidth(); j++)
	//		cout << this->map->getPointAt(j, i)->getPrint();
	//	printf("\n");
	//}
}

void ScreenManager::printPlayerInfo(bool isTurn, int money) {
	printf("\033[%d;1H", this->map->getHeight() + 1);
	for (int i = 0; i < this->map->getWidth(); i++)
		printf("—");
	printf("\n\33[2K");
	printf("Player %c Money: %d\n", isTurn ? 'A' : 'B', money);
}

void ScreenManager::printPointTerrainInfo() {
	// cutline
	for (int i = 0; i < this->map->getWidth(); i++)
		printf("—");
	printf("\n");

	cout << this->map->getTerrainInfo(this->map->getPointAt(this->cursor->x, this->cursor->y));
}

bool ScreenManager::printShadowedRegion(bool isTurn)
{
	int x = this->cursor->x;
	int y = this->cursor->y;
	Point* p = this->map->getPointAt(x, y);
	if (p->getSide() != isTurn) return false;
	int from = -p->getPortability(), to = p->getPortability();
	if (from == to) return false;

	for (int i = from; i <= to; i++)
	{
		for (int j = from; j <=to; j++)
		{
			printf("\033[%d;%dH", y + j + 1, 2 * (x + i) + 1);

			if (this->map->canTo(p, x + i, y + j)) {
				// move cmd cursor to position
				// note that it should be double counted horizontally
				// because symbols we use in this game all occupy two english chars
				cout << KBLB + this->map->getPointAt(x + i, y + j)->getPrint() + RST;
			}
			else {
				if (this->map->notOutOfBound(x + i, y + j)) cout << this->map->getPointAt(x + i, y + j)->getPrint();
			}
		}
	}
	return true;
}

void ScreenManager::printPointOccupierInfo(bool isTurn) {
	cout << this->map->getOccupierInfo(this->map->getPointAt(this->cursor->x, this->cursor->y), isTurn);
}


bool ScreenManager::moveUp(bool isPosCur) {
	if (isPosCur) {
		int limit = this->cursor->y - this->map->getPointAt(this->cursor->x, this->cursor->y)->getPortability();
		return this->posCur->moveUp(limit > 0 ? limit : 0);
	}
	else return this->cursor->moveUp(0);
}

bool ScreenManager::moveDown(bool isPosCur) {
	int upper = this->map->getHeight() - 1;
	if (isPosCur) {
		int limit = this->cursor->y + this->map->getPointAt(this->cursor->x, this->cursor->y)->getPortability();
		return this->posCur->moveDown(limit < upper ? limit : upper);
	}
	else return this->cursor->moveDown(upper);
}

bool ScreenManager::moveLeft(bool isPosCur) {
	if (isPosCur) {
		int limit = this->cursor->x - this->map->getPointAt(this->cursor->x, this->cursor->y)->getPortability();
		return this->posCur->moveLeft(limit > 0 ? limit : 0);
	}
	else return this->cursor->moveLeft(0);
}

bool ScreenManager::moveRight(bool isPosCur) {
	int upper = this->map->getWidth() - 1;
	if (isPosCur) {
		int limit = this->cursor->x + this->map->getPointAt(this->cursor->x, this->cursor->y)->getPortability();
		return this->posCur->moveRight(limit < upper ? limit : upper);
	}
	else return this->cursor->moveRight(upper);
}

void ScreenManager::followCursor()
{
	this->posCur->x = this->cursor->x;
	this->posCur->y = this->cursor->y;
}

bool ScreenManager::cursorsMeet() {
	return ((this->cursor->x == this->posCur->x) && (this->cursor->y == this->posCur->y));
}

bool ScreenManager::canTo()
{
	return this->map->canTo(this->map->getPointAt(this->cursor->x, this->cursor->y), this->posCur->x, this->posCur->y);
}

void ScreenManager::printEndInfo(bool whoWins)
{
	system("clear");
	printf("Player %c wins! Congratulations!\nPress any button to exit.", whoWins ? 'A' : 'B');
}

void ScreenManager::printEndInfo()
{
	system("clear");
	printf("Both Lose!\nPress any button to exit.");
}
