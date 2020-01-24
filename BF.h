#pragma once

#include "Graph.h"
#include <iostream>
class BF
{
	//brut force data
	int matrixSize, startVert, minCostResult, activeCostOfPermut, currentSize;     
	Graph* myGraph;
	int* resultPermut, * permuTab;
	bool* visited;


public:
	~BF();
	void brutForce(int v);
	void intitialBrutForce(Graph* newGraphData);
	void printResult();

};

