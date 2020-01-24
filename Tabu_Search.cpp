#include "Tabu_Search.h"


//using namespace std;

vector<int> Tabu_Search::makeRandPermut(int size_of_permutation)
{
	vector<int> newRandPermut;
	newRandPermut.reserve(size_of_permutation);
	for (int i = 0; i < size_of_permutation; ++i) {
		newRandPermut.push_back(i);
	}
	random_shuffle(newRandPermut.begin(), newRandPermut.end());
	
	return newRandPermut;
}

void Tabu_Search::tabuS(Graph* newGraphData)
{
	vector<vector< int > > tabuMatrix;
	vector<int> permutation;
	vector<int> nextPermut;
	bestSolution=permutation;
	result = 1 << 30;

	matrixSize= newGraphData->getNumbOfVerts();
	permutation = makeRandPermut(matrixSize);//utworzenie startowej permutacji
	nextPermut = vector<int> (permutation);
	//------------------parametry
	int howMany = 100;// ile razy algorytm sie wywola aby uzyskac rozne wyniki	A 10-1000
	int stamina = matrixSize * 2;//ile sily jeszcze dysponujemy, ilosc krokow jakie jeszcze mozemy robic	B 2-50
	int cadence = matrixSize * 1;//na jak dlugo zostaje zablokowany dany ruch	C 1/4 - 10

	tabuMatrix.resize(matrixSize);//utworzenie macierzy do przechowywania "zakazanych" ruchow
	for (int i = 0; i < matrixSize; ++i) {
		tabuMatrix[i].resize(matrixSize, 0);
	}

	for (int i = 0; i < howMany; ++i) {// howMany=150
		//cout<<"Proba Nr["<<i<<"] ";
		for (int step = 0; step < stamina; ++step) {
			int firstVertSwap = 0;
			int secondVertSwap = 0;
			int nextPermutValue = 1 << 30;

			//Mam jakas permutacje/wynik
			for (int firstPos = 0; firstPos < matrixSize; firstPos++) {
				for (int secondPos = firstPos + 1; secondPos < matrixSize; secondPos++) {

					swap(permutation[firstPos], permutation[secondPos]);//przechodze obok	...A...B... -> ...B...A...
			
					int costOfPath = 0;//liczenie kosztu sciezki po swap'ie
					for (int i = 0; i < matrixSize - 1; i++) {
						//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
						costOfPath += newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
					}
					// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
					costOfPath += newGraphData->getValueOfEdge(permutation[matrixSize - 1], permutation[0]);
					int currValue = costOfPath;


					if (currValue < result) {//jak znalazles cos lepszego- zapamietaj
						result = currValue;
						bestSolution = permutation;
					}

					if (currValue < nextPermutValue) {//jesli krok jest najelpszym do tej pory sasiadem to go zapisz
						if (tabuMatrix[firstPos][secondPos] < step) {//jesli krok jest dozwolony//[secondPos][firstPos]
							nextPermutValue = currValue;
							nextPermut = permutation;
							firstVertSwap = firstPos;//secondPos;//first_position; 
							secondVertSwap = secondPos;//firstPos;// second_position;//
						}
					}

					swap(permutation[firstPos], permutation[secondPos]);// przywroc do poprzedniej permutacji, szukaj po innych sasiadach ...A...B...
				}
			}
			permutation = nextPermut;//przejdz do nastepnego wykonania z kolejnego punktu bazowego
			tabuMatrix[firstVertSwap][secondVertSwap] += cadence;//zablokuj powrot na okreslona kadencje
		}

		/*-------Zakonczenie jednej iteracji algorytmu--------------------*/
		//wyczysc tabuMatrix, zacznij w kolejnym randomowym punkcie
		permutation = makeRandPermut(matrixSize);
		for (int j = 0; j < matrixSize; ++j) {
			for (int k = 0; k < matrixSize; ++k) {
				tabuMatrix[j][k] = 0;
			}
		}
	}

}

