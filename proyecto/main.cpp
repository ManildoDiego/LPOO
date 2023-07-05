#include <cstdlib>
#include <iostream>

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
	setCursorConsola();

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
			inputKey = static_cast<char>(tolower(getch()));
		}

		// si toca el ESC sale del juego
		if (inputKey == ESC) {
			goto inicio;
		}

		// actualiza el tablero
		juego.actualizar(inputKey);
		cout << juego << endl;

		if (juego.gano()) {
			system("cls");
			const auto c = getCentroConsola();
			gotoxy(c);
			cout << color.green << "Ganaste!\n" << color.reset;
			gotoxy(c.first, c.second+1);
			system("pause");
			goto inicio;
		}

		// pausa la consola
		Sleep(TICK_RATE);
	}

	perdio();
	goto inicio;

	// sale del programa
	salir();
}
