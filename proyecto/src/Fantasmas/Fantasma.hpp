#pragma once

#pragma once

#include <ostream>
#include <cmath>
#include <array>

extern "C" {
	#include <time.h>
}

#include "../Mapa.hpp"
#include "../PacMan.hpp"
#include "../Pieza.hpp"

#define FILAS_SIZE 31
#define COLUMNAS_SIZE 28

using Coords_t = std::pair<int64_t, int64_t>;

#define DEFAULT_TIMER_SALIDA 10
#define DEFAULT_TIMER_MOV_FANTASMAS 2
#define DEFAULT_CONTADOR_MOVIMIENTOS_SALIDA 3
#define DEFAULT_RESET_TIMER 40

struct Fantasma {
	std::size_t timerMovFantasmas = DEFAULT_TIMER_MOV_FANTASMAS;
	bool        huyendo = false;
	Coords_t    pos;
private:
	std::size_t _contadorMovimientosSalida = DEFAULT_CONTADOR_MOVIMIENTOS_SALIDA;
	std::size_t _timerSalida               = DEFAULT_TIMER_SALIDA;
	std::size_t _resetTimer                = DEFAULT_RESET_TIMER;
	bool        _barreraActiva = false;
	bool        _enojado       = false;
	char        _sprite;
	Coords_t    _initPos;
public:
	Fantasma();
	Fantasma(char, const Coords_t&);

	void resetear(bool);
	void mover(const PacMan&, Mapa&);
	void murio();
	void setHuyendo();
	void setEnojado();

	friend std::ostream& operator<<(std::ostream&, const Fantasma&);
protected:
	// funcion virtual (abstracta) _GetColor
	virtual std::string _GetColor() const = 0;
	// funcion virtual (abstracta) _SeguirPacman
	virtual void _SeguirPacman(const PacMan&) = 0;

	static Coords_t _MoverRandom(Coords_t, int);
	static Coords_t _MoverFantasma(Coords_t, const Coords_t&, const Coords_t&);

	void _CorregirPosicion(const Coords_t&, const Mapa&);
	void _Huir(const PacMan&);
};

Fantasma::Fantasma() = default;

Fantasma::Fantasma(char sprite, const Coords_t& pos) : pos(pos), _sprite(sprite), _initPos(pos) {}

std::ostream& operator<<(std::ostream& os, const Fantasma& p) { 
	// si esta huyendo, color cyan, si no, si esta enojado, rojo y si no el color que sea el fantasma
	const auto colorFantasma = (p.huyendo) ? color.cyan : (p._enojado) ? color.red : p._GetColor();
	// lo imprimo
	return os << colorFantasma << p._sprite;
}

void Fantasma::resetear(bool resetear_siempre = false) {
	// si esta huyendo o enojado y el timer esta a 1 resetea el timer 
	if (((huyendo || _enojado) && _resetTimer == 1) || resetear_siempre) {
		_resetTimer = DEFAULT_RESET_TIMER;
		huyendo = false;
		_enojado = false;
		timerMovFantasmas = DEFAULT_TIMER_MOV_FANTASMAS;
		return;
	}

	// si no, si esta huyendo o enojado, disminuyo el timer
	if (huyendo || _enojado) {
		_resetTimer--;
	}
}

// mueve al pacman
void Fantasma::mover(const PacMan& p, Mapa& mapa) {
	if (_timerSalida > 0) {
		_timerSalida--;
		return;
	} 
	
	if (huyendo) {
		const auto ultima_posicion = pos;
		_Huir(p);
		_CorregirPosicion(ultima_posicion, mapa);
		return;
	}
	
	const auto ultima_posicion = pos;

	if (_contadorMovimientosSalida > 0) {
		_contadorMovimientosSalida--;
		pos.first--;
		for (std::size_t j = 12; j <= 15; j++) {
			mapa.at(12).at(j) = Piezas.at(Tipo_Pieza::VACIO);
		}
	} 
	
	else {
		if (!_barreraActiva) {
			for (std::size_t j = 12; j <= 15; j++) {
				mapa.at(12).at(j) = Piezas.at(Tipo_Pieza::BARRERA);
			}
		}

		_SeguirPacman(p);
	}

	_CorregirPosicion(ultima_posicion, mapa);
}

// corrige la posicion del pacman
void Fantasma::_CorregirPosicion(const Coords_t& ultima_posicion, const Mapa& mapa) {
	static auto posInvalida = [](const Pieza& p) {
		return 
		p != Piezas.at(Tipo_Pieza::PACMAN) && 
		p != Piezas.at(Tipo_Pieza::PUNTOS) && 
		p != Piezas.at(Tipo_Pieza::FRUTA) && 
		p != Piezas.at(Tipo_Pieza::VACIO);
	};

	Pieza pieza = mapa.at(pos.first).at(pos.second);

	while (posInvalida(pieza)) {
		pos = ultima_posicion;
		int random = (rand() % 3) + 1;
		pos = _MoverRandom(pos, random);
		pieza = mapa.at(pos.first).at(pos.second);
	}
}

void Fantasma::_Huir(const PacMan& p) {
  int64_t move_x = (pos.first - p.pos.first > 0)   ? 1 : -1;
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

Coords_t Fantasma::_MoverFantasma(Coords_t pos, const Coords_t& ghost, const Coords_t& pac) {
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
	} else if (ghost.second < pac.second) {
		pos.second++;
	} else if (ghost.second > pac.second) {
		pos.second--;
	}

	return pos;
}

void Fantasma::murio() {
	pos = _initPos;
	_barreraActiva = false;
	_timerSalida = DEFAULT_TIMER_SALIDA;
	_contadorMovimientosSalida = DEFAULT_CONTADOR_MOVIMIENTOS_SALIDA;
	resetear(true);
}

void Fantasma::setHuyendo() {
	huyendo = true;
	_resetTimer = DEFAULT_RESET_TIMER;
	timerMovFantasmas = 3;
}

void Fantasma::setEnojado() {
	_enojado = true;
	_resetTimer = DEFAULT_RESET_TIMER;
	timerMovFantasmas = 1;
}