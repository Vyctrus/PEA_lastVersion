#pragma once
#include "Graph.h";
#include  <vector>
#include <fstream>
#include <algorithm>

//#include <string>
//#include <fstream>
#include <iostream>

using namespace std;

class Simulated_Annealing
{
	vector<int> makeRandPermut(int size_of_permutation);
	int matrixSize = 0;
	vector<int> bestResult;

	//vector<int> permutation;
	//vector<int> nextPermut;

	int result = 1 << 30;
	//int temperature = 1 << 16;

public:
	void runAlgorithm(Graph* newGraphData);
	int runAlgorithmParam(Graph* newGraphData, float paramA,float paramB,float paramC);
	//int TabuSParam(Graph* newGraphData, int paramA, int paramB, float paramC);
	void printResult();
	//~Tabu_Search();
};