void Tabu_Search::tabuStepByStep(Graph* newGraphData)
{
	//-----
	string fileName;
	//cout << "Podaj nazwe pliku do ktorego chcesz zpaisac graf: ";

	fileName = "stepByStep.txt";
	std::fstream graphOutput;

	//graphOutput << numbOfVerts << endl;
	vector<vector< int > > tabuMatrix;
	vector<int> permutation;
	vector<int> nextPermut;
	bestSolution = permutation;
	result = 1 << 30;

	matrixSize = newGraphData->getNumbOfVerts();
	permutation = makeRandPermut(matrixSize);//utworzenie startowej permutacji


	nextPermut = vector<int>(permutation);
	//------------------parametry
	int howMany = 3;// ile razy algorytm sie wywola aby uzyskac rozne wyniki	A 10-1000
	int stamina = matrixSize * 2;//ile sily jeszcze dysponujemy, ilosc krokow jakie jeszcze mozemy robic	B 2-50
	int cadence = matrixSize * 1;//na jak dlugo zostaje zablokowany dany ruch	C 1/4 - 10

	tabuMatrix.resize(matrixSize);//utworzenie macierzy do przechowywania "zakazanych" ruchow
	for (int i = 0; i < matrixSize; ++i) {
		tabuMatrix[i].resize(matrixSize, 0);
	}
	graphOutput.open(fileName, ios::app);	//  | ios::app
	if (graphOutput.good() == true) {
		graphOutput << "Tworze macierz o rozmiarze :" << matrixSize << endl;
		
		graphOutput.close();
	}

	for (int i = 0; i < howMany; ++i) {// howMany=150

		graphOutput.open(fileName, ios::app);	//  | ios::app
		if (graphOutput.good() == true) {
			graphOutput << "Wykonujê g³owny przebieg numer:" << i << endl;
			graphOutput.close();
		}

		//cout<<"Proba Nr["<<i<<"] ";
		for (int step = 0; step < stamina; ++step) {
			int firstVertSwap = 0;
			int secondVertSwap = 0;
			int nextPermutValue = 1 << 30;


			graphOutput.open(fileName, ios::app);	//  | ios::app
			if (graphOutput.good() == true) {
				graphOutput << "Dla permutacji: ";
				for (int dog = 0; dog < matrixSize; dog++) {
					//bestResult
					//newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
					graphOutput << permutation[dog];
				}
				graphOutput << endl;
				graphOutput.close();
			}
			//Mam jakas permutacje/wynik
			for (int firstPos = 0; firstPos < matrixSize; firstPos++) {
				for (int secondPos = firstPos + 1; secondPos < matrixSize; secondPos++) {

					swap(permutation[firstPos], permutation[secondPos]);//przechodze obok	...A...B... -> ...B...A...
					graphOutput.open(fileName, ios::app);	//  | ios::app
					if (graphOutput.good() == true) {
						graphOutput << "Sprwadzam sasiada(swapuje aby go uzyskac): ";
						for (int dog = 0; dog < matrixSize; dog++) {
							//bestResult
							//newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
							graphOutput << permutation[dog];
						}
						graphOutput << endl;
						graphOutput.close();
					}



					int costOfPath = 0;//liczenie kosztu sciezki po swap'ie
					for (int i = 0; i < matrixSize - 1; i++) {
						//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
						costOfPath += newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
					}
					// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
					costOfPath += newGraphData->getValueOfEdge(permutation[matrixSize - 1], permutation[0]);
					int currValue = costOfPath;
					graphOutput.open(fileName, ios::app);	//  | ios::app
					if (graphOutput.good() == true) {
						graphOutput << "Licze obecny koszt permutacji: ";
						graphOutput << currValue << endl;
						graphOutput.close();
					}


					if (currValue < result) {//jak znalazles cos lepszego- zapamietaj
						result = currValue;
						bestSolution = permutation;
						graphOutput.open(fileName, ios::app);	//  | ios::app
						if (graphOutput.good() == true) {
							graphOutput << "Rozwiazanie lepsze niz do tej pory- zapisuje: " << result << endl;
							graphOutput.close();
						}


					}

					if (currValue < nextPermutValue) {//jesli krok jest najelpszym do tej pory sasiadem to go zapisz
						if (tabuMatrix[firstPos][secondPos] < step) {//jesli krok jest dozwolony//[secondPos][firstPos]
							nextPermutValue = currValue;
							nextPermut = permutation;
							firstVertSwap = firstPos;//secondPos;//first_position; 
							secondVertSwap = secondPos;//firstPos;// second_position;//

							graphOutput.open(fileName, ios::app);	//  | ios::app
							if (graphOutput.good() == true) {
								graphOutput << "Aktualizuje najlepszego sasiada: ";
								for (int dog = 0; dog < matrixSize; dog++) {
									//bestResult
									//newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
									graphOutput << permutation[dog];
								}
								graphOutput << endl;
								graphOutput.close();
							}

						}
					}

					swap(permutation[firstPos], permutation[secondPos]);// przywroc do poprzedniej permutacji, szukaj po innych sasiadach ...A...B...

					graphOutput.open(fileName, ios::app);	//  | ios::app
					if (graphOutput.good() == true) {
						graphOutput << "Cofam do poprzedniej permutacji:";
						for (int dog = 0; dog < matrixSize; dog++) {
							//bestResult
							//newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
							graphOutput << permutation[dog];
						}
						graphOutput << endl;
						graphOutput.close();
					}

				}
			}
			permutation = nextPermut;//przejdz do nastepnego wykonania z kolejnego punktu bazowego


			graphOutput.open(fileName, ios::app);	//  | ios::app
			if (graphOutput.good() == true) {
				graphOutput << "Przechodzê do nastêpnej permutacji";
				graphOutput << endl;
				graphOutput << "BLokuje tabu list na parametrach: " << firstVertSwap << " " << secondVertSwap << endl;
				graphOutput << "Zmniejszam liczbe pozostalych krokow" << endl;
				graphOutput.close();
			}

			tabuMatrix[firstVertSwap][secondVertSwap] += cadence;//zablokuj powrot na okreslona kadencje

		}

		/*-------Zakonczenie jednej iteracji algorytmu--------------------*/
		//wyczysc tabuMatrix, zacznij w kolejnym randomowym punkcie
		permutation = makeRandPermut(matrixSize);
		for (int j = 0; j < matrixSize; ++j) {
			for (int k = 0; k < matrixSize; ++k) {
				tabuMatrix[j][k] = 0;
			}
		}
	}


	//-----
}

