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

using Coords_t = std::pair<std::size_t, std::size_t>;

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
		: m_sprite(p.m_sprite), m_color(p.m_color), m_tipo(p.m_tipo), m_pos(p.m_pos) {}
	Fantasma(char sprite, const char* color, Tipo_Fantasma tipo, Coords_t pos) 
		: m_sprite(sprite), m_color(color), m_tipo(tipo), m_pos(pos) {}

	Coords_t get_pos() const { return m_pos; }
	std::string get_color() const { return m_color; }
	Tipo_Fantasma get_tipo() const { return m_tipo; }

	Fantasma& operator=(const Fantasma& p) { m_sprite = p.m_sprite; m_color = p.m_color; return *this; }

	friend std::ostream& operator<<(std::ostream& os, const Fantasma& p) { return os << p.m_color << p.m_sprite; }

	void mover(const PacMan& p) {
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
	}
private:
	char          m_sprite;
	const char*   m_color;
	Tipo_Fantasma m_tipo;
	Coords_t      m_pos;
private:
	void mover_blinky(const PacMan& p) {
		
	}

	void mover_pinky(const PacMan& p) {

	}

	void mover_inky(const PacMan& p) {

	}

	void mover_clyde(const PacMan& p) {

	}
};
