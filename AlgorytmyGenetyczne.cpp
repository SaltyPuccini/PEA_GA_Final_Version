#include "AlgorytmyGenetyczne.h"

bool compare(chromosom a, chromosom b) {
	if (a.fitness < b.fitness)
		return true;
	else
		return false;
}

long long int AlgorytmyGenetyczne::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void AlgorytmyGenetyczne::TSP_GA(vector<vector<int>> macierz, float kryteriumStopu, int wielkoscPopulacjiPoczatkowej, double wspolczynnikMutacji, double wspolczynnikKrzyzowania, int rodzajMutacji) {

	long long int frequency, start, elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();
	srand(unsigned(time(0)));

	vector<chromosom> aktualnaPopulacja;
	int iterator = 0;

	//Wyznaczam rozwi¹zanie pocz¹tkowe poprzez wpisanie do vektora wszystkich miast, a nastêpnie ustawieniu ich w losowej kolejnoœci.
	for (int i = 0; i < wielkoscPopulacjiPoczatkowej; i++) {
		chromosom ch;
		for (int j = 0; j < macierz.size(); j++) {
			ch.wierzcholki.push_back(j);
		}
		aktualnaPopulacja.push_back(ch);
		random_shuffle(aktualnaPopulacja[i].wierzcholki.begin(), aktualnaPopulacja[i].wierzcholki.end());
	}



	//G³ówna pêtla programu			
	while (((float)elapsed / frequency) < kryteriumStopu) {
		vector<chromosom> nastepnaPopulacja;

		//Liczê fitness ka¿dego osobnika z aktualnej populacji.
		for (int i = 0; i < aktualnaPopulacja.size(); i++) {
			aktualnaPopulacja[i].fitness = liczDroge(macierz, aktualnaPopulacja[i].wierzcholki);
		}

		//Dodajê wielkoœæ populacji/8 najlepszych osobników do kolejnej populacji (elitaryzm) -> sortujê po najmniejszym fitnesie aktualn¹ populacjê i przekazujê najlepsze osobniki do nastêpnej.
		sort(aktualnaPopulacja.begin(), aktualnaPopulacja.end(), compare);
		for (int i = 0; i < aktualnaPopulacja.size() / 8; i++) {

			nastepnaPopulacja.push_back(aktualnaPopulacja[i]);
		}

		//wypiszChromosomyZPopulacji(aktualnaPopulacja);
		//wypiszFitnessPopulacji(aktualnaPopulacja);

		//Dopóki nowa populacja nie jest wielkoœci aktualnej, prowadzê turnieje, a nastêpnie wygrani tworz¹ potomstwo z okreœlonym prawdopodobieñstwem, które kolejno mo¿e zmutowaæ z okreœlonym prawdopodobieñstwem i ostatecznie jest dodawane do nowej generacji.
		while (nastepnaPopulacja.size() < wielkoscPopulacjiPoczatkowej)
		{
			//Turniej
			chromosom rodzic1 = turniej(aktualnaPopulacja);
			chromosom rodzic2 = turniej(aktualnaPopulacja);

			//Crossover, Mutacja i Nastêpna Populacja

			chromosom dzieciaczek1;
			chromosom dzieciaczek2;

			if (RRG(0, 1) < wspolczynnikKrzyzowania)
			{
				dzieciaczek1 = crossoverCX(rodzic1, rodzic2);
				dzieciaczek2 = crossoverCX(rodzic2, rodzic1);
			}
			else {
				dzieciaczek1 = rodzic1;
				dzieciaczek2 = rodzic2;
			}

			if (RRG(0, 1) < wspolczynnikMutacji) {
				switch (rodzajMutacji)
				{
				case 0:
					mutacja1(dzieciaczek1);
					break;
				case 1:
					mutacja2(dzieciaczek1);
					break;
				}
				nastepnaPopulacja.push_back(dzieciaczek1);
			}
			
			if (RRG(0, 1) < wspolczynnikMutacji) {
				switch (rodzajMutacji)
				{
				case 0:
					mutacja1(dzieciaczek2);
					break;
				case 1:
					mutacja2(dzieciaczek2);
					break;
				}
			}
			nastepnaPopulacja.push_back(dzieciaczek2);
		}

		aktualnaPopulacja = nastepnaPopulacja;
		iterator++;

		elapsed = read_QPC() - start;
	}

	//Liczê fitness ka¿dego osobnika z ostatecznej populacji.
	for (int i = 0; i < aktualnaPopulacja.size(); i++) {
		aktualnaPopulacja[i].fitness = liczDroge(macierz, aktualnaPopulacja[i].wierzcholki);
	}

	sort(aktualnaPopulacja.begin(), aktualnaPopulacja.end(), compare);

	cout << "Koncowy rezultat:" << endl << endl;
	wypiszChromosomyZPopulacji(aktualnaPopulacja, 1);
	wypiszFitnessPopulacji(aktualnaPopulacja, 1);


}
//Zamiana miejsc dwóch losowych miast.
void AlgorytmyGenetyczne::mutacja1(chromosom& dzieciaczek) {
	int x, y;

	do {
		x = RNG(0, dzieciaczek.wierzcholki.size() - 1);
		y = RNG(0, dzieciaczek.wierzcholki.size() - 1);
	} while (x == y);

	swap(dzieciaczek.wierzcholki[x], dzieciaczek.wierzcholki[y]);
}
//Odwrócenie kolejnoœci miast miêdzy dwoma wylosowanymi miejscami.
void AlgorytmyGenetyczne::mutacja2(chromosom& dzieciaczek) {
	int x, y;

	do {
		x = RNG(0, dzieciaczek.wierzcholki.size() - 1);
		y = RNG(0, dzieciaczek.wierzcholki.size() - 1);
	} while (x == y);

	if (x > y) {
		swap(x, y);
	}

	reverse(dzieciaczek.wierzcholki.begin() + x, dzieciaczek.wierzcholki.begin() + y);
}

