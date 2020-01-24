#pragma once

#include <string>
#include<iostream>
#include<fstream>
using namespace std;

struct graphData {
	int value;
	int verticleNumb;
	int verticleFrom;
};

class BinaryHeap
{
private:
	//int* myArray;
	graphData* myArray;
	int size;
	int currSize;
	int const sizeInc = 30000;
public:
	BinaryHeap();
	~BinaryHeap();
	void push(int addNumb, int verticle,int verticleFrom);//wstawienie elementu do kopca
	graphData pop(); //usuwanie elementu ze szczytu kopca
	//**usuwanie konkretnej wartosci z kopca
		//**szukanie danej wartosc w kopcu
	void removeValue(int currNumber,int verticle);
	bool searchNumb(int lookNumb, int verticle);
	void sortAdd(int tabIndex);
	void sortRem(int tabIndex);

	void printBT(string sp, string sn, int v);
	void printBT2(string sp, string sn, int v);
	void display3();
	void display2();
	void display();
	void expandArray();
	void reduceArray();

	bool isSizeZero();
	bool isSizeZeroV2();
	int getSize();
	int getCurrSize();

	void createRand(int sizeOfArray);
	void append(int addNumb,int verticle, int verticleFrom);
	void addMin(int newElement);
	int getTopValue();
	static void loadFromFile(string fileName, BinaryHeap * loadedArray);

};



