#define DEBUG
#include <cstdlib>
#include <iostream>

extern "C" {
	#include <conio.h>
}

#include "menu.hpp"
#include "Map.hpp"
#include "manejo_consola.hpp"

using namespace std;

int main() {
	ocultar_cursor();

__menu:
	while (1) {
		bool salir = menu();
		if (salir) {
			break;
		}
	}

	Map mapa{};

	char input_key = '\0';
	char anterior;

	cout << mapa << endl;
	
	while (!mapa.murio()) {
		if (kbhit()) {
			anterior = input_key;
			input_key = static_cast<char>(getch());
		}

		if (static_cast<int>(input_key) == 27) {
			goto __menu;
		}

		mapa.actualizar(&input_key, anterior);
		cout << mapa << endl;

		Sleep(200);
	}

	main();
}