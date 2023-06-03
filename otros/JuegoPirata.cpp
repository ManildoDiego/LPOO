#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

// Creo una tipo de datos Tablero_t que sirve para el tablero
using Tablero_t = vector<vector<char>>;
// Creo una tipo de datos Coords_t que sirve para el jugador
using Coords_t = std::pair<int, int>;

// creo un entero de 64 bits sin signo para guardar los movimientos del jugador y lo hago global para no tener que pasarlo por parametros a funciones
uint64_t movimientos = 0;

// devuelve numero random entre un min y max
int random(int min, int max) { return min + (std::rand() % (max - min + 1)); }

Tablero_t inicializarTablero(Tablero_t t) {
	// creo tablero 8x8
	const size_t t_size = 8;
	t.resize(t_size);

	// la lleno de (char)254 (caracter de cuadrado) y los bordes los relleno de agua (A)
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

	// creo el tesoro
	do {
		i = random(1, t.size()-2);
		j = random(1, t.size()-2);
	} while (i == 1 && j == 1);

	t[i][j] = 'T';

	// creo los puentes
	t[0][t.size()-1] = 'P';
	t[t.size()-1][0] = 'P';

	return t;
}

void mostrar_tablero(Tablero_t t, Coords_t pj) {
	movimientos++;
	system("cls");

	cout << "Movimientos restantes: " << (50-movimientos) << endl;

	for (size_t i = 0; i < t.size(); i++) {
		for (size_t j = 0; j < t[i].size(); j++) {
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

// logica para mover el jugador
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

// si t[pj.first][pj.second] es igual al caracter 'T' significa que gano (encontro el tesoro)
bool gano(Tablero_t t, Coords_t pj) { return (t[pj.first][pj.second] == 'T'); }

int main() {
	srand(time(NULL));
	// creo e inicializo variables
	Tablero_t tablero;
	Coords_t jugador = {1, 1};
	tablero = inicializarTablero(tablero);

	mostrar_tablero(tablero, jugador);

	// Mientras no haya ganado sigo el juego
	while (!gano(tablero, jugador)) {
		// si no toca el teclado, omito el ciclo
		if (!kbhit()) continue;
		// si lo toca obtengo el input del teclado
		char input = getch();

		// muevo al jugador
		jugador = mover_pj(jugador, tablero, input);
		
		mostrar_tablero(tablero, jugador);

		// si los movimientos son mayores o iguales a 50, perdio
		if (movimientos >= 50) {
			cout << "\033[31mPerdiste\033[0m";
			return 0;
		}
	}

	cout << "\033[32mGanaste!\033[0m";
	return 0;
}