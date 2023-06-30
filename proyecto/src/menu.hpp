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

#define ESC   static_cast<char>(27)
#define ENTER static_cast<char>(13)

// declaro que Tecla_t = std::pair<std::string, char>
using Tecla_t = std::pair<std::string, char>;

std::vector<Tecla_t> controles = {
	{color.red     + std::string("ARRIBA   ") + color.reset, 'w'},
	{color.magenta + std::string("ABAJO    ") + color.reset, 's'},
	{color.cyan    + std::string("DERECHA  ") + color.reset, 'd'},
	{color.orange  + std::string("IZQUIERDA") + color.reset, 'a'},
};

// funcion de salir y creditos
void salir() {
	system("cls");

	const auto coords = obtener_centro_consola();
	gotoxy(coords);
	std::cout << "Gracias por jugar!\n";
	gotoxy(coords.first, coords.second + 1);
	std::cout << color.magenta << "Creditos:\n";
	gotoxy(coords.first, coords.second + 2);
	std::cout << color.green << "\tManildo Diego    " << color.reset << "-> programador\n";
	gotoxy(coords.first, coords.second + 3);
	std::cout << color.red   << "\tFransico Tumulty " << color.reset << "-> diseniador grafico\n";
	gotoxy(coords.first, coords.second + 4);
	std::cout << color.blue  << "\tJoaquin Pagano   " << color.reset << "-> diseniador y programador\n";

	exit(0);
}

// funcion perdio
void perdio() {
	system("cls");

	gotoxy(obtener_centro_consola());
	std::cout << "Perdiste!";
	std::cin.get();
	salir();
}

void menuControles() {
	char inputKey = '\0';
	size_t n = 0;

	auto esta_en_controles = [](char k, Tecla_t actual) {
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
			inputKey = static_cast<char>(getch());

			if (inputKey == ESC) {
				system("cls");
				return;
			}

			if (inputKey == ENTER) {
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

			if (inputKey == ARRIBA && n > 0)     { n--; } 
			else if (inputKey == ABAJO && n < controles.size()) { n++; }
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
		
		(n == controles.size())
			? std::cout << " [ VOLVER ] "
			: std::cout << "   VOLVER   ";

		Sleep(20);
	}
}

bool menu() {
	// menu de opciones
	static std::vector<std::string> opciones = {
		color.green   + std::string("Jugar")                 + color.reset, 
		color.magenta + std::string("Opciones")              + color.reset, 
		color.cyan    + std::string("Ver maxima puntuacion") + color.reset,
		color.orange  + std::string("Resetear puntuacion")   + color.reset,
		color.red     + std::string("Salir")                 + color.reset,
	};
	
	static std::size_t n = 0;

	char inputKey = '\0';

	if (kbhit()) {
		inputKey = static_cast<char>(getch());

		if (inputKey == ESC) {
			salida:
			salir();
		}

		if (inputKey == ARRIBA && n > 0) { 
			n--; 
		} 
		else if (inputKey == ABAJO && n < (opciones.size()-1)) { 
			n++; 
		}
	}

	if (inputKey == ENTER) {
		system("cls");
		switch (n) {
			case 0: 
				// retorna true (ya puede empezar a jugar)
				return true;
			case 1: 
				// va a al menu de controles
				menuControles();
				break;
			case 2: {
				// 
				const auto coords = obtener_centro_consola();
				gotoxy(coords);
				auto p = leerPuntuacion();
				auto n = leerNombre();
				if (p != 0 || n != "NULL") {
					std::cout << "Maxima puntuacion: " << p << std::endl;
					gotoxy(coords.first, coords.second+1);
					std::cout << "Hecha por: \"" << n << "\"\n";
				} else {
					std::cout << "Ninguna puntuacion ha sido registrada!\n";
				}
				std::cin.get();
				system("cls");
				break;
			}
			case 3: 				
				// resetea la puntuacion
				guardarPuntuacion(0);
				guardarNombre("NULL");
				gotoxy(obtener_centro_consola());
				std::cout << "La puntuacion ha sido reseteada!\n";
				std::cin.get();
				system("cls");
				break;
			case 4:
				goto salida;
				break;
			default:
				// nunca deberia suceder
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

	Sleep(20);

	return false;
}
