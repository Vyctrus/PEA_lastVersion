#include "BinaryHeap.h"


BinaryHeap::BinaryHeap()
{
	size = 0;
	currSize = 0;
}


BinaryHeap::~BinaryHeap()
{
	delete[] myArray;
}

void BinaryHeap::push(int addNumb,int verticle, int verticleFrom)
{
	if (size == 0 && currSize == 0) {
		myArray = new graphData[sizeInc];
		size = sizeInc;
		currSize = 1;
		//myArray[0] = addNumb;
		myArray[0].value = addNumb;
		myArray[0].verticleNumb = verticle;
		myArray[0].verticleFrom = verticleFrom;
		return;
	}
	if (currSize == size) {
		expandArray();
	}

	myArray[currSize].value = addNumb;
	myArray[currSize].verticleNumb = verticle;
	myArray[currSize].verticleFrom = verticleFrom;
	sortAdd(currSize);
	++currSize;
	return;


}

graphData BinaryHeap::pop()
{

	if (size == 0 || currSize == 0) {
		graphData tempX;
		tempX.value = 99999;
		tempX.verticleNumb = 99999;
		cout << "rzuca bleeeeedem\n";
		return tempX;
	}
	graphData temp = myArray[0];
	myArray[0] = myArray[currSize - 1];		//przypisujemy najmlodszy lisc do korzenia
	--currSize;
	sortRem(0);		//bo zaczynamy sortowac od korzenia do lisci
	//sortAdd(0);
	if (currSize < (size - sizeInc)) {
		reduceArray();
	}

	return temp;
}

void BinaryHeap::removeValue(int lookNumb, int lookVert)
{
	for (int i = 0; i < currSize; i++) {
		if (myArray[i].value == lookNumb && myArray[i].verticleNumb== lookVert) {
			--currSize;
			myArray[i] = myArray[currSize];
			sortRem(i);
			sortAdd(i);//TUTAJ BYL BLAD
			if (currSize < (size - sizeInc)) {
				reduceArray();
			}
			return;
		}
	}
	return;
}

bool BinaryHeap::searchNumb(int lookNumb, int lookVert)
{
	for (int i = 0; i < currSize; i++) {
		if (myArray[i].value == lookNumb && myArray[i].verticleNumb==lookVert) {
			//std::cout <<lookNumb<< " -Liczba jest w strukturze\n";
			return true;
		}
	}
	//std::cout<<lookNumb << " -Tej liczby nie ma w strukturze\n";
	return false;
}



void BinaryHeap::sortAdd(int tabIndex)	//currSize as first param
{
	if (myArray[tabIndex].value >= myArray[(tabIndex - 1) / 2].value) {//tutaj bylo > zamiast >=
		graphData temp = myArray[(tabIndex - 1) / 2];
		myArray[(tabIndex - 1) / 2] = myArray[tabIndex];
		myArray[tabIndex] = temp;
		if ((tabIndex - 1) / 2 == 0) {
			return;
		}
		sortAdd((tabIndex - 1) / 2);
	}
}

void BinaryHeap::sortRem(int tabIndex)
{
	if ((tabIndex * 2) + 1 >= currSize) {
		return;		//to gwarantuje ze marr[tabindex*2)+1] istnieje
	}
	if (myArray[(tabIndex * 2) + 1].value >= myArray[tabIndex].value) {		//tutaj bylo > zamiast >=
		graphData temp = myArray[tabIndex];
		myArray[tabIndex] = myArray[(tabIndex * 2) + 1];
		myArray[(tabIndex * 2) + 1] = temp;

		sortRem((tabIndex * 2) + 1);
	}

	//nowo dodane, naprawia kopiec wtedy kiedy wartosci sie powatazaja, bez tego jak mamy np dwie 6 jedna zostanie odczytana, druga nie
	if ((tabIndex * 2) + 2 >= currSize) {
		return;		//to gwarantuje ze marr[tabindex*2)+1] istnieje
	}
	if (myArray[(tabIndex * 2) + 2].value >= myArray[tabIndex].value) {		//tutaj bylo > zamiast >=
		graphData temp = myArray[tabIndex];
		myArray[tabIndex] = myArray[(tabIndex * 2) + 2];
		myArray[(tabIndex * 2) + 2] = temp;

		sortRem((tabIndex * 2) + 2);
	}
}

