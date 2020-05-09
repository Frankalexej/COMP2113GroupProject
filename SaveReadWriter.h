#include "Point.h"
#include "Initialiser.h"
#include <sstream>
#pragma once
class SaveReadWriter
{
	// this class is used for transformation between saving data and Occupier point
	// note that this is for Occupiers only
	// terrain is much simpler but require more complicated positioning techniques
	// because terrain info is listed as lines of space-separated ints, whose position needs inference from the whole map
private:
	istringstream ins;
	ostringstream os;
	//stringstream ss;
	Initialiser* init;	// just used to pass repres
public:
	// model: "x y type side attack life portability"
	SaveReadWriter(Initialiser* init);
	Point* occupierRead(string line);	// raed a line in saving and reconstruct a point
	string occupierWrite(Point* p);	// transform point to string
};

