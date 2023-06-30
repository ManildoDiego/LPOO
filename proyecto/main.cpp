#include <cstdlib>
#include <iostream>

extern "C" {
	#include <conio.h>
}

#define TICK_RATE 100
#define ESC   static_cast<char>(27)
#define ENTER static_cast<char>(13)

#include "src/puntuacion.hpp"
#include "src/Juego.hpp"

#include "src/menu.hpp"

using namespace std;

int main() {
inicio:
	// preparo la consola
	system("cls"); 
	ocultar_cursor();

	// menu inicial
	while (1) {
		bool salir = menu();
		if (salir) {
			break;
		}
	}

	char inputKey = '\0';

	Juego juego{};
	cout << juego << endl;
	
	// mientras no se murio, sigue el juego
	while (!juego.murio()) {
		// si toca el teclado, guarda la tecla
		if (kbhit()) {
			inputKey = static_cast<char>(getch());
		}

		// si toca el ESC sale del juego
		if (inputKey == ESC) {
			goto inicio;
		}

		// actualiza el tablero
		juego.actualizar(inputKey);
		cout << juego << endl;

		// pausa la consola
		Sleep(TICK_RATE);
	}

	perdio();

	// sale del programa
	salir();
}
