#include <string>
using namespace std;
#pragma once
// these two are almost always used together, therefore are they included in the same file
// these structs only act as a info-package, therefore no methods
struct Occupier
{
	Occupier(string type, int attack, int life, int portability, string repres, int fee) :
		type(type), attack(attack), life(life), portability(portability), repres(repres), fee(fee) {}
	string type;	// type, please refer to Passer.h, line 8 for details
	// below three same as described in OccupierPasser.h line 8-13
	int attack;
	int life;
	int portability;
	string repres;	// symbol (probably with escape sequence for on-screnn printing)
	int fee;	// price, used for factory/capital's production and lifeRecovery
};

struct Terrain
{
	Terrain(string type, string repres) : type(type), repres(repres) {}
	string type;	// type, please refer to Passer.h, line 7 for details
	string repres;	// repres, same as above in line 15
};