void AlgorytmyGenetyczne::wypiszChromosomyZPopulacji(const vector<chromosom>& populacja, int w) {
	for (int i = 0; i < w; i++) {
		cout << "{";
		for (int j = 0; j < populacja[i].wierzcholki.size(); j++) {
			cout << populacja[i].wierzcholki[j] << " ";
		}cout << "}" << endl;
	}cout << endl << endl;
}

void AlgorytmyGenetyczne::wypiszFitnessPopulacji(const vector<chromosom>& populacja, int w) {
	for (int i = 0; i < w; i++) {
		cout <<"Najlepszy chromosom ma fitness: " << populacja[i].fitness << endl;
	}cout << endl;
}

int AlgorytmyGenetyczne::getIndex(vector<int> v, int K)
{
	auto it = find(v.begin(), v.end(), K);

	if (it != v.end()) {
		int index = it - v.begin();
		return index = it - v.begin();
	}
	return -1;
}

//Mocniejszy z dwóch wylosowanych chromosomów jest zwracany.
chromosom AlgorytmyGenetyczne::turniej(const vector<chromosom>& aktualnaPopulacja) {
	chromosom best;

	for (int i = 0; i < 2; i++) {

		chromosom jednostka = aktualnaPopulacja[RNG(0, aktualnaPopulacja.size() - 1)];

		if (best.wierzcholki.empty() || jednostka.fitness < best.fitness)
			best = jednostka;
	}
	return best;
}

//Cycle crossover
chromosom AlgorytmyGenetyczne::crossoverCX(const chromosom& p1, const chromosom& p2) {
	vector<int> tablica(p1.wierzcholki.size(), -1);
	set <int> odwiedzone;
	int pozycja = RNG(0, p1.wierzcholki.size() - 1);
	int poczatekCyklu = p1.wierzcholki[pozycja];

	while (true)
	{
		tablica[pozycja] = p1.wierzcholki[pozycja];
		odwiedzone.insert(p1.wierzcholki[pozycja]);

		if (poczatekCyklu == p2.wierzcholki[pozycja]) {
			break;
		}
		else {
			pozycja = getIndex(p1.wierzcholki, p2.wierzcholki[pozycja]);
		}
	}

	for (int i = 0; i < p1.wierzcholki.size(); i++) {
		if (tablica[i] == -1) {
			tablica[i] = p2.wierzcholki[i];
		}
	}

	chromosom dzieciaczek;
	dzieciaczek.wierzcholki = tablica;

	return dzieciaczek;

}

int AlgorytmyGenetyczne::liczDroge(vector<vector<int>> macierz, vector<int> sciezka) {
	int droga = 0;
	for (int i = 0; i < sciezka.size() - 1; i++) {
		droga = droga + macierz[sciezka[i]][sciezka[i + 1]];
	}
	droga = droga + macierz[sciezka[sciezka.size() - 1]][sciezka[0]];
	return droga;
}
//Random Number Generator
int AlgorytmyGenetyczne::RNG(int zakresDolny, int zakresGorny) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(zakresDolny, zakresGorny);
	return dist(gen);
}
//Random Realnumber Generator
double AlgorytmyGenetyczne::RRG(int zakresDolny, int zakresGorny) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dist(zakresDolny, zakresGorny);
	return dist(gen);
}