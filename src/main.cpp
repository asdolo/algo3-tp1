#include "algoritmos.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	cout << "Ingresar la longitud del arreglo y el valor objetivo V:" << endl;
	
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
		//cin >> S[i];
		S[i] = rand() % 100 + 1;
		cout << "S[" << i << "] = " << S[i] << endl;
	}

	cout << "]";

	// Algoritmo de backtracking 
	cout << "Backtracking: " << backtracking(S, V) << endl;
	// Algoritmo de fuerza bruta 
	cout << "Fuerza bruta: " << fuerzaBruta(S, V) << endl;

	return 0;
}