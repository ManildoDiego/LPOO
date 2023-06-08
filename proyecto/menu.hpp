#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

extern "C" {
	#include <conio.h>
}

#include "manejo_consola.hpp"

#define ARRIBA    static_cast<char>(72)
#define ABAJO     static_cast<char>(80)

#define __TIMER 100

using Tecla_t = std::pair<std::string, char>;

std::vector<Tecla_t> controles = {
	{"ARRIBA   ", 'w'},
	{"ABAJO    ", 's'},
	{"DERECHA  ", 'd'},
	{"IZQUIERDA", 'a'},
};

void menu_opciones() {
	char input_key = '\0';
	size_t n = 0;

	auto esta_en_controles = [](char k) {
		for (const auto& key : controles) {
			if (k == key.second) {
				system("cls");
				std::cout << "\'" << k << "\' esta en controles esa tecla!\n";
				return true;
			}
		}

		return false;
	};

	while (1) {
		system("cls");
		if (kbhit()) {
			input_key = static_cast<char>(getch());

			if (static_cast<int>(input_key) == 27) {
				return;
			}

			if (static_cast<int>(input_key) == 13) {
				std::cout << "Ingrese una tecla: ";
				char key = '\0';

				do {
					key = static_cast<char>(getch());
				} while (iscntrl(key) || isdigit(key) || esta_en_controles(key));
				
				controles.at(n).second = key;
			}

			if (input_key == ARRIBA && n > 0)     { n--; } 
			else if (input_key == ABAJO && n < 3) { n++; }
		}

		const auto console_coords = obtener_centro_consola();

		const auto& offset_x = console_coords.first;
		const auto& offset_y = console_coords.second;

		for (std::size_t i = 0; i < controles.size(); i++) {
		  gotoxy(offset_x, offset_y + i);

		  if (i == n) {
	      std::cout << controles[i].first << " [\'" << controles[i].second <<  "\'] ";
				continue;
		  }

	    std::cout << controles[i].first << "  \'" << controles[i].second <<  "\'  ";
		}

		Sleep(__TIMER);
	}
}

void mostrar_menu(size_t opcion, char c) {
	const auto console_coords = obtener_centro_consola();

	const auto& offset_x = console_coords.first;
	const auto& offset_y = console_coords.second;

	std::vector<std::string> opciones = {
		"Jugar", 
		"Opciones", 
		"Salir",
	};

	for (std::size_t i = 0; i < opciones.size(); i++) {
	  gotoxy(offset_x, offset_y + i);

	  if (i == opcion) {
      std::cout << " [ " << opciones[i] << " ] ";
			continue;
	  }

    std::cout << "   " << opciones[i] << "   ";
	}
}

bool menu() {
	bool salir = false;
	char input_key = '\0';
	static size_t n = 0;
	system("cls");

	if (kbhit()) {
		input_key = static_cast<char>(getch());

		if (static_cast<int>(input_key) == 27) {
			salida:
			system("cls");
			std::cout << "Gracias por jugar!\n";
			exit(0);
		}

		if (input_key == ARRIBA && n > 0)     { n--; } 
		else if (input_key == ABAJO && n < 3) { n++; }
	}

	if (static_cast<int>(input_key) == 13) {
		switch (n) {
			case 0:
				salir = true;
				break;

			case 1: 
				menu_opciones();
				break;
			
			case 2:
				goto salida;
				break;
				
			default:
				throw std::invalid_argument("Opcion invalida (0-2) -> " + std::to_string(n));
				break;
		}
	}

	if (salir) { return salir; }

	mostrar_menu(n, input_key);

	Sleep(__TIMER);

	return false;
}
