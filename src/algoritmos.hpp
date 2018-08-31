#include <vector>

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

using namespace std;

vector<bool> getBinario(int n, int length);
vector<vector<int>> getConjuntoDePartes(vector<int> items);
int getSumatoria(vector<int> items);
int fuerzaBruta(vector<int> S, int V);

#endif