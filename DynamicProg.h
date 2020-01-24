#pragma once
#include "Graph.h"
class DynamicProg
{
	struct myData {
		int value;
		int from;
	};

	int matrixSize;
	int** btab;
	int** wtfrom;
	int bitPathSize;

	int result;
	int lastVerticle;

	int* myTab;
public:
	void DynamicTSP(Graph* newGraphData);
	void printResult();
	~DynamicProg();
};

