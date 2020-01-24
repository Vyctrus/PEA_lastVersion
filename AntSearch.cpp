#include "AntSearch.h"
#include "Ant.h"
#include<ctime> //srnad
#include <iostream>

vector<int> AntSearch::makeRandPermut(int size_of_permutation)
{
	vector<int> newRandPermut;
	newRandPermut.reserve(size_of_permutation);
	for (int i = 0; i < size_of_permutation; ++i) {
		newRandPermut.push_back(i);
	}
	random_shuffle(newRandPermut.begin(), newRandPermut.end());

	return newRandPermut;
}

void AntSearch::antAlgorithm(Graph* newGraphData)
{
	//Inicjalizacja
	myGraph = newGraphData;
	matrixSize = myGraph->getNumbOfVerts();	//to sie nie zmieni w trakcie iteracji nzm
	numberOfAnts = matrixSize;//nzm
	qPheromone = matrixSize;//nzm
	numberOfAntIterations = 100;//nzm

	bestSolution = makeRandPermut(matrixSize);//utworzenie startowej permutacji //permutation;
	result = getValueOfPath(bestSolution);
	tauZero =(double) matrixSize / (double)result;

	pheromonMatrix.resize(matrixSize);
	for (int i = 0; i < matrixSize; i++) {
		pheromonMatrix[i].resize(matrixSize, tauZero);
	}
	//Wszedzie jest ju¿ feromon w macierzy feromonów zgodnie ze wskazaniami Dorigo


	for (int i = 0; i < numberOfAntIterations; i++) {
		cout << "ANT ITERATION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-----------: " << i << "\n";
		deltaPheromon.resize(matrixSize);//to ma sie wyzerowac
		for (int j = 0; j < matrixSize; j++) {
			deltaPheromon[j].resize(matrixSize, 0);
		}
		iterationPermutations.resize(numberOfAnts);//tutaj pzechowywane bêd¹ œcie¿ki z jednej iteracji pokolenia mrowek
		for (int j = 0; j < numberOfAnts; j++) {
			iterationPermutations[j].resize(numberOfAnts, 0);
		}

		for (int singleAnt=0; singleAnt < numberOfAnts; singleAnt++) {
			// tworzymy mrowke, ktora wie juz skad idzie, ma swoj¹ tabu liste, ma swoj numer
			Ant *myAnt = new Ant(getRandomStart(singleAnt),singleAnt,matrixSize);

			//MrowkaIdzie
			//MrówkaWybieraSobieDrogê w oparciu o graf- widocznosc, feromony zostawione przez przodków

			iterationPermutations[singleAnt]= antJourney(myAnt);//tutaj------------ tu bylo i zamiast singleAnt

			//Koniec drogi
			//wynikiem tego jest jakas permutacja zapisana do Iterationpermutation[i]

			//Wrzuæ feromony do deltaPheromons
			updateDeltaPheromones(iterationPermutations[singleAnt]);

			//Jeœli œcie¿ka któr¹ znalazlas < result to bestSolution=sciezka, result=new result
			if (getValueOfPath(iterationPermutations[singleAnt]) < result) {
				result = getValueOfPath(iterationPermutations[singleAnt]);
				bestSolution = iterationPermutations[singleAnt];
			}
			delete myAnt;
		}
		//Dodaj delta feromony do glownej macierzy feromonów
		//Paruj feromony
		updatePheromones();
		
		//wyczysc deltaPheromones po pokoleniu
		deltaPheromon.resize(matrixSize);
		for (int j = 0; j < matrixSize; j++) {
			deltaPheromon[j].resize(matrixSize, 0);
		}
		//If wszystkie mrowki znalazly to samo->break zkaoncz, iterationPermutation sprawdzaj kolejne elementy z pierwszym rekordem

		//for (int check = 1; check < numberOfAnts; check++) {//mrowki
		//	for (int check2 = 0; check2 < matrixSize; check2++) {
		//		if (iterationPermutations[0][check2] != iterationPermutations[check][check2]) {
		//			goto exit;
		//		}
		//	}
		//}
		////Zakoncz algorytm- wszystkie mrowki znalazly jedna droge
		//break;
		//exit:;

		
	}

	cout << "Result= " << result << "\n" ;
}


int AntSearch::getValueOfPath(vector<int> path)
{
	//zlozonosc N
	int res = 0;
	for (int k = 0; k < path.size() - 1; k++) {

		res += myGraph->getValueOfEdge(path[k], path[k + 1]);//tutaj cos bardoz nie tak
	}
	res += myGraph->getValueOfEdge(path[path.size()-1], path[0]);
	return res;
}

void AntSearch::printResult()
{
	std::cout << "Result : " << result << std::endl;

	std::cout << "Path: ";//<< indexQ;

	for (int i = 0; i < bestSolution.size() ; i++) {
		//result += newGraphData->getValueOfEdge(path[i], path[i + 1]);
		cout<<bestSolution[i]<<"-->";
	}
	std::cout << bestSolution[0]<<"\n";
}

