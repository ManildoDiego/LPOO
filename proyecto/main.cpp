#include <cstdlib>
#include <iostream>

extern "C" {
	#include <conio.h>
}

#define TICK_RATE 150
#define ESC   static_cast<char>(27)
#define ENTER static_cast<char>(13)

const char* file_name = "Puntaje.txt";
FILE* puntuacion = fopen(file_name, "r+");

#include "src/Game.hpp"

void salir(const Game* juego) {
	system("cls");
	std::cout << "Gracias por jugar!\n";
	std::cout << color.magenta << "Creditos:\n";
	std::cout << color.green << "\tManildo Diego    " << color.reset << "-> programador\n";
	std::cout << color.red   << "\tFransico Tumulty " << color.reset << "-> diseniador grafico\n";
	std::cout << color.blue  << "\tJoaquin Pagano   " << color.reset << "-> diseniador y programador\n";
	
	if (juego != nullptr) {
		fprintf(puntuacion, "%llu", juego->get_puntuacion());
	}
	fclose(puntuacion);
	exit(0);
}

#include "src/menu.hpp"

using namespace std;

int main() {
inicio:
	system("cls");
	ocultar_cursor();

	if (puntuacion == NULL) {
		system("cls");
		cout << "Creando archivo de puntaje"; Sleep(500);
		cout << '.';                          Sleep(500);
		cout << '.';                          Sleep(500);
		cout << '.' << endl;                  Sleep(500);
		
		puntuacion = fopen(file_name, "w+");

		system("cls");
		cout << "Archivo creado!";
		Sleep(1000);
	}

	Game juego{};

	while (1) {
		bool salir = menu(&juego);
		if (salir) {
			break;
		}
	}

	char input_key = '\0';
	char anterior = '\0';

	cout << juego << endl;
	
	while (!juego.murio()) {
		if (kbhit()) {
			anterior = input_key;
			input_key = static_cast<char>(getch());
		}

		if (input_key == ESC) {
			goto inicio;
		}

		juego.actualizar(&input_key, anterior);
		cout << juego << endl;

		Sleep(TICK_RATE);
	}

	salir(&juego);
}
