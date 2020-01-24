#include "Simulated_Annealing.h"

vector<int> Simulated_Annealing::makeRandPermut(int size_of_permutation)
{
	vector<int> newRandPermut;
	newRandPermut.reserve(size_of_permutation);
	for (int i = 0; i < size_of_permutation; ++i) {
		newRandPermut.push_back(i);
	}
	random_shuffle(newRandPermut.begin(), newRandPermut.end());

	return newRandPermut;
}

void Simulated_Annealing::runAlgorithm(Graph* newGraphData)
{
	vector<int> permutation;
	vector<int> nextPermut;
	bestResult=permutation;
	int temperature = 1e9;// 1 << 30;
	result = 1 << 30;//1 << 30;

	matrixSize = newGraphData->getNumbOfVerts();
	permutation = makeRandPermut(matrixSize);//punkt startowy(losowy)
	nextPermut = vector<int> (permutation);

	float COOLING = 0.95;//0.95;
	int howMany = 70;// ile razy algorytm sie wywola aby uzyskac rozne wyniki	A 10-1000
	int totalSteps = matrixSize*2;//* 3;//ile sily jeszcze dysponujemy, ilosc krokow jakie jeszcze mozemy robic	B 2-50
	//int cadence = matrixSize * 1;//na jak dlugo zostaje zablokowany dany ruch	C 1/4 - 10

	for (int i = 0; i < howMany; ++i) { //wykonania algorytmu
		while (temperature >= 0.1) {
			int numbOfSteps = totalSteps;
			nextPermut = permutation;

			int costOfPermut = 0;//liczenie kosztu sciezki przed swap'em
			for (int i = 0; i < matrixSize - 1; i++) {
				//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
				costOfPermut += newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
			}
			// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
			costOfPermut += newGraphData->getValueOfEdge(permutation[matrixSize - 1], permutation[0]);
			
			//ile najwiecej krokow masz wykonac poki niee  przejdziesz do nastepnego
			for (; numbOfSteps > 0; numbOfSteps--) {
				int firstPos = rand() % matrixSize;   // potencjalne pozycja do zamiany
				int secondPos = rand() % matrixSize;

				swap(nextPermut[firstPos], nextPermut[secondPos]);//sprobuj przejsc dalej

				costOfPermut = 0;//liczenie kosztu sciezki po swap'ie
				for (int i = 0; i < matrixSize - 1; i++) {
					//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
					costOfPermut += newGraphData->getValueOfEdge(nextPermut[i], nextPermut[(i + 1)]);
				}
				// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
				costOfPermut += newGraphData->getValueOfEdge(nextPermut[matrixSize - 1], nextPermut[0]);

				//int diffrence = result - costOfPermut;//roznica rozwiazan najlepszego i aktualnie rozpatrywanego
				int diff = costOfPermut - result;
				if (result>costOfPermut) {//result>costOfPermut	diffrence > 0
					result = costOfPermut;
					bestResult = nextPermut;//przypisz najlepsze rozwiazanie- znalazles teraz
				}
				//diffrence > 0 || (diffrence < 0 && exp(diffrence / temperature) >((double)rand() / RAND_MAX) + 1)
				if (diff < 0 || (diff > 0 && exp((-1)*diff / temperature) >((double)rand() / RAND_MAX) + 1)) {//warunek akceptacji
					
					//jesli znalazles wejscie do lepszego to niech on stanie sie kolejnym punktem rozpatrywania
					//jesli rozwiazanie jest gorsze, ale temperatura spadla wystarczajaco- godzimy sie zaakceptowac wyjscie ktore niekoniecznie jest najlepsze-zeby tylko isc dalej
					permutation = nextPermut;//zaakceptuj przejscie, przejdz
					break;
				}
				else {
					swap(nextPermut[firstPos], nextPermut[secondPos]);//cofnij sie, wykonuj dalej
				}

			}		
			temperature *= COOLING;
		}

		temperature = 1e9;//1<<30;
		permutation = makeRandPermut(matrixSize);
	}
}