void AntSearch::updateDeltaPheromones(vector<int> path)
{
	//QAS
	for (int i = 0; i < path.size()-1; i++) {
		deltaPheromon[path[i]][path[i+1]] +=  qPheromone/ (double)myGraph->getValueOfEdge(path[i], path[i + 1]);// wariant QAS
	}
	deltaPheromon[path[(path.size()) -1]][path[0]] += qPheromone/(double)myGraph->getValueOfEdge(path[(path.size()) -1], path[0]);

	//CAS
	//for (int i = 0; i < path.size() - 1; i++) {
	//	deltaPheromon[path[i]][path[i + 1]] += qPheromone / (double)getValueOfPath(path);
	//}
	//deltaPheromon[path[(path.size()) - 1]][path[0]] += qPheromone / (double)getValueOfPath(path);

	//DAS
	//for (int i = 0; i < path.size() - 1; i++) {
	//	deltaPheromon[path[i]][path[i + 1]] += qPheromone ;
	//}
	//deltaPheromon[path[(path.size()) - 1]][path[0]] += qPheromone;
}

void AntSearch::updatePheromones()
{
	//z z definicji wzoru tau_ij(t+1)= ro* tau_ij(t) + delta tau_ij(t,t+1)
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			pheromonMatrix[i][j] *= roPheromone;
			pheromonMatrix[i][j] += deltaPheromon[i][j];			
		}
	}
}

int AntSearch::getRandomStart(int iteration)
{
	return iteration;
	srand(iteration + time(NULL));
	return rand()%matrixSize;

}


vector<int> AntSearch::antJourney(Ant* Frodo)
{
	//wystartuj z miasta poczatkowego
	///podroz bedzie trwac matrixSize bo tyle jest miast
	Frodo->visitedByMe[Frodo->myCity] = true;//wpisujemy miasto mrowki na tabu liste
	vector<int> antPermut;
	antPermut.reserve(matrixSize);
	antPermut.push_back(Frodo->myCity);
	for (int i = 1; i < matrixSize; i++) {// miaasto[0] jest juz na antPermut
		antPermut.push_back(getNextCity(Frodo));
	}
	return antPermut;
}

int AntSearch::getNextCity(Ant* Sam)
{
	//cout << "Jestem tu\n";
	//1.wiem ile jest i gdzie rozlozonego feromonu (globalna pheromonMatrix, pheromonMatrix to tau_ij
	//2. widze(mrowka nie jest slepa) jakie s¹ odleglosci (GrapData) 1/getValueofEdge_ij to eta_ij
	//jestem w miescie Sam.myCity
	srand(time(NULL) + Sam->myNumber);
	double probX = (double)rand() / (double)RAND_MAX; //liczba z przedzialu 0-1

	//Metoda pól prawdopodobieñstw
	vector<double> probabilities;
	probabilities.resize(matrixSize);
	double mianownik = 0;
	for (int i = 0; i < matrixSize; i++) {
		if (Sam->visitedByMe[i] == true) {
			//juz odwiedzony wierzcholek jest na tabu liscie
			mianownik += 0;
		}
		else {
			if (myGraph->getValueOfEdge(Sam->myCity, i) == 0) {
				mianownik += 1000000;
				cout << "A problem :0\n";
			}
			else {
				mianownik += (
					pow((pheromonMatrix[Sam->myCity][i]), alpha)
					* pow(1.0 / myGraph->getValueOfEdge(Sam->myCity, i), beta)
					);
			}	
		}
	}


	for (int i = 0; i < matrixSize; i++) {
		if (Sam->visitedByMe[i] == true) {
			//juz odwiedzony wierzcholek jest na tabu liscie
			probabilities[i] = 0;
		}
		else {
			//zagrozenie ze sie wywali jak jakas krawedz bêdzie rowna zero
			if (myGraph->getValueOfEdge(Sam->myCity, i) == 0) {
				probabilities[i] = 1;//kiedy jest zero, przejdz automatycznie
			}
			else {
				probabilities[i] = (
					pow((pheromonMatrix[Sam->myCity][i]), alpha)
					* pow(1.0 / myGraph->getValueOfEdge(Sam->myCity, i), beta)
					) / mianownik;
			}		
		}	
	}
	//mam prawdopodobienstwa przejsc w postaci vectora gdzie dla vec[0] czyt prawd. przejscia do miasta 0 jest równe vec[0].value
	//pamietac aby po przejsciu zmienic miasto myCity!!!

	int iter = 0;
	double sum = probabilities[iter];
	while (sum < probX) {
		iter++;
		sum += probabilities[iter];
	}

	Sam->visitedByMe[iter] = true;//przenioslem sie do kolejnego miasta
	Sam->myCity = iter;

	return iter;
}
