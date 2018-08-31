#include <vector>
#include <algorithm>
#include "algoritmos.hpp"

using namespace std;

int fuerzaBruta(vector<int> S, int V)
{
	vector<vector<int>> partesDeS = getConjuntoDePartes(S); // 2^n

	int minimoCardinal = -1;

	for (size_t i = 0; i < partesDeS.size(); i++)		// O(2^n)
	{
		vector<int> subconjunto = partesDeS[i];
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

int getSumatoria(vector<int> items)
{
	int res = 0;

	for (size_t i = 0; i < items.size(); i++)
	{
		res += items[i];
	}

	return res;
}

vector<vector<int>> getConjuntoDePartes(vector<int> items)
{
	long long int cardinalPartes = pow(2, items.size());
	vector<vector<int>> res(cardinalPartes);

	for (int i = 0; i < cardinalPartes; i++)
	{
		vector<bool> binario = getBinario(i, items.size());
		vector<int> subconjuntoActual;

		for (size_t j = 0; j < binario.size(); j++)
		{
			if (binario[j] == true)
				subconjuntoActual.push_back(items[j]);
		}

		res.push_back(subconjuntoActual);
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
