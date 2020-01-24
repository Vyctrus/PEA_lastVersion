#pragma once
#include "Graph.h"
#include <iostream>

class BranchAndBound
{
	//nie dzia³a!!!!!!!!!!
	//brut force data
	int matrixSize, startVert, minCostResult, activeCostOfPermut, currentSize;
	Graph* myGraph;
	int* resultPermut, * permuTab;
	bool* visited;


	public:
		~BranchAndBound();
		void brutForce(int v);
		void startAlgorithm(Graph* newGraphData);

		int predictPath(int howDeep,int currU);
	
};

