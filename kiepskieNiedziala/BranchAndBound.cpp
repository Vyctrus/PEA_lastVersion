#include "BranchAndBound.h"
#include "BinaryHeap.h"

BranchAndBound::BranchAndBound::~BranchAndBound()
{
	delete[] resultPermut;
	delete[] permuTab;
	delete[] visited;
}

void BranchAndBound::BranchAndBound::brutForce(int v)
{
	int u;
	permuTab[currentSize++] = v;//permuTab jest zawsze tej samej wielkosci, current size to poprwane zapelnienie
	if (currentSize < matrixSize)
	{
		visited[v] = true;
		for (u = 0; u < matrixSize; u++)
			if (!visited[u])
			{
				activeCostOfPermut += myGraph->getValueOfEdge(v, u);
				//ile krawedzi potrzeba jeszcze?
				//matrixSize - (currentSize + 1) - 1
				//+ predictPath(matrixSize - (currentSize + 1) - 1, u)
				if (activeCostOfPermut + predictPath(matrixSize - (currentSize + 1) - 1, u) <= minCostResult) {
					brutForce(u);	//rekurencja
				}
				//w tym miejscu wiemy ile wartosc ma w wybranym wierzcholku drzewa-wystarczy podmienic brutForce na idz dalej			
				activeCostOfPermut -= myGraph->getValueOfEdge(v, u);//cofa dany krok
			}
		visited[v] = false;//przywraca mozliwosc odwiedzania tego wierzcholka w kolejnych szukaniach
	}
	else
	{
		//mamy juz wszystkie wierzcholki
		activeCostOfPermut += myGraph->getValueOfEdge(v, startVert);//laczymy kolo
		if (activeCostOfPermut < minCostResult)
		{
			minCostResult = activeCostOfPermut;
			for (u = 0; u < currentSize; u++)
				resultPermut[u] = permuTab[u];
		}
		activeCostOfPermut -= myGraph->getValueOfEdge(v, startVert);
	}
	currentSize--;//!!!!!!!!!cofamy siê w tablicy- wracamy poprawiac te ktore do tej pory byly ustalone
}

void BranchAndBound::BranchAndBound::startAlgorithm(Graph* newGraphData)
{
	matrixSize = newGraphData->getNumbOfVerts();
	resultPermut = new int[matrixSize];
	permuTab = new int[matrixSize];
	visited = new bool[matrixSize];
	//W = new int* [n];
	myGraph = newGraphData;
	std::cout << "Drukuje dane wczytanego grafu:" << std::endl;
	myGraph->printGraph();
	for (int i = 0; i < matrixSize; i++)
	{
		visited[i] = false;
	}
	currentSize = 0;
	minCostResult = 99999;
	activeCostOfPermut = startVert = 0;
	brutForce(startVert);

	//sekcja wyswietlania
	for (int i = 0; i < matrixSize; i++) std::cout << resultPermut[i] << " ";
	std::cout << startVert << std::endl;
	std::cout << "d = " << minCostResult << std::endl;
}

int BranchAndBound::predictPath(int howDeep,int currU)
{
	//currU to ostatni zbadany wierzcholek

	//najmniejsze dojscie do wolnych wierzcholkow
	int bridge = 99999;
	int temp;
	for (int i = 0; i < matrixSize; i++) {
		if (!visited[i]) {//jesli wierzcholek jest wolny
			temp = myGraph->getValueOfEdge(currU, i);
			if (bridge > temp) {
				bridge = temp;
			}
		}
	}

	BinaryHeap* myHeap = new BinaryHeap;
	for (int i = 0; i < matrixSize; i++) {
		if (!visited[i]) {//jesli wierzcholek jest wolny
			for (int j = 0; j < matrixSize; j++) {
				if (!visited[i] && i!=j) {
					myHeap->addMin(myGraph->getValueOfEdge(i, j));
					//wrzuc do wora, usun najwieksze
				}
			}
		}
	}
	//zsumuj rzeczy z wora
	int tempSum = 0;
	for (int i = 0; i < howDeep; i++) {
		tempSum += myHeap->getTopValue();
	}
	delete myHeap;

	//dodanie najkrotszej drogi powrotnej
	int bridge2 = 99999;
	int temp2;
	for (int i = 0; i < matrixSize; i++) {
		if (!visited[i]) {//jesli wierzcholek jest wolny
			temp2 = myGraph->getValueOfEdge(i, 0);
			if (bridge2 > temp2) {
				bridge2 = temp2;
			}
		}
	}

	return bridge+bridge2+tempSum;
}


