#include <iostream>
#include <vector>

using namespace std;

using Tablero_t = vector<vector<char>>;

int random(int min, int max) {
	return min + (std::rand() % (max - min + 1));
}

Tablero_t inicializarTablero(Tablero_t t) {
	// creo tablero 8x8
	const size_t t_size = 8;
	t.resize(t_size);
	for (auto& fila : t) {
		fila.resize(t_size);
	}

	for (size_t i = 0; i < t.size(); i++) {
		for (size_t j = 0; j < t.size(); j++) {
			
		}
	}

	return t;
}

void print_tablero(Tablero_t t) {
	for (size_t i = 0; i < t.size(); i++) {
		for (size_t j = 0; j < t.size(); j++) {
			cout << t[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main() {
	Tablero_t tablero;

	tablero = inicializarTablero(tablero);
	print_tablero(tablero);
}