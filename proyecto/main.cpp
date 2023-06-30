#include <cstdlib>
#include <iostream>

extern "C" {
	#include <conio.h>
}

#define TICK_RATE 100
#define ESC   static_cast<char>(27)
#define ENTER static_cast<char>(13)

#include "src/puntuacion.hpp"
#include "src/Game.hpp"

#include "src/menu.hpp"

using namespace std;

int main() {
inicio:
	// preparo la consola
	system("cls"); 
	ocultar_cursor();

	Game juego{};

	// menu inicial
	while (1) {
		bool salir = menu();
		if (salir) {
			break;
		}
	}

	char input_key = '\0';
	char anterior = '\0';

	cout << juego << endl;
	
	// mientras no se murio, sigue el juego
	while (!juego.murio()) {
		// si toca el teclado, guarda la tecla
		if (kbhit()) {
			input_key = static_cast<char>(getch());
		}

		// si toca el ESC sale del juego
		if (input_key == ESC) {
			goto inicio;
		}

		// actualiza el tablero
		juego.actualizar(&input_key, &anterior);
		cout << juego << endl;

		// pausa la consola
		Sleep(TICK_RATE);
	}

	// sale del programa
	salir();
}
