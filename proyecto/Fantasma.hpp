#pragma once

#include <ostream>
#include <cmath>

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

#define FILAS_SIZE 31
#define COLUMNAS_SIZE 28

using Mapa_t = std::array<std::array<Pieza, COLUMNAS_SIZE>, FILAS_SIZE>;
using Coords_t = std::pair<int64_t, int64_t>;

enum class Tipo_Fantasma {
	null,

	BLINKY, // Rojo
	PINKY,  // Rosa
	INKY,   // Azul
	CLYDE,  // Naranja
};

class Fantasma {
	char          m_sprite;
	const char*   m_color;
	const char*   m_old_color;
	Tipo_Fantasma m_tipo;
	std::size_t   timer_salida = 3;
	bool          barrera_activa = false;
	std::size_t   reset_timer = 80;
public:
	Coords_t pos;
	std::size_t contador_movimientos_salida = 3;
	bool huyendo = false;
public:
	Fantasma();
	Fantasma(const Fantasma&);
	Fantasma(char, const char*, Tipo_Fantasma, Coords_t);

	std::string get_color() const;
	Fantasma& operator=(const Fantasma&);
	void change_color(const char*);
	void resetear();
	void mover(const PacMan&, Mapa_t&);

	friend std::ostream& operator<<(std::ostream&, const Fantasma&);
private:
	static Coords_t _MoverRandom(Coords_t, int);
	static Coords_t _Mover(Coords_t, Coords_t, Coords_t);
	void corregir_posicion(const Coords_t&, const Mapa_t&);
	void mover_blinky(const PacMan&);
	void mover_pinky(const PacMan&);
	void mover_inky(const PacMan&);
	void mover_clyde(const PacMan&);
	void huir(const PacMan&);
};

std::string Fantasma::get_color() const { return m_color; }

Fantasma::Fantasma() = default;
Fantasma::Fantasma(const Fantasma& p) 
	: m_sprite(p.m_sprite), m_color(p.m_color), m_old_color(m_color), m_tipo(p.m_tipo), pos(p.pos) {}
Fantasma::Fantasma(char sprite, const char* color, Tipo_Fantasma tipo, Coords_t pos) 
	: m_sprite(sprite), m_color(color), m_old_color(m_color), m_tipo(tipo), pos(pos) {}

Fantasma& Fantasma::operator=(const Fantasma& p) { 
	m_sprite = p.m_sprite;
	m_color = p.m_color;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Fantasma& p) { return os << p.m_color << p.m_sprite; }

void Fantasma::change_color(const char* color) {
	m_color = color;
}

void Fantasma::resetear() {
	if (huyendo && reset_timer == 1) {
		reset_timer = 80;
		m_color = m_old_color;
		huyendo = false;
		return;
	}

	if (huyendo) {
		reset_timer--;
	}
}

void Fantasma::mover(const PacMan& p, Mapa_t& mapa) {
	if (huyendo) {
		const auto ultima_posicion = pos;
		huir(p);
		corregir_posicion(ultima_posicion, mapa);
		return;
	}
	
	if (timer_salida > 0) {
		timer_salida--;
		return;
	} 
	
	const auto ultima_posicion = pos;

	if (contador_movimientos_salida > 0) {
		contador_movimientos_salida--;
		pos.first--;
	} else {
		if (!barrera_activa) {
			for (std::size_t j = 12; j <= 15; j++) {
				mapa.at(12).at(j) = Piezas.at(Tipo_Pieza::BARRERA);
			}
		}

		switch (m_tipo) {
			case Tipo_Fantasma::BLINKY: {
				mover_blinky(p);
				break;
			}
			case Tipo_Fantasma::PINKY: {
				mover_pinky(p);
				break;
			}
			case Tipo_Fantasma::INKY: {
				mover_inky(p);
				break;
			}
			case Tipo_Fantasma::CLYDE: {
				mover_clyde(p);
				break;
			}

			default: 
				throw std::runtime_error("Tipo de fantasma Invalido");
				break;
		}
	}

	corregir_posicion(ultima_posicion, mapa);
}

