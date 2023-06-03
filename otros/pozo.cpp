#include <iostream>
#include <array>
#include <conio.h>

#define ARRIBA    'w'
#define ABAJO     's'
#define DERECHA   'd'
#define IZQUIERDA 'a'

using namespace std;

using Tablero_t = array<array<int, 10>, 10>;
using Coordenadas_t = pair<int, int>;

Tablero_t inicializar_matriz(Tablero_t matriz) {
	// Rellenar matriz de unos
	for (size_t i = 0; i < matriz.size(); i++) {
		for (size_t j = 0; j < matriz.size(); j++) {
			matriz[i][j] = 1;
		}
	}

	// Genera pozos (0) en lugares random
	for (size_t k = 0; k < 3; k++) {
		auto i = rand() % matriz.size();
		auto j = rand() % matriz.size();

		// si existe un pozo o se genera un pozo en {0, 0} o {9, 9} vuelve a realizar el procedimineto
		while (matriz[i][j] == 0 || (i == 0 && j == 0) || (i == matriz.size() && j == matriz.size())) {
			i = rand() % matriz.size();
			j = rand() % matriz.size();
		}

		matriz[i][j] = 0;
	}

	return matriz;
} 

void print_tablero(Tablero_t tablero, Coordenadas_t pj) {
	system("cls");
	cout << "Puedes moverte con W A S D\n\n";
	for (size_t i = 0; i < tablero.size(); i++) {
		for (size_t j = 0; j < tablero.size(); j++) {
			// Comprueba si es el jugador
			if (pj.first == i && pj.second == j) {
				cout << "P ";
				continue;
			} 
			
			// comprueba si es el final
			else if (i == 9 && j == 9) {
				cout << "F";
				continue;
			}

			#ifdef DEBUG
				cout << tablero[i][j] << ' ';
			#else
				cout << "* ";
			#endif
		}

		cout << '\n';
	}
}

void print_minas(Tablero_t tablero, Coordenadas_t pj, bool imprimir_bomba = true) {	
	system("cls");
	for (size_t i = 0; i < tablero.size(); i++) {
		for (size_t j = 0; j < tablero.size(); j++) {
			// comprueba si es un pozo
			if (tablero[i][j] == 0) {
				cout << "O ";
				continue;
			} 
			
			// comprueba si es el final
			else if (i == 9 && j == 9) {
				cout << "F";
				continue;
			}
			cout << "* ";
		}

		cout << '\n';
	}

	if (imprimir_bomba) {
		cout << "Habia un pozo en {" << pj.first << ", " << pj.second << "}\n";
		return;
	}

	cout << "Ganaste!";
}

bool game_over(Tablero_t tablero, Coordenadas_t pj) {
	for (size_t i = 0; i < tablero.size(); i++) {
		for (size_t j = 0; j < tablero.size(); j++) {
			// Comprueba por cada posicion si el personaje se ubica en un pozo
			if (tablero[i][j] == 0 && pj.first == i && pj.second == j) {
				return true;
			}
		}
	}

	return false;
}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	Tablero_t posiciones;
	Coordenadas_t pj_pos = {0, 0};

	posiciones = inicializar_matriz(posiciones);

	print_tablero(posiciones, pj_pos);

	while (!game_over(posiciones, pj_pos)) {
		// si no esta tocando ninguna tecla, omite el ciclo
		if (!kbhit()) { continue; }

		// si no obtiene el input
		char key_pressed = static_cast<char>(getch());
		
		// va comprobando que tecla pulso y si no se sale de los limites
		if      (key_pressed == ARRIBA && pj_pos.first >= 1)                    { pj_pos.first--; }
		else if (key_pressed == ABAJO && pj_pos.first < posiciones.size()-1)    { pj_pos.first++; }
		else if (key_pressed == IZQUIERDA && pj_pos.second >= 1)                { pj_pos.second--; }
		else if (key_pressed == DERECHA && pj_pos.second < posiciones.size()-1) { pj_pos.second++; }

		// si las posiciones del personaje son 9, 9 gano
		if (pj_pos.first == 9 && pj_pos.second == 9) {
			cout << "Ganaste!\n\n";
			// llamo a la funcion con imprimir_bomba = false
			print_minas(posiciones, pj_pos, false);
			return 0;
		}

		// imprime el tablero
		print_tablero(posiciones, pj_pos);
	}

	// si llego aca significa que perdio
	print_minas(posiciones, pj_pos);
}