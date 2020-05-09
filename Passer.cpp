#include "Passer.h"
#include <string>
using namespace std;

Passer::Passer(string type, string repres) :type(type), repres(repres) {}

string Passer::getRepres() {
	return this->repres;
}

string Passer::getType() {
	return this->type;
}