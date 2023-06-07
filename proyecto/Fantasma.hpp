#pragma once

#include <ostream>

extern "C" {
	#include <time.h>
}

#include "PacMan.hpp"

/*
	1-Blinky (Shadow): Blinky es el fantasma rojo y su objetivo principal es perseguir directamente a Pac-Man. 
	Blinky se mueve hacia la posición actual de Pac-Man y trata de reducir la distancia entre ellos lo más rápido posible.

	2-Pinky (Speedy): Pinky es el fantasma rosa y su objetivo es emboscar a Pac-Man anticipando su movimiento. 
	Pinky intenta posicionarse cuatro celdas por delante de Pac-Man, teniendo en cuenta la dirección actual de Pac-Man.

	3-Inky (Bashful): Inky es el fantasma celeste y su objetivo es más complejo. Inky trata de emboscar a Pac-Man combinando la posición de Blinky y la posición relativa a la ubicación actual de Pac-Man. 
	Inky se calcula trazando una línea desde Blinky a dos celdas más allá de Pac-Man, luego duplicando la distancia y trazando una línea en esa dirección.

	4-Clyde (Pokey): Clyde es el fantasma naranja y su comportamiento es más impredecible.
	Clyde se mueve hacia Pac-Man cuando está a una distancia mayor que o igual a ocho celdas, pero si la distancia es menor a ocho, Clyde se comporta de manera aleatoria.
*/

#include "Pieza.hpp"

using Mapa_t = std::array<std::array<Pieza, COLUMNAS_SIZE>, FILAS_SIZE>;
using Coords_t = std::pair<int64_t, int64_t>;

enum Tipo_Fantasma {
	null,

	BLINKY, // Rojo
	PINKY,  // Rosa
	INKY,   // Azul
	CLYDE,  // Naranja
};

struct Fantasma {
	Fantasma() = default;
	Fantasma(const Fantasma& p) 
		: m_sprite(p.m_sprite), m_color(p.m_color), m_tipo(p.m_tipo), pos(p.pos) {}
	Fantasma(char sprite, const char* color, Tipo_Fantasma tipo, Coords_t pos) 
		: m_sprite(sprite), m_color(color), m_tipo(tipo), pos(pos) {}

	std::string get_color() const { return m_color; }
	Tipo_Fantasma get_tipo() const { return m_tipo; }

	Fantasma& operator=(const Fantasma& p) { m_sprite = p.m_sprite; m_color = p.m_color; return *this; }

	friend std::ostream& operator<<(std::ostream& os, const Fantasma& p) { return os << p.m_color << p.m_sprite; }


	void mover(const PacMan& p, const Mapa_t& mapa) {
		const auto ultima_posicion = pos;

		switch (m_tipo) {
			case BLINKY: {
				mover_blinky(p);
				break;
			}
			case PINKY: {
				mover_pinky(p);
				break;
			}
			case INKY: {
				mover_inky(p);
				break;
			}
			case CLYDE: {
				mover_clyde(p);
				break;
			}

			default: 
				throw std::runtime_error("Tipo de fantasma Invalido");
				break;
		}

		corregir_posicion(ultima_posicion, mapa);
	}
private:
	char          m_sprite;
	const char*   m_color;
	Tipo_Fantasma m_tipo;
public:
	Coords_t      pos;
private:
	static Coords_t _Mover(Coords_t, int);

	void corregir_posicion(const Coords_t& ultima_posicion, const Mapa_t& mapa) {
		auto pos_invalida = [](const Pieza& p) {
			return p != Piezas.at(Tipo_Pieza::PACMAN) && p != Piezas.at(Tipo_Pieza::PUNTOS) && p != Piezas.at(Tipo_Pieza::VACIO);
		};
		
		Pieza pieza = mapa.at(pos.first).at(pos.second);

		while (pos_invalida(pieza)) {
			pos = ultima_posicion;
			int random = (rand() % 3) + 1;
			pos = _Mover(pos, random);
			pieza = mapa.at(pos.first).at(pos.second);
		}
	}

	void mover_blinky(const PacMan& p) {
    if (p.pos.first < pos.first)        { pos.first--; } 
		else if (p.pos.first > pos.first)   { pos.first++; }
		if (p.pos.second < pos.second)      { pos.second--; } 
		else if (p.pos.second > pos.second) { pos.second++; }
	}

	void mover_pinky(const PacMan& p) {
		int64_t pac_x = p.pos.first;
    int64_t pac_y = p.pos.second;
    int64_t ghost_x = pos.first;
    int64_t ghost_y = pos.second;

    int64_t pac_dir_x = pac_x - p.prev_pos.first;
    int64_t pac_dir_y = pac_y - p.prev_pos.second;

    int64_t target_x = pac_x + 4 * pac_dir_x;
    int64_t target_y = pac_y + 4 * pac_dir_y;

    if (ghost_x < target_x)      { pos.first++; } 
		else if (ghost_x > target_x) { pos.first--; }
    if (ghost_y < target_y)      { pos.second++; } 
		else if (ghost_y > target_y) { pos.second--; }
	}

	void mover_inky(const PacMan& p) {

	}

	void mover_clyde(const PacMan& p) {

	}
};

Coords_t Fantasma::_Mover(Coords_t position, int _RandomNumber) {
	switch (_RandomNumber) {
		case 1: position.first++;  break;
		case 2: position.first--;  break;
		case 3: position.second++; break;
		case 4: position.second--; break;
		default: 
			std::invalid_argument("_RandomNumber invalido! " + std::to_string(_RandomNumber) + " no es un argumento valido");
			break;
	}

	return position;
}