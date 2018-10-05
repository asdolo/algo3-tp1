#include <vector>
#include <algorithm>
#include "algoritmos.hpp"
#include <iostream>
#include <bitset>

using namespace std;


int programacionDinamica(vector<int> S, int V)
{
	return programacionDinamicaAux(S, S.size(), V);
}

int programacionDinamicaAux(vector<int> S, int i, int v)
{
	if (v < 0)
		return -1; // +infinito

	if (matriz[v][i] == -2)
	{
		if (i == 0 && v == 0)
		{
			matriz[v][i] = 0;
		}
		else if (i == 0 && v !=0)
		{
			matriz[v][i] = -1;
		}
		else
		{
			int resultadoPongo = programacionDinamicaAux(S, i-1, v - S[i-1]);
			int resultadoNoPongo = programacionDinamicaAux(S, i-1, v);

			int resultado;

			if (resultadoPongo != -1 && resultadoNoPongo != -1)
			{
				// Si los dos números son distintos de +infinito
				resultado = (resultadoPongo + 1 < resultadoNoPongo ? resultadoPongo + 1 : resultadoNoPongo);
			}
			else if (resultadoPongo != -1)
			{
				// Sólo resultadoPongo es un número finito
				resultado = resultadoPongo + 1;
			}
			else if (resultadoNoPongo != -1)
			{
				// Sólo resultadoNoPongo es un número finito
				resultado = resultadoNoPongo;
			}
			else
			{
				resultado = -1;
			}
			matriz[v][i] = resultado;
		}
	}

	return matriz[v][i];
}

int backtracking(vector<int> S, int V)
{
	
	for (int i = 0; i <= S.size(); i++)	// O(n * ...)
	{
		cout << endl << "Subconjuntos de tamaño " << i << " (" << nChoosek(S.size(), i) << "):" << endl;
		// Subconjuntos de tamaño i

		// Obtengo un vector de bool, que representa la primer permutacion de i elementos del vector original S
		
		// Hmm, qué pasa si esto es O(n)?
		vector<bool> primeraPermutacion = getPrimeraPermutacion(i, S.size());
		vector<bool> permutacionActual = getPrimeraPermutacion(i, S.size());

		unsigned long long int currentPermCount = 1;
		// Para cada subconjunto de tamaño i hacer:
		do
		{	
			cout << currentPermCount << ": \t\t";
			printVector(permutacionActual);
			// Obtenemos el subconjunto en cuestión usando el vector de bool
			// que representa la permutación de este subconjunto
			vector<int> subconjunto;

			for (size_t j = 0; j < permutacionActual.size(); j++)
			{
				if (permutacionActual[j] == true)
					subconjunto.push_back(S[j]);
			}

			// Hacemos la sumatoria del subconjunto
			int sumaSubconjunto = 0;
			bool solucionFactible = true;
			int elementosNoFactibles = 0;

			for (size_t j = 0; j < subconjunto.size() && solucionFactible; j++)
			{
				sumaSubconjunto += subconjunto[j];
				
				// Poda por factibilidad: si nos pasamos del valor objetivo V,
				// es imposible que, sumando más números no negativos, lleguemos al valor V
				if (sumaSubconjunto > V)
				{
					solucionFactible = false;
					elementosNoFactibles = j;
				}
			}
			
			if (solucionFactible && sumaSubconjunto == V)
			{
				// Encontramos un subconjunto cuya sumatoria es el valor objetivo V

				// Como estamos iterando en subconjuntos de tamaño i de forma creciente,
				// seguro que, aunque haya una solución de tamaño mayor a i, ésta no va 
				// a ser óptima, con lo cual nos ahorramos seguir buscando una solución
				// óptima.

				// Simplemente devolvemos ésta solución como (una) de las óptimas, pues lo es

				cout << "Poda por optimalidad" << endl;
				return subconjunto.size();
			}
			else
			{
				// Si la solución no es factible, guardamos en un vector las posiciones de los elementos
				// que no son parte de la solucion
				cout << "Poda por factibilidad" << endl;
				// TODO: PREGUNTAR. Creo que está mal.
			}			
			
			prev_permutation(permutacionActual.begin(), permutacionActual.end());
			currentPermCount++;
		} while (permutacionActual != primeraPermutacion);
		
	}

	// Si llegamos acá es porque recorrimos todos los subconjuntos y no encontramos ninguna
	// solución que sume el valor objetivo

	return -1;
}

void printVector(vector<bool> v)
{

	if (v.size() == 0)
	{
		cout << "[ ]" << endl;
		return;	
	}

	cout << "[";

	for (int i = 0; i < v.size() - 1; i++)
	{
		cout << v[i] << ",";
	}

	cout << v[v.size() - 1] << "]" << endl;

}

int fuerzaBruta(vector<int> S, int V)
{
	int minimoCardinal = -1;

	unsigned long long int cardinalPartes = getCardinalPartes(S.size());

	// Para cada subconjunto de S... O(2^n)
	for (unsigned long int i = 0; i < cardinalPartes; i++)
	{
		vector<bool> binario = getBinario(i, S.size()); // O(n)
		vector<int> subconjunto;

		for (size_t j = 0; j < binario.size(); j++)
		{
			if (binario[j] == true)
				subconjunto.push_back(S[j]);
		}

		int sumaSubconjunto = getSumatoria(subconjunto);

		if (sumaSubconjunto == V)
		{
			// Encontramos un subconjunto cuya sumatoria es el valor objetivo V

			// Veamos si es el minimo, o si es el primero que encontramos
			if ((int)subconjunto.size() < minimoCardinal || minimoCardinal == -1)
				minimoCardinal = subconjunto.size();
		}
	}

	return minimoCardinal;
}

unsigned nChoosek( unsigned n, unsigned k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

unsigned long long int getCardinalPartes(int length)
{
	unsigned long long int res = 1;

	for (int i = 0; i < length; i++)
	{
		res = res * 2;
	}

	return res;
}

int getSumatoria(vector<int> items)
{
	int res = 0;

	for (size_t i = 0; i < items.size(); i++)
	{
		res += items[i];
	}

	return res;
}

vector<bool> getPrimeraPermutacion(int n, int length)
{
	vector<bool> res(length);

	for (int i = 0; i < n; i++)
	{
		res[i] = 1;
	}

	return res;
}

vector<bool> getBinario(int n, int length)
{
	vector<bool> res(length);

	for (int i = 0; i < length; i++)
	{
		res[i] = (n >> i) & 1;
	}

	return res;
}