void BinaryHeap::printBT(string sp, string sn, int v)
{ 
	string cr, cl, cp;      // ³añcuchy do znaków ramek
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	string s;
	if (v < currSize)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printBT(s + cp, cr, 2 * v + 2);
		s = s.substr(0, sp.length() - 2);
		cout << s << sn << myArray[v].value << endl;
		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printBT(s + cp, cl, 2 * v + 1);
	}
}

void BinaryHeap::printBT2(string sp, string sn, int v)
{
	string cr, cl, cp;      // ³añcuchy do znaków ramek
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	string s;
	if (v < currSize)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printBT2(s + cp, cr, 2 * v + 2);
		s = s.substr(0, sp.length() - 2);
		cout << s << sn << myArray[v].value <<"("<< myArray[v].verticleNumb<<")"<< endl;
		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printBT2(s + cp, cl, 2 * v + 1);
	}
}

void BinaryHeap::display3()
{
	printBT2("", "", 0);
}

void BinaryHeap::display()
{
	printBT("", "", 0);
}

void BinaryHeap::display2()
{
	for (int i = 0; i < currSize; i++) {
		std::cout << myArray[i].value << " ";
	}
	std::cout << std::endl;
}

void BinaryHeap::expandArray()
{
	//std::cout << "rozszerzam tablice\n";
	size += sizeInc;
	graphData *tempArray = new graphData[size]; //nowa, wieksza tablica
	for (int i = 0; i < currSize; i++) {
		tempArray[i] = myArray[i];
	}
	delete[] myArray;
	myArray = tempArray;
	return;
}

void BinaryHeap::reduceArray()
{
	//std::cout << "pomniejszam tablice\n";
	size -= sizeInc;
	graphData *tempArray = new graphData[size]; //nowa, mniejsza tablica
	for (int i = 0; i < currSize; i++) {
		tempArray[i] = myArray[i];
	}
	delete[] myArray;
	myArray = tempArray;
	return;
}

bool BinaryHeap::isSizeZero()
{
	if (currSize == 0) {
		return true;
	}
	return false;
}

bool BinaryHeap::isSizeZeroV2()
{
	if (size == 0) {
		return true;
	}
	return false;
}

int BinaryHeap::getSize()
{
	return size;
}

int BinaryHeap::getCurrSize()
{
	return currSize;
}

void BinaryHeap::createRand(int sizeOfArray)
{
	for (int i = 0; i < sizeOfArray; i++) {
		push(rand(),69,0);	//tutaj mozna dac rand() % maksymalna liczba		//rand()
	}
}

void BinaryHeap::append(int addNumb,int verticle, int vertFrom)
{
	push(addNumb,verticle, vertFrom);
}

void BinaryHeap::addMin(int newElement){
		push(-newElement,newElement,0);
}
int BinaryHeap::getTopValue()
{
	return pop().verticleNumb;
}
void BinaryHeap::loadFromFile(string fileName, BinaryHeap * loadedHeap)
{
	std::fstream file;
	std::string  dataRow;
	file.open(fileName, std::ios::in);	//fileName = data_in.txt
	if (file.good() == true) {
		getline(file, dataRow);
		std::cout << "Poprawny odczyt z pliku\n";
		int numberOfData = std::stoi(dataRow);
		for (int i = 0; i < numberOfData; i++) {
			getline(file, dataRow);
			loadedHeap->append(std::stoi(dataRow),69,0);
		}
		file.close();
		return;//std::fstream &file
	}
	else {
		std::cout << "Nieudany odczyt z pliku\n";
	}
	return;
}