void Fantasma::corregir_posicion(const Coords_t& ultima_posicion, const Mapa_t& mapa) {
	auto pos_invalida = [](const Pieza& p) {
		return p != Piezas.at(Tipo_Pieza::PACMAN) && p != Piezas.at(Tipo_Pieza::PUNTOS) && p != Piezas.at(Tipo_Pieza::VACIO);
	};
	
	Pieza pieza = mapa.at(pos.first).at(pos.second);

	while (pos_invalida(pieza)) {
		pos = ultima_posicion;
		int random = (rand() % 3) + 1;
		pos = _MoverRandom(pos, random);
		pieza = mapa.at(pos.first).at(pos.second);
	}
}

void Fantasma::mover_blinky(const PacMan& p) {
	pos = _Mover(pos, pos, p.pos);
}

void Fantasma::mover_pinky(const PacMan& p) {
	int64_t target_x = p.pos.first + 4 * (p.pos.first - p.prev_pos.first);
	int64_t target_y = p.pos.second + 4 * (p.pos.second - p.prev_pos.second);

	pos = _Mover(pos, pos, {target_x, target_y});
}

void Fantasma::mover_inky(const PacMan& p) {
	int64_t target_x = p.pos.first + 2 * (p.pos.first - pos.first);
	int64_t target_y = p.pos.second + 2 * (p.pos.second - pos.second);

	pos = _Mover(pos, pos, {target_x, target_y});
}

void Fantasma::mover_clyde(const PacMan& p) {
	const double SEGUIR_PACMAN = 8;
	double distance = std::sqrt(std::pow(p.pos.first - pos.first, 2) + std::pow(p.pos.second - pos.second, 2));

	if (distance >= SEGUIR_PACMAN) {
		pos = _Mover(pos, pos, p.pos);
		return;
	}

	int random = (rand() % 3) + 1;
	pos = _MoverRandom(pos, random);
}

void Fantasma::huir(const PacMan& p) {
  int64_t move_x = (pos.first - p.pos.first > 0) ? 1 : -1;
  int64_t move_y = (pos.second - p.pos.second > 0) ? 1 : -1;

	if (pos == Coords_t{14, 0} && move_y == -1) { // IZQUIERDA
		pos = {14, COLUMNAS_SIZE-1};
		return;
	}

	if (pos == Coords_t{14, COLUMNAS_SIZE-1} && move_y == 1) { // DERECHA
		pos = {14, 0};
		return;
	}
	
	pos.first += move_x;
  pos.second += move_y;
}

Coords_t Fantasma::_MoverRandom(Coords_t position, int _RandomNumber) {
	if (position == Coords_t{14, 0} && _RandomNumber == 4) { // IZQUIERDA
		return {14, COLUMNAS_SIZE-1};
	}

	else if (position == Coords_t{14, COLUMNAS_SIZE-1} && _RandomNumber == 3) { // DERECHA
		return {14, 0};
	}
	
	switch (_RandomNumber) {
		case 1: position.first++;  break;
		case 2: position.first--;  break;
		case 3: position.second++; break;
		case 4: position.second--; break;
		default: 
			std::invalid_argument("_RandomNumber invalido! " + std::to_string(_RandomNumber) + " no es un argumento valido (1-4)");
			break;
	}

	return position;
}

Coords_t Fantasma::_Mover(Coords_t pos, Coords_t ghost, Coords_t pac) {
	if (pos == Coords_t{14, 0} && ghost.second > pac.second) { // IZQUIERDA
		return {14, COLUMNAS_SIZE-1};
	}

	if (pos == Coords_t{14, COLUMNAS_SIZE-1} && ghost.second < pac.second) { // DERECHA
		return {14, 0};
	}

	
	if (ghost.first < pac.first) {
		pos.first++;
	} else if (ghost.first > pac.first) {
		pos.first--;
	}


	if (ghost.second < pac.second) {
		pos.second++;
	} else if (ghost.second > pac.second) {
		pos.second--;
	}

	return pos;
}