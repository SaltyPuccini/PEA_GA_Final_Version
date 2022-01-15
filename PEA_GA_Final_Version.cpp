#include"AlgorytmyGenetyczne.h"
#include"FileLoader.h"

//https://cstheory.stackexchange.com/questions/14758/tournament-selection-in-genetic-algorithms

class Dostep {
public:

	char wejscie;
	bool petla = true;
	float kryteriumStopu = 60;
	int wielkoscPopulacjiPoczatkowej = 50, rodzajMutacji = 1;
	double wspolczynnikMutacji = 0.01, wspolczynnikKrzyzowania = 0.9;
	AlgorytmyGenetyczne alg;

	string wypiszRodzajMutacji(int rodzaj) {
		switch (rodzaj)
		{
		case 0:
			return "SWAP";
		case 1:
			return "REVERSE";
		}
	}

	void menu(FileLoader wczyt) {

		string sciezka = "";
		do {
			cout << endl;
			cout << "Kryterium stopu: " << kryteriumStopu << "s | Wielkosc populacji poczatkowej: " << wielkoscPopulacjiPoczatkowej << " | Wspolczynnik mutacji : " << wspolczynnikMutacji << " | Wspolczynnik krzyzowania: " << wspolczynnikKrzyzowania << " | Rodzaj mutacji: " << wypiszRodzajMutacji(rodzajMutacji);
			cout << endl << endl;
			cout << "1. Wczytanie danych z pliku i wyswietlenie wczytanych danych" << endl;
			cout << "2. Wprowadzenie kryterium stopu" << endl;
			cout << "3. Ustawienie wielkosci populacji poczatkowej" << endl;
			cout << "4. Ustawienie wspolczynnika mutacji" << endl;
			cout << "5. Ustawienia wspolczynnika krzyzowania" << endl;
			cout << "6. Wybor rodzaju mutacji." << endl;
			cout << "7. Uruchomianie algorytmu dla wczytanych danych i ustawionych parametrow oraz wyswietlenie wynikow." << endl;
			cout << "q. Wyjdz" << endl;

			cin >> wejscie;

			switch (wejscie) {
			case '1':
				cout << "Podaj sciezke dostepu do pliku (np. Q:\\\\graf.txt)" << endl;
				cin >> sciezka;

				if (!wczyt.file_read_graph(sciezka))
					break;

				for (int i = 0; i < wczyt.macierz.size(); i++) {
					for (int j = 0; j < wczyt.macierz.size(); j++) {
						cout << wczyt.macierz[i][j] << " ";
					}
					cout << endl;
				}

				cout << endl;
				break;
			case '2':
				cout << "Podaj kryterium stopy [w sekundach]: " << endl;
				cin >> kryteriumStopu;
				break;
			case '3':
				cout << "Podaj wielkosc populacji poczatkowej" << endl;
				cin >> wielkoscPopulacjiPoczatkowej;
				break;
			case '4':
				cout << "Podaj wspolczynnik mutacji: " << endl;
				cin >> wspolczynnikMutacji;
				break;
			case '5':
				cout << "Podaj wspolczynnik krzyzowania: " << endl;
				cin >> wspolczynnikKrzyzowania;
				break;
			case '6':
				cout << "Podaj rodzaj mutacji (0 - zamiana dwoch losowo wybranych miast; 1 - odwrocenie kolejnosci miast o losowej dlugosci w losowym miejscu permutacji ): " << endl;
				do
					cin >> rodzajMutacji;
				while (rodzajMutacji != 0 && rodzajMutacji != 1);
				break;
			case '7':
				alg.TSP_GA(wczyt.macierz, kryteriumStopu, wielkoscPopulacjiPoczatkowej, wspolczynnikMutacji, wspolczynnikKrzyzowania, rodzajMutacji);
				break;
			case 'q':
				petla = false;
				break;
			default:
				break;
			}
			//system("PAUSE");
			//system("CLS");
		} while (petla);

	}
};


int main()
{
	FileLoader wczyt;
	Dostep menuGlowne;
	menuGlowne.menu(wczyt);
}