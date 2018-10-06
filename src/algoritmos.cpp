#include <vector>
#include <algorithm>
#include "algoritmos.hpp"

using namespace std;

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

int backtracking(vector<int> S, int V)
{
	vector<int> subconjunto = vector<int>(0);

	int minimoGlobal = -1;

	return backtrackingAux(S, subconjunto, 0, V, minimoGlobal);	
}


int backtrackingAux(vector<int> S, vector<int> subconjunto, int i, int V, int& minimoGlobal)
{
	// Poda por optimalidad:
	// Si el subconjunto a analizar tiene cardinal mayor o igual a la solución óptima encontrada hasta el momento,
	// entonces puede descartarse, ya que seguro que no va a ser una solución mejor a la ya encontrada.
	if (minimoGlobal != -1 && subconjunto.size() >= minimoGlobal)
		return -1;

	// Llegados a este punto, el subconjunto tiene menor cardinal que la solución mínima encontrada hasta este momento.
	
	// Calculo la sumatoria del subconjunto
	int sumaSubconjunto = getSumatoria(subconjunto);

	// Poda por factibilidad:
	// Si nos pasamos del valor objetivo V, no sólo este subconjunto no es solución,
	// sino que ningún otro subconjunto de S que tenga estos elementos será solución
	// (ya que con los elementos de este subconjunto nos alcanza para "pasarnos" del valor V)
	// En términos de árbol, lo que hacemos es podar ambas ramas del subárbol que representa
	// a este subconjunto
	if (sumaSubconjunto > V)
		return -1;

	// Poda por optimalidad:
	// Si este conjunto es solución, no tiene sentido llamar a la recursion en los sub-árboles de este conjunto,
	// Ya que estos contienen elementos de mayor tamaño, por lo que es seguro que no van a ser solución final del problema original
	if (sumaSubconjunto == V)
	{
		// Llegados este punto, el subconjunto es la mejor solución encontrada hasta el momento.	
		minimoGlobal = subconjunto.size();
		return subconjunto.size();
	}
	else
	{
		// Si este subconjunto no suma el numero V, sigo buscando en los sub-árboles
		if (i < S.size())
		{
			int resultadoNoPongo = backtrackingAux(S, subconjunto, i+1, V, minimoGlobal);
			subconjunto.push_back(S[i]);
			int resultadoPongo = backtrackingAux(S, subconjunto, i+1, V, minimoGlobal);

			// Si los resultados devueltos son números finitos (distintos de -1),
			// significa que se encontró una mejor solución
			int resultado;

			if (resultadoPongo != -1 && resultadoNoPongo != -1)
			{
				// Si los dos números son distintos de +infinito, el resultado final
				// será el menor de ellos
				resultado = (resultadoPongo < resultadoNoPongo ? resultadoPongo : resultadoNoPongo);
			}
			else if (resultadoPongo != -1)
			{
				// Si sólo resultadoPongo es un número finito, entonces ese es el resultado óptimo
				resultado = resultadoPongo;
			}
			else if (resultadoNoPongo != -1)
			{
				// Si sólo resultadoNoPongo es un número finito, entonces ese es el resultado óptimo
				resultado = resultadoNoPongo;
			}
			else
			{
				// Ningún sub-árbol contiene la solución óptima, entonces la solución óptima
				// es la del nodo actual
				resultado = -1;
			}
			return resultado;	
		}
		else
		{
			return -1;
		}
	}
}

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

vector<bool> getBinario(int n, int length)
{
	vector<bool> res(length);

	for (int i = 0; i < length; i++)
	{
		res[i] = (n >> i) & 1;
	}

	return res;
}
