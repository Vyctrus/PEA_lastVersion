#include "Ant.h"

Ant::Ant(int placeFrom, int number, int vertSize)
{
	this->visitedByMe.resize(vertSize,false);
	this->myNumber = number;
	this->myCity = placeFrom;
}

Ant::~Ant()
{
	this->myCity = NULL;
	this->myNumber = NULL;
	this->visitedByMe.clear();
}
