#pragma once
#include<iostream>
using namespace std;

class Graph//projected as matrix buddy
{
	private:
		int maxValue = 100;//wartosc do createRandomGraph
		int numbOfVerts = 0; //Number of verticles
		int** matrix;
		void setNumbOfVerts(int number);
	public:
		void printGraph();
		Graph(int numberOfVerticles);
		~Graph();
		void createRandomGraph();
		void createRandomGraph(int addSmth);

		void loadGraphFromFile();
		void loadGraphFromFileS(string graphName);
		void saveToFile();

		int getValueOfEdge(int startPoint, int endPoint);
		void setValueOfEdge(int startPoint, int endPoint, int valueToSet);

		int getNumbOfVerts();
		void updateGraph(int newSize);
		
		int getRandomParam();
		void setRandomParam(int setThis);
};

