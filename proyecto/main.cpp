#include <cstdlib>
#include <iostream>

extern "C" {
	#include <conio.h>
}

#include "Map.hpp"
#include "manejo_consola.hpp"

using namespace std;

int main() {
	ocultar_cursor();

	Map mapa{};
	char input_key;

	cout << mapa << endl;

	
	while (!mapa.murio()) {
		if (!kbhit()) {
			continue;
		}

		input_key = static_cast<char>(getch());

		mapa.mover_pacman(input_key);
		cout << mapa << endl;

		Sleep(0);
	}
}