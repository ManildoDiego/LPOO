#pragma once

#include "Pieza.hpp"
#include "PacMan.hpp"

struct PacMan {
	// declaro que Coords_t = std::pair<int64_t, int64_t>
	using Coords_t = std::pair<int64_t, int64_t>;

	// pieza del pacman
	const Pieza pieza  = Piezas.at(Tipo_Pieza::PACMAN);
	// posicion del pacman
	Coords_t pos      = {1, 1};
	// posicion del pacman previa para que los fantasmas puedan predecir movimientos
	Coords_t prev_pos = {1, 1};
	
	// metodo set pos en base a coordenadas
	void setPos(const Coords_t&, bool);
	// sobrecarga del metodo set pos en base a x e y
	void setPos(int64_t, int64_t, bool);

	// metodo para imprimir el pacman
	friend std::ostream& operator<<(std::ostream& os, const PacMan& pac);
};

void PacMan::setPos(const Coords_t& new_pos, bool change = false) {
	if (!change) {
		prev_pos = pos;
	}

	pos = new_pos;
}

void PacMan::setPos(int64_t x, int64_t y, bool change = false) { 
	setPos({x, y}, change);
}

std::ostream& operator<<(std::ostream& os, const PacMan& pac) { 
	// imprimo la pieza del pacman (el sprite)
	return os << pac.pieza;
}