int Simulated_Annealing::runAlgorithmParam(Graph* newGraphData, float paramA, float paramB, float paramC)
{
	vector<int> permutation;
	vector<int> nextPermut;
	bestResult = permutation;
	int temperature = 1e9;// 1 << 16;
	result = 1 << 30;

	matrixSize = newGraphData->getNumbOfVerts();
	permutation = makeRandPermut(matrixSize);//punkt startowy(losowy)
	nextPermut = vector<int>(permutation);

	float COOLING = paramC;//0.95;
	int howMany = 1 * paramA;//100;// ile razy algorytm sie wywola aby uzyskac rozne wyniki	A 10-1000
	int totalSteps = matrixSize * paramB;// 3;//ile sily jeszcze dysponujemy, ilosc krokow jakie jeszcze mozemy robic	B 2-50
	//int cadence = matrixSize * 1;//na jak dlugo zostaje zablokowany dany ruch	C 1/4 - 10

	for (int i = 0; i < howMany; ++i) { //wykonania algorytmu
		while (temperature >= 0.1) {
			int numbOfSteps = totalSteps;
			nextPermut = permutation;

			int costOfPermut = 0;//liczenie kosztu sciezki przed swap'em
			for (int i = 0; i < matrixSize - 1; i++) {
				//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
				costOfPermut += newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
			}
			// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
			costOfPermut += newGraphData->getValueOfEdge(permutation[matrixSize - 1], permutation[0]);


			for (; numbOfSteps > 0; numbOfSteps--) {
				int firstPos = rand() % matrixSize;   // potencjalne pozycja do zamiany
				int secondPos = rand() % matrixSize;

				swap(nextPermut[firstPos], nextPermut[secondPos]);//sprobuj przejsc dalej

				costOfPermut = 0;//liczenie kosztu sciezki po swap'ie//to mozna poprawic- liczyc tylko zmiane
				for (int i = 0; i < matrixSize - 1; i++) {
					//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
					costOfPermut += newGraphData->getValueOfEdge(nextPermut[i], nextPermut[(i + 1)]);
				}
				// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
				costOfPermut += newGraphData->getValueOfEdge(nextPermut[matrixSize - 1], nextPermut[0]);

				int diffrence = result - costOfPermut;//roznica rozwiazan najlepszego i aktualnie rozpatrywanego

				if (diffrence > 0) {//result>costOfPermut
					result = costOfPermut;
					bestResult = nextPermut;//przypisz najlepsze rozwiazanie jakie znalazles teraz(omija rozwiazania lepsze ktore s¹ dalej?)
				}
				if (diffrence > 0 || (diffrence < 0 && exp(diffrence / temperature) >((double)rand() / RAND_MAX) + 1)) {//warunek akceptacji
					//jesli znalazles wejscie do lepszego to niech on stanie sie kolejnym punktem rozpatrywania
					//jesli rozwiazanie jest gorsze, ale temperatura spadla wystarczajaco- godzimy sie zaakceptowac wyjscie ktore niekoniecznie jest najlepsze-zeby tylko isc dalej
					permutation = nextPermut;//zaakceptuj przejscie, przejdz
					break;
				}
				else {
					swap(nextPermut[firstPos], nextPermut[secondPos]);//cofnij sie, wykonuj dalej
				}

			}


			temperature *= COOLING;
		}

		temperature = 1e9;//1 << 16;
		permutation = makeRandPermut(matrixSize);
	}

	//cout << "Result: " << result<<"\n";
	return result;
}



void Simulated_Annealing::printResult()
{
	std::cout << "Result : " << result << std::endl;

	std::cout << "Path: ";//<< indexQ;
	for (int i = 0; i < matrixSize; i++) {
		//bestResult
		//newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
		std::cout << bestResult[i] << "-->";
	}
	std::cout << bestResult[0]<<"\n";
}
