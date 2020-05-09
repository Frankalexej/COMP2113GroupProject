#include "KeyboardSetting.h"
#include "ScreenManager.h"
#include "GameMediator.h"
#include "Map.h"
#pragma once
class GameListener
{
private:
	// Game Listener can be thought of as the highest controller below main()
	Map* map;
	ScreenManager* screen;
	GameMediator* mediator;
	KeyboardSetting* keyboard;
	// this is the function to listen to keyboard events and returns the ASCII code of the key
	// scanKeyboard is a simple copy&paste from the Internet
	int scanKeyboard();
public:
	// constructor, must pass in all four, for these four, please refer to related files
	GameListener(KeyboardSetting* keyboard, ScreenManager* screen, Map* map, GameMediator* mediator);

	// below 6 are listeners
	ifstream listenStartPage();	// startpage listener, returns the ifstream for reading in map or savings

	void listenQuit();	// quit listener, called when quit key (esc) down

	void listenMain();	// main game listener, imagine it as the first layer of the game

	bool listenPos();	// called when nextStep key (e) down, always called by listenMain(), imagine it as the second layer of the game

	// called when nextStep key (e) down, for factories and capitals only
	// always called by listenPos(), imagine it as the third layer of the game
	// it returns the selected troop to produce, or, if "last", is when formerStep key (q) down
	string listenProduction(); 

	void listenGameEnd(int result);	// called when one player's capital occupied

	int AccMoney();	// 1 A win, 0 continue, -1 B win, -2 both loses
};