int Tabu_Search::tabuSParam(Graph* newGraphData, int paramA, int paramB, float paramC)
{
	vector<vector< int > > tabuMatrix;
	vector<int> permutation;
	vector<int> nextPermut;
	bestSolution = permutation;
	result = 1 << 30;

	matrixSize = newGraphData->getNumbOfVerts();
	permutation = makeRandPermut(matrixSize);//utworzenie startowej permutacji
	nextPermut = vector<int>(permutation);

	//------------------parametry
	int howMany = 1*paramA;// ile razy algorytm sie wywola aby uzyskac rozne wyniki	A 10-1000
	int stamina = matrixSize * paramB;//ile sily jeszcze dysponujemy, ilosc krokow jakie jeszcze mozemy robic	B 2-50
	int cadence = matrixSize * paramC;//na jak dlugo zostaje zablokowany dany ruch	C 1/4 - 10

	tabuMatrix.resize(matrixSize);//utworzenie macierzy do przechowywania "zakazanych" ruchow
	for (int i = 0; i < matrixSize; ++i) {
		tabuMatrix[i].resize(matrixSize, 0);
	}

	for (int i = 0; i < howMany; ++i) {// howMany=150
		//cout<<"Proba Nr["<<i<<"] ";
		for (int step = 0; step < stamina; ++step) {
			int firstVertSwap = 0;
			int secondVertSwap = 0;
			int nextPermutValue = 1 << 30;

			//Mam jakas permutacje/wynik
			for (int first_position = 0; first_position < matrixSize; first_position++) {
				for (int second_position = first_position + 1; second_position < matrixSize; second_position++) {

					swap(permutation[first_position], permutation[second_position]);//przechodze obok	...A...B... -> ...B...A...

					int costOfPath = 0;//liczenie kosztu sciezki po swap'ie
					for (int i = 0; i < matrixSize - 1; i++) {
						//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
						costOfPath += newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
					}
					// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
					costOfPath += newGraphData->getValueOfEdge(permutation[matrixSize - 1], permutation[0]);
					int currValue = costOfPath;


					if (currValue < result) {//jak znalazles cos lepszego- zapamietaj
						result = currValue;
						bestSolution = permutation;
					}

					if (currValue < nextPermutValue) {//jesli krok jest najelpszym do tej pory sasiadem to go zapisz
						if (tabuMatrix[second_position][first_position] < step) {//jesli krok jest dozwolony
							nextPermutValue = currValue;
							nextPermut = permutation;
							firstVertSwap = second_position;//first_position; 
							secondVertSwap = first_position;// second_position;//
						}
					}

					swap(permutation[first_position], permutation[second_position]);// przywroc do poprzedniej permutacji, szukaj po innych sasiadach ...A...B...
				}
			}
			permutation = nextPermut;//przejdz do nastepnego wykonania z kolejnego punktu bazowego
			tabuMatrix[firstVertSwap][secondVertSwap] += cadence;//zablokuj powrot na okreslona kadencje
		}


		/*-------Zakonczenie jednej iteracji algorytmu--------------------*/
		//wyczysc tabuMatrix, zacznij w kolejnym randomowym punkcie
		permutation = makeRandPermut(matrixSize);
		for (int j = 0; j < matrixSize; ++j) {
			for (int k = 0; k < matrixSize; ++k) {
				tabuMatrix[j][k] = 0;
			}
		}
	}

	return result;
}



void Tabu_Search::printResult()
{
	std::cout << "Result : " << result << std::endl;

	std::cout << "Path: ";//<< indexQ;
	for (int i = 0; i < matrixSize; i++) {
		//bestResult
		//newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
		std::cout << bestSolution[i] << "-->";
	}
	std::cout << bestSolution[0] << "\n";
}


