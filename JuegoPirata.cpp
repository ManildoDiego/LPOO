#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

using Tablero_t = vector<vector<char>>;
using Coords_t = std::pair<int, int>;

uint64_t movimientos = 0;

int random(int min, int max) { return min + (std::rand() % (max - min + 1)); }

Tablero_t inicializarTablero(Tablero_t t) {
	// creo tablero 8x8
	const size_t t_size = 8;
	t.resize(t_size);

	for (size_t i = 0; i < t.size(); i++) {
		t[i].resize(t_size);
		for (size_t j = 0; j < t[i].size(); j++) {
			t[i][j] = 254;
			if (i == 0 || i == (t.size()-1) || j == 0 || j == (t.size()-1)) {
				t[i][j] = 'A';
			}
		}
	}

	int i = 1, j = 1;

	do {
		i = random(1, t.size()-2);
		j = random(1, t.size()-2);
	} while (i == 1 && j == 1);

	t[i][j] = 'T';
	t[0][t.size()-1] = 'P';
	t[t.size()-1][0] = 'P';

	return t;
}

void print_tablero(Tablero_t t, Coords_t pj) {
	movimientos++;
	system("cls");

	cout << "Movimientos restantes: " << (50-movimientos) << endl;

	for (size_t i = 0; i < t.size(); i++) {
		for (size_t j = 0; j < t.size(); j++) {
			if (pj.first == i && pj.second == j) {
				cout << "\033[33m" << static_cast<char>(2) << "\033[0m ";
				continue;
			}

			else if (t[i][j] == 'T') {
				cout << static_cast<char>(254) << ' ';
				continue;
			}

			else if (t[i][j] == 'A') {
				cout << "\033[34m" << t[i][j] << "\033[0m ";
				continue;
			}

			else if (t[i][j] == 'P') {
				cout << "\033[35m" << t[i][j] << "\033[0m ";
				continue;
			}

			cout << t[i][j] << ' ';
		}
		cout << '\n';
	}
}

Coords_t mover_pj(Coords_t pj, Tablero_t t, char input) {
	if (input == 'd' && pj.second < t.size()-2) {
		pj.second++;
	} 
	
	else if (input == 'a' && pj.second > 1) {
		pj.second--;
	}

	else if (input == 's' && pj.first < t.size()-2) {
		pj.first++;
	}

	else if (input == 'w' && pj.first > 1) {
		pj.first--;
	}

	return pj;
}

bool gano(Tablero_t t, Coords_t pj) { return (t[pj.first][pj.second] == 'T'); }

int main() {
	srand(time(NULL));
	Tablero_t tablero;
	Coords_t jugador = {1, 1};


	tablero = inicializarTablero(tablero);

	print_tablero(tablero, jugador);

	while (!gano(tablero, jugador)) {
		if (!kbhit()) continue;
		char input = getch();

		jugador = mover_pj(jugador, tablero, input);
		

		print_tablero(tablero, jugador);

		if (movimientos >= 50) {
			cout << "\033[31mPerdiste\033[0m";
			return 0;
		}
	}

	cout << "\033[32mGanaste!\033[0m";
}