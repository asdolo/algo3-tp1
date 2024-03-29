#include "algoritmos.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<int>> matriz;

int main(int argc, char* argv[])
{
	int n, V;
	n = V = 0;

	cin >> n;
	cin >> V;
		
	if (n < 0 || V < 0)
	{
		cerr << "n y V deben ser no negativos.";
		return -1;
	}

	ofstream myFile;
	stringstream fileName;
	fileName << "output/" << (argc > 1 ? argv[1] : "programaciondinamica.csv");
	myFile.open(fileName.str(), ios_base::app);
	
	vector<int> S(n);

	for (int i = 0; i < n; i++)
	{
		cin >> S[i];
	}

	// Inicializo la matriz para programación dinámica
	matriz = vector<vector<int>>(V+1);

	for (size_t i = 0; i < matriz.size(); i++)
	{
		matriz[i] = vector<int>(S.size() + 1, -2);
	}

	int res;

	// Algoritmo de programación dinámica
	auto startTime = chrono::steady_clock::now();
	res = programacionDinamica(S, V);
	auto endTime = chrono::steady_clock::now();
	cout << res << endl;

	myFile << n << "," << V << "," << res << "," << chrono::duration <double, milli> (endTime - startTime).count() << endl;
	myFile.close();

	return 0;
}