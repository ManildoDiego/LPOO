#include <cstdlib>
#include <iostream>

extern "C" {
	#include <conio.h>
}

#include "src/menu.hpp"
#include "src/Game.hpp"

#define TICK_RATE 250

using namespace std;

int main() {
	ocultar_cursor();

	while (1) {
		bool salir = menu();
		if (salir) {
			break;
		}
	}

	Game juego{};

	char input_key = '\0';
	char anterior;

	cout << juego << endl;
	
	while (!juego.murio()) {
		if (kbhit()) {
			anterior = input_key;
			input_key = static_cast<char>(getch());
		}

		if (static_cast<int>(input_key) == 27) {
			main();
		}

		juego.actualizar(&input_key, anterior);
		cout << juego << endl;

		Sleep(TICK_RATE);
	}

	main();
}