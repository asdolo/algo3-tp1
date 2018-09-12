#include "algoritmos.hpp"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

vector<vector<int>> matriz;

int main()
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
	
	vector<int> S(n);

	for (int i = 0; i < n; i++)
	{
		cin >> S[i];
	}

	int res;

	// Algoritmo de fuerza bruta
	cout << "Calculando con Fuerza bruta..." << endl;
	auto startTime = chrono::steady_clock::now();
	res = fuerzaBruta(S, V);
	auto endTime = chrono::steady_clock::now();
	cout << "Fuerza bruta: " << res << endl;
	cout << "Tiempo: " << chrono::duration <double, milli> (endTime - startTime).count() << " ms" << endl;

	return 0;
}