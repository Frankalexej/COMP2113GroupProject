#include "Initialiser.h"
#include "ConfigInitiator.h"
#include "Map.h"
#include "Point.h"
#include "GameListener.h"
#include "ScreenManager.h"
#include <fstream>
#include <iostream>
using namespace std;

int main() {
	Initialiser* initialiser = new Initialiser();
	ConfigInitiator* congfigInitiator = new ConfigInitiator(initialiser);
	Map* map = new Map(initialiser, congfigInitiator);
	ScreenManager* screen = new ScreenManager();
	screen->bindMap(map);
	GameMediator* mediator = new GameMediator();
	GameListener* listener = new GameListener(initialiser->getKeyboardSetting(), screen, map, mediator);

	ifstream fin = listener->listenStartPage();
	fin >> mediator->isTurn >> mediator->AMoney >> mediator->BMoney;
	map->initMap(fin);
	listener->listenMain();
}