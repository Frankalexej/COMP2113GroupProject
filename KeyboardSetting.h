#include <string>
using namespace std;
#pragma once
struct Key
{
	Key(string repres, char keyCode) :repres(repres), keyCode(keyCode) {}
	string repres;	// name to be presented on screen
	char keyCode;	// code for listeners
};

struct KeyboardSetting {
	KeyboardSetting() {	//default setting, reading from external config file not implemented, not important
		this->exit = new Key("Esc", 27);
		this->formerStep = new Key("q", 'q');
		this->nextStep = new Key("e", 'e');
		this->skip = new Key("f", 'f');


		this->cursorUp = new Key("w", 'w');
		this->cursorDown = new Key("s", 's');
		this->cursorLeft = new Key("a", 'a');
		this->cursorRight = new Key("d", 'd');

		//this->moveNorth = new Key("8", '8');
		//this->moveNorthEast = new Key("9", '9');
		//this->moveEast = new Key("6", '6');
		//this->moveSouthEast = new Key("3", '3');
		//this->moveSouth = new Key("2", '2');
		//this->moveSouthWest = new Key("1", '1');
		//this->moveWest = new Key("4", '4');
		//this->moveNorthWest = new Key("7", '7');
		//this->center = new Key("5", '5');

		this->soldier = new Key("z", 'z');
		this->engineer = new Key("x", 'x');
		this->lav = new Key("c", 'c');
		this->tank = new Key("v", 'v');
	}

	Key* exit, * formerStep, * nextStep, * skip;
	Key* cursorUp, * cursorDown, * cursorLeft, * cursorRight;	// cursor movement
	// troop movement keys discarded after implementation of listenPos() layer
	// Key* moveNorth, * moveNorthEast, * moveEast, * moveSouthEast, * moveSouth, * moveSouthWest, * moveWest, * moveNorthWest, * center;	// Occupier movement
	Key* soldier, * engineer, * lav, * tank;
};