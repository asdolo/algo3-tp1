#include <vector>
#include <algorithm>
#include "algoritmos.hpp"

using namespace std;

int backtracking(vector<int> S, int V)
{
	// Poda por factibilidad:
	// 	Al analizar si el subconjunto actual suma el valor objetivo, podemos hacer un break
	// cuando la sumatoria actual ya se pasa de dicho valor, ya que todos los valores son
	// enteros no negativos

	// Poda por optimalidad:
	// Opción 1:
	// 	Recorrer el conjunto de partes en orden creciente por cardinal.
	// La primer solución que encontremos será una de las mínimas,
	// con lo cual ya no conviene seguir buscando en el resto de subconjuntos
	// (es imposible que haya otra solución con menor cardinal)
	// Opción 2:
	//	Recorrer el conjunto en cualquier orden. Cada vez que estamos por probar
	// un subconjunto nuevo, vemos antes su cardinal. Si el cardinal es mayor que
	// el mínimo que ya tenemos, lo salteamos, ya que, aunque el subconjunto sea
	// solución, su cardinal será mayor que el ya obtenido.

	int minimoCardinal = -1;

	unsigned long long int cardinalPartes = getCardinalPartes(S.size());

	// Para cada subconjunto de S... O(2^n)
	for (int i = 0; i < cardinalPartes; i++)
	{
		vector<bool> binario = getBinario(i, S.size()); // O(n)
		vector<int> subconjunto;

		for (size_t j = 0; j < binario.size(); j++)
		{
			if (binario[j] == true)
				subconjunto.push_back(S[j]);
		}

		// Poda por optimalidad: si el cardinal del subconjunto a analizar es mayor que el cardinal del
		// subconjunto solución actual, entonces seguro que este subconjunto no será solución optima, con lo
		// cual lo podemos saltear

		if (minimoCardinal != -1 && subconjunto.size() > minimoCardinal)
			continue; // Avanzar al siguiente subconjunto
		
		// Hacemos la sumatoria del subconjunto
		int sumaSubconjunto = 0;

		for (size_t j = 0; j < subconjunto.size(); j++)
		{
			sumaSubconjunto += subconjunto[j];
			
			// Poda por factibilidad: si nos pasamos del valor objetivo V,
			// es imposible que, sumando más números no negativos, lleguemos al valor V
			if (sumaSubconjunto > V)
				break;
		}
			
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

int fuerzaBruta(vector<int> S, int V)
{
	int minimoCardinal = -1;

	unsigned long long int cardinalPartes = getCardinalPartes(S.size());

	// Para cada subconjunto de S... O(2^n)
	for (int i = 0; i < cardinalPartes; i++)
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
