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

	float alpha = 1.1; // close to 1 1.1
	float beta = 4.5; // 2-5
	float roPheromone = 0.5; //sta³a parowania
	double qPheromone = matrixSize;//sta³a feromonowa
	int numberOfAnts = matrixSize;
	int numberOfAntIterations = 100;
	Graph* myGraph;

	vector<vector< double > > deltaPheromon;// delta pheromon- sum of feromones of 1 ant iteration
	vector<vector< double > > pheromonMatrix;// pheromones from previous generations, sohuld be started by tauZero= matrixSize(antNumber)/length of ?random permutation?- nie jestem pewny

	//vector<int> permutation;//place where(best) path can be stored
	vector<vector< int > > iterationPermutations;
	double tauZero = 0;

	void antAlgorithm(Graph* newGraphData);
	int getValueOfPath(vector<int> path);
	void printResult();

	void updateDeltaPheromones(vector<int> path);//stosowac przy iteracji jednej mrówki
	void updatePheromones();//stosowaæ po obiegu wszystkich mrowek, parowanie i dodanie delty
	int getRandomStart(int iteration);
	vector<int> antJourney(Ant * Frodo);
	int getNextCity(Ant * Sam);

};

