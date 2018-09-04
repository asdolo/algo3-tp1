#include "algoritmos.hpp"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

vector<vector<int>> matriz;

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
		cin >> S[i];
		//S[i] = rand() % 100 + 1;
		//cout << "S[" << i << "] = " << S[i] << endl;
	}

	//cout << "]";

	// Inicializo la matriz para programación dinámica
	matriz = vector<vector<int>>(V+1);

	for (size_t i = 0; i < matriz.size(); i++)
	{
		matriz[i] = vector<int>(S.size() + 1, -2);
	}

	/*
	cout << "Matriz antes:" << endl;

	for (int i = 0; i < matriz[0].size(); i++)
	{
		cout << "       i = " << i << "\t";
	}
	cout << endl;
	for (int i = 0; i < matriz.size(); i++)
	{
		cout << "V = " << i << ": ";
		for (int j = 0; j < matriz[i].size(); j++)
		{
			cout << matriz[i][j] << "\t\t";
		}
		cout << endl;
	}
	*/

	cout << "steady_clock" << endl;
	cout << chrono::steady_clock::period::num << endl;
	cout << chrono::steady_clock::period::den << endl;
	cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;

	int res;

	// Algoritmo de programación dinámica
	auto startTime = chrono::steady_clock::now();
	res = programacionDinamica(S, V);
	auto endTime = chrono::steady_clock::now();
	cout << "Programación dinámica: " << res << endl;
	cout << "Tiempo: " << chrono::duration <double, milli> (endTime - startTime).count() << " ms" << endl;

	/*
	cout << "Matriz despues:" << endl;

	for (int i = 0; i < matriz[0].size(); i++)
	{
		cout << "       i = " << i << "\t";
	}
	cout << endl;
	for (int i = 0; i < matriz.size(); i++)
	{
		cout << "V = " << i << ": ";
		for (int j = 0; j < matriz[i].size(); j++)
		{
			cout << matriz[i][j] << "\t\t";
		}
		cout << endl;
	}
	*/

	// Algoritmo de backtracking
	startTime = chrono::steady_clock::now();
	res = backtracking(S, V);
	endTime = chrono::steady_clock::now();
	cout << "Backtracking: " << res << endl;
	cout << "Tiempo: " << chrono::duration <double, milli> (endTime - startTime).count() << " ms" << endl;

	// Algoritmo de fuerza bruta
	startTime = chrono::steady_clock::now();
	res = fuerzaBruta(S, V);
	endTime = chrono::steady_clock::now();
	cout << "Fuerza bruta: " << res << endl;
	cout << "Tiempo: " << chrono::duration <double, milli> (endTime - startTime).count() << " ms" << endl;
	
	return 0;
}