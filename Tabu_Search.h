#pragma once
#include "Graph.h"
#include  <vector>
#include <fstream>
#include <algorithm>

//#include <string>
//#include <fstream>
#include <iostream>
//#include <list>
//#include <math.h>

using namespace std;

class Tabu_Search
{
	vector<int> makeRandPermut(int size_of_permutation);

	//vector<vector< int > > tabuMatrix;
	vector<int> bestSolution;
	//vector<int> permutation;
	//vector<int> nextPermut;
	int result = 1 << 30;

	int matrixSize=0;
	//int** btab;
	//testy

	
public:
	void tabuS(Graph* newGraphData);
	void tabuStepByStep(Graph* newGraphData);
	int tabuSParam(Graph* newGraphData, int paramA, int paramB, float paramC);
	void printResult();
	//~Tabu_Search();
};

