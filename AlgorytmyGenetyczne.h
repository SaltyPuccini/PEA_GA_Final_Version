#pragma once
#include<vector>
#include <chrono>
#include <random>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

struct chromosom
{
	std::vector<int> wierzcholki;
	int fitness;

	bool compare(const chromosom& a, const chromosom& b);
};

class AlgorytmyGenetyczne
{
public:
	long long int read_QPC();
	void TSP_GA(vector<vector<int>> macierz, float kryteriumStopu, int wielkoscPopulacjiPoczatkowej, double wspolczynnikMutacji, double wspolczynnikKrzyzowania, int rodzajMutacji);
	void mutacja1(chromosom& dzieciaczek);
	void mutacja2(chromosom& dzieciaczek);
	void wypiszChromosomyZPopulacji(const vector<chromosom>& populacja, int w);
	void wypiszFitnessPopulacji(const vector<chromosom>& populacja, int w);
	int getIndex(vector<int> v, int K);
	chromosom turniej(const vector<chromosom>& aktualnaPopulacja);
	chromosom crossoverCX(const chromosom& p1, const chromosom& p2);
	int liczDroge(vector<vector<int>> macierz, vector<int> sciezka);
	int RNG(int zakresDolny, int zakresGorny);
	double RRG(int zakresDolny, int zakresGorny);
};

