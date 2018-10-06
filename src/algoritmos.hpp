#include <vector>

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

using namespace std;

extern vector<vector<int>> matriz;

vector<bool> getBinario(int n, int length);
vector<vector<int>> getConjuntoDePartes(vector<int> items);
int getSumatoria(vector<int> items);
unsigned long long int getCardinalPartes(int length);
int fuerzaBruta(vector<int> S, int V);
int backtracking(vector<int> S, int V);
int backtrackingAux(vector<int> S, vector<int> subconjunto, int i, int V, int& minimoGlobal);
int programacionDinamica(vector<int> S, int V);
int programacionDinamicaAux(vector<int> S, int i, int v);

#endif