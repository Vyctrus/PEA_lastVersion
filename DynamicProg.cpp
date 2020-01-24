#include "DynamicProg.h"
#include <iostream>

void DynamicProg::DynamicTSP(Graph* newGraphData)
{
	matrixSize = newGraphData->getNumbOfVerts();
	//int** btab;
	//int** wtfrom;
	bitPathSize = (1 << matrixSize);
	btab = new int* [bitPathSize];// 1<<matrixSize  zeby pomiescic informacje w postaci bitowej(1010101)
	wtfrom = new int* [bitPathSize];

	//value:koszt dojscia sciezka zawarta w i, z ostatnim wierzcholkiem w j
	for (int i = 0; i < bitPathSize; i++) {
		btab[i] = new int[matrixSize];
		wtfrom[i] = new int[matrixSize];
		for (int j = 0; j < matrixSize; j++) {
			btab[i][j] =( 1 << 30);//999999 *pseudo nieskonczonosc
			wtfrom[i][j] = 99;
		}
	}

	// 0->1 0->2 0->3... 0->(mSize-1)
	for (int i = 0; i < matrixSize; i++) {
		// 1<<i miasto do,  miasto z(pocz¹tkowe, 0) 
		btab[(1 << i) | 1][i] = newGraphData->getValueOfEdge(0, i);
		wtfrom[(1 << i) | 1][i] = 0;//
		//w 0 0 jest -1
		if (i == 0) {
			btab[(1 << i) | 1][i] = 0;
		}
		
	}


	for (int bitPath = 0; bitPath < bitPathSize; bitPath++) {
		//dla kazdej sciezki (kombinacji 010101)
		for (int ev=0; ev < matrixSize; ev++) {
			//endVert- vert w ktorym konczymy sciezke
			if (bitPath & (1 << ev)) {
				//w sciezce jest koncowy wierzcholek ev, dla kazdego z mozliwych koncow
				for (int i = 0; i < matrixSize; i++) {
					//szukaj wsrod wszystkich ktore jeszcze mozesz dolaczyc
					if (bitPath & (1 << i)) {
						//juz to mamy(tego juz nie dolaczysz)
					}
					else {
						//nie ma i w sciezce a ev jest czyli tutaj nawet ujemne na srodku mog¹ byc
						//		aktualne value + dojscie do i z ev-specyzowane skad			<	value dla wierzcholka i dla sciezki zawierajacej takie miasta
						if ((btab[bitPath][ev] + newGraphData->getValueOfEdge(ev, i)) < btab[bitPath|(1<<i)][i]) {
							//jak to dojscie bedzie optymalne, to je ustaw na optymalne dla tej sciezki
							// bitPath |(1<<i) to sciezka poszerzona o wierzcholek i- blokuje ponowne uzycie, uzytych elementow
							btab[bitPath | (1 << i)][i] = (btab[bitPath][ev] + newGraphData->getValueOfEdge(ev, i));
							wtfrom[bitPath | (1 << i)][i] = ev;
							//dla danego wierzcholka nalezy zapamietac tez skad
						}
					}
				}

			}	
		}
	}


	//zapelniona tablica z optymalnymi dojsciami do poszczegolnych miast
	result = (1 << 30);
	lastVerticle = 0;
	for (int i = 1; i < matrixSize; i++) {// sprawdzic potem czy 1 czy zostawic 0
		//sprawdzenie po wartosciach sciezek zawierajacych wszystkie elementy
		//wraz z dodaniem do nich kosztu powrotu-wyszukanie minimum
		//					"pelne sciezki"				"zapetlenie", powrot
		
		int temp = btab[bitPathSize- 1][i] + (newGraphData->getValueOfEdge(i,0));
		if (temp < result) {
			result = temp;
			lastVerticle = i;
		}	
	}
	//std::cout << "Result : " << result << std::endl;

	int mask = (1 << matrixSize) - 1;//full
	int iter = lastVerticle;
	//int* myTab;
	myTab = new int[matrixSize];
	//myTab[0] = 0;
	//myTab[matrixSize - 1] = iter;
	myTab[0] = 0;
	myTab[matrixSize-1] = iter;
	for (int k = matrixSize - 2; k >0;k--) {
		int previousThanIter= wtfrom[mask][iter];
		myTab[k] = previousThanIter;//myTab od : matrixSize - 1 - k
		//dla poprzednika itera odbierz maske----- wytnij itera z maski
		mask = mask - (1 << iter);
		iter = previousThanIter;
	}
	
	//std::cout << "Path: ";//<< indexQ;
	//for (int i = 0; i < matrixSize; i++) {
	//	std::cout << myTab[i] << "-->";
	//}
	//std::cout << "0\n";


	////destruktor wanna be-->zamiast wywo³ywaæ delete po kazdym wykonaniu algorytmu algorytm sam czysci to czego juz nie potrzebuje
	for (int i = 0; i < bitPathSize; i++) {
		delete[]btab[i];
		delete[]wtfrom[i];
	}
	delete[]btab;
	delete[]wtfrom;
	//delete[]myTab;
}

void DynamicProg::printResult()
{
	std::cout << "Result : " << result << std::endl;

	std::cout << "Path: ";//<< indexQ;
	for (int i = 0; i < matrixSize; i++) {
		std::cout << myTab[i] << "-->";
	}
	std::cout << "0\n";
}

DynamicProg::~DynamicProg()
{
	//destruktor wanna be
	/*for (int i = 0; i < bitPathSize; i++) {
		delete[]btab[i];
		delete[]wtfrom[i];
	}
	delete[]btab;
	delete[]wtfrom;*/
	delete[]myTab;
}

