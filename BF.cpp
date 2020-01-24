#include "BF.h"

BF::~BF()
{
	delete[] resultPermut;
	delete[] permuTab;
	delete[] visited;
}

void BF::brutForce(int v)
{
	int u;
	permuTab[currentSize++] = v;//permuTab jest zawsze tej samej wielkosci, current size to poprwane zapelnienie
	if (currentSize < matrixSize)
	{
		visited[v] = true;// automatycznie sprawdza i!=j
		for (u = 0; u < matrixSize; u++)
			if (!visited[u])
			{
				//std::cout << "edge: " << myGraph->getValueOfEdge(v, u) << std::endl;
				activeCostOfPermut += myGraph->getValueOfEdge(v,u);
				brutForce(u);	//rekurencja
				activeCostOfPermut -= myGraph->getValueOfEdge(v, u);
			}
		visited[v] = false;
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
	currentSize--;//!cofamy siê w tablicy- wracamy poprawiac te ktore do tej pory byly ustalone
}

void BF::intitialBrutForce(Graph* newGraphData)
{
	matrixSize = newGraphData->getNumbOfVerts();
	resultPermut = new int[matrixSize];
	permuTab = new int[matrixSize];
	visited = new bool[matrixSize];
	myGraph = newGraphData;
	for (int i = 0; i < matrixSize; i++)
	{
		visited[i] = false;
	}
	currentSize = 0;
	minCostResult = 99999;
	activeCostOfPermut = 0;
	startVert = 0;
	brutForce(startVert);//zaczynamy od 0 nie tracac ogolnosci zalozen bo i tak chodzi nam o cykl- nie ma poczatku ani konca

}

void BF::printResult()
{
	//sekcja wyswietlania
	for (int i = 0; i < matrixSize; i++) 
		std::cout << resultPermut[i] << "-->";
	std::cout << startVert << std::endl;
	std::cout << "Koszt drogi = " << minCostResult << std::endl;
}

