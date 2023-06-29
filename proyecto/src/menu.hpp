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

#define __TIMER 20

using Tecla_t = std::pair<const char*, char>;

std::vector<Tecla_t> controles = {
	{"ARRIBA   ", 'w'},
	{"ABAJO    ", 's'},
	{"DERECHA  ", 'd'},
	{"IZQUIERDA", 'a'},
};

void salir() {
	system("cls");

	std::cout << "Gracias por jugar!\n";
	std::cout << color.magenta << "Creditos:\n";
	std::cout << color.green << "\tManildo Diego    " << color.reset << "-> programador\n";
	std::cout << color.red   << "\tFransico Tumulty " << color.reset << "-> diseniador grafico\n";
	std::cout << color.blue  << "\tJoaquin Pagano   " << color.reset << "-> diseniador y programador\n";

	exit(0);
}

void menu_opciones() {
	char input_key = '\0';
	size_t n = 0;

	auto esta_en_controles = [&n](char k, Tecla_t actual) {
		if (actual.second == k) {
			system("cls");
			return false;
		}
		
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
		if (kbhit()) {
			input_key = static_cast<char>(getch());

			if (input_key == ESC) {
				system("cls");
				return;
			}

			if (input_key == ENTER) {
				system("cls");
				if (n == controles.size()) { 
					return; 
				}
				std::cout << "Ingrese una tecla: ";
				char key = '\0';

				do {
					key = static_cast<char>(getch());
					system("cls");
				} while (iscntrl(key) || isdigit(key) || esta_en_controles(key, controles.at(n)));
				
				controles.at(n).second = key;
			}

			if (input_key == ARRIBA && n > 0)     { n--; } 
			else if (input_key == ABAJO && n < controles.size()) { n++; }
		}

		const auto console_coords = obtener_centro_consola();

		const auto& offset_x = console_coords.first;
		const auto& offset_y = console_coords.second;

		for (std::size_t i = 0; i < controles.size(); i++) {
		  gotoxy(offset_x, offset_y + i);

		  if (i == n) {
	      std::cout << controles[i].first << " [ \"" << controles[i].second << "\" ]";
				continue;
		  }

	    std::cout << controles[i].first << "   \"" << controles[i].second << "\"  ";
		}
		
		gotoxy(offset_x, offset_y + controles.size());
		
		if (n == controles.size()) {
			std::cout << " [ VOLVER ] ";
		} else {
			std::cout << "   VOLVER   ";
		}

		Sleep(__TIMER);
	}
}

#define ESC   static_cast<char>(27)
#define ENTER static_cast<char>(13)

bool menu() {
	static std::vector<std::string> opciones = {
		"Jugar", 
		"Opciones", 
		"Ver maxima puntuacion",
		"Salir",
	};
	static std::size_t n = 0;

	char input_key = '\0';

	if (kbhit()) {
		input_key = static_cast<char>(getch());

		if (input_key == ESC) {
			salida:
			salir();
		}

		if (input_key == ARRIBA && n > 0) { 
			n--; 
		} 
		else if (input_key == ABAJO && n < (opciones.size()-1)) { 
			n++; 
		}
	}

	if (input_key == ENTER) {
		system("cls");
		switch (n) {
			case 0: return true;
			case 1: menu_opciones(); break;
			case 2:
				std::cout << "Maxima puntuacion: " << leerPuntuacion() << std::endl;
				std::cin.get();
				system("cls");
				break;
			case 3: goto salida; break;
			default:
				throw std::invalid_argument("Opcion invalida (0-3) -> " + std::to_string(n));
				break;
		}
	}

	const auto console_coords = obtener_centro_consola();

	const auto& offset_x = console_coords.first;
	const auto& offset_y = console_coords.second;

	for (std::size_t i = 0; i < opciones.size(); i++) {
	  gotoxy(offset_x, offset_y + i);

	  if (i == n) {
      std::cout << " [ " << opciones[i] << " ] ";
			continue;
	  }

    std::cout << "   " << opciones[i] << "   ";
	}

	Sleep(__TIMER);

	return false;
}
