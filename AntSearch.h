#pragma once
#include "Graph.h"
#include <vector>
#include <algorithm> //random shuffle
#include <iostream>
#include "Ant.h"
#include<cmath>

using namespace std;
class AntSearch
{
public:

	vector<int> makeRandPermut(int size_of_permutation);
	vector<int> bestSolution;
	int result = 1 << 30;//nadpisane zaraz po wywolaniu algorytmu przez randomow¹ drogê
	int matrixSize = 0;
	int variant = 1;// 1QAS 2CAS 3DAS

	float alpha = 1.1; // close to 1 1.1
	float beta = 4.5; // 2-5
	float roPheromone = 0.5; //sta³a parowania
	double qPheromone = matrixSize;//sta³a feromonowa
	int numberOfAnts = matrixSize;
	int numberOfAntIterations = 100;
	Graph* myGraph;

	vector<vector< double > > deltaPheromon;// delta pheromon- sum of feromones of 1 ant iteration
	vector<vector< double > > pheromonMatrix;// pheromones from previous generations
	vector<vector< int > > iterationPermutations;
	double tauZero = 0;

	void antAlgorithm(Graph* newGraphData);
	void antAlgorithm(Graph* newGraphData, int paramNumbOfAnts,int paramVariant,float paramAlpha, float paramBeta, double paramQPheromone, double paramRoPheromone, int paramIterations);

	int getValueOfPath(vector<int> path);
	void printResult();

	void updateDeltaPheromones(vector<int> path);//stosowac przy iteracji jednej mrówki
	void updatePheromones();//stosowaæ po obiegu wszystkich mrowek, parowanie i dodanie delty
	int getRandomStart(int iteration);
	vector<int> antJourney(Ant * Frodo);
	int getNextCity(Ant * Sam);


};

