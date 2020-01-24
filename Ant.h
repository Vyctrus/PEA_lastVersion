#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Ant
{
public:
	int myNumber;	//Name of Ant
	int myCity;
	//vector<vector< int > > tabuMatrix;
	vector<bool> visitedByMe;
	Ant(int placeFrom, int number,int vertSize);//PlaceFrom- miasto poczatkowe tej ant
	~Ant();
};

