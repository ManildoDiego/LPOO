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
				if (n == controles.size()) { 
					system("cls");
					return; 
				}
				std::cout << "Ingrese una tecla: ";
				char key = '\0';

				do {
					key = static_cast<char>(getch());
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

bool menu(const Game* juego) {
	char input_key = '\0';
	static size_t n = 0;

	if (kbhit()) {
		input_key = static_cast<char>(getch());

		if (input_key == ESC) {
			salida:
			salir(juego);
		}

		if (input_key == ARRIBA && n > 0)     { n--; } 
		else if (input_key == ABAJO && n < 2) { n++; }
	}

	if (input_key == ENTER) {
		switch (n) {
			case 0: return true;
			case 1: menu_opciones(); break;
			case 2: goto salida;     break;
			default:
				throw std::invalid_argument("Opcion invalida (0-2) -> " + std::to_string(n));
				break;
		}
	}

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

	  if (i == n) {
      std::cout << " [ " << opciones[i] << " ] ";
			continue;
	  }

    std::cout << "   " << opciones[i] << "   ";
	}

	Sleep(__TIMER);

	return false;
}