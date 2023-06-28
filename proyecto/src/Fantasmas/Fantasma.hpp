#pragma once

#pragma once

#include <ostream>
#include <cmath>
#include <array>

extern "C" {
	#include <time.h>
}

#include "../PacMan.hpp"
#include "../Pieza.hpp"

#define FILAS_SIZE 31
#define COLUMNAS_SIZE 28

using Mapa_t  = std::array<std::array<Pieza, COLUMNAS_SIZE>, FILAS_SIZE>;
using Coords_t = std::pair<int64_t, int64_t>;

class Fantasma {
	char          m_sprite;
	std::size_t   timer_salida = 3;
	bool          barrera_activa = false;
public:
	std::size_t   reset_timer = 40;
	Coords_t pos;
	Coords_t init_pos;
	std::size_t contador_movimientos_salida = 3;
	bool huyendo = false;
	bool enojado = false;
public:
	Fantasma();
	Fantasma(const Fantasma&);
	Fantasma(char, Coords_t);

	virtual std::string get_color() const = 0;

	Fantasma& operator=(const Fantasma&);
	bool resetear();
	void mover(const PacMan&, Mapa_t&);

	friend std::ostream& operator<<(std::ostream&, const Fantasma&);
protected:
	virtual void seguir_pacman(const PacMan&) = 0;

	static Coords_t _MoverRandom(Coords_t, int);
	static Coords_t _MoverFantasma(Coords_t, Coords_t, Coords_t);

	void corregir_posicion(const Coords_t&, const Mapa_t&);
	void huir(const PacMan&);
};

Fantasma::Fantasma() = default;

Fantasma::Fantasma(const Fantasma& p) : m_sprite(p.m_sprite), pos(p.pos) { 
	init_pos = p.init_pos;
}

Fantasma::Fantasma(char sprite, Coords_t pos) : m_sprite(sprite), pos(pos) { 
	init_pos = pos;
}

Fantasma& Fantasma::operator=(const Fantasma& p) { 
	m_sprite = p.m_sprite;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Fantasma& p) { 
	const auto f_color = (p.huyendo) ? color.cyan : (p.enojado) ? color.red : p.get_color();
	return os << f_color << p.m_sprite; 
}

bool Fantasma::resetear() {
	if ((huyendo || enojado) && reset_timer == 1) {
		reset_timer = 40;
		huyendo = false;
		enojado = false;
		return true;
	}

	if (huyendo || enojado) {
		reset_timer--;
	}

	return false;
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

		seguir_pacman(p);
	}

	corregir_posicion(ultima_posicion, mapa);
}

void Fantasma::corregir_posicion(const Coords_t& ultima_posicion, const Mapa_t& mapa) {
	auto pos_invalida = [](const Pieza& p) {
		return 
		p != Piezas.at(Tipo_Pieza::PACMAN) && 
		p != Piezas.at(Tipo_Pieza::PUNTOS) && 
		p != Piezas.at(Tipo_Pieza::VACIO);
	};
	
	Pieza pieza = mapa.at(pos.first).at(pos.second);

	while (pos_invalida(pieza)) {
		pos = ultima_posicion;
		int random = (rand() % 3) + 1;
		pos = _MoverRandom(pos, random);
		pieza = mapa.at(pos.first).at(pos.second);
	}
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

Coords_t Fantasma::_MoverFantasma(Coords_t pos, Coords_t ghost, Coords_t pac) {
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
