#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class FileLoader {
public:
	int rozmiar;
	vector<vector<int>> macierz;

	bool file_read_line(ifstream& file, int tab[], int size);
	bool file_read_graph(string file_name);

};