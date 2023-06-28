#pragma once

#include "Pieza.hpp"
#include "PacMan.hpp"

struct PacMan {
	using Coords_t = std::pair<int64_t, int64_t>;

	const Pieza pieza  = Piezas.at(Tipo_Pieza::PACMAN);
	Coords_t pos       = {1, 1};
	Coords_t prev_pos  = {1, 1};
	
	void set_pos(const Coords_t&, bool);
	void set_pos(int64_t, int64_t, bool);

	friend std::ostream& operator<<(std::ostream& os, const PacMan& pac);
};

void PacMan::set_pos(const Coords_t& new_pos, bool change = false) {
	if (!change) {
		prev_pos = pos;
	}

	pos = new_pos;
}

void PacMan::set_pos(int64_t x, int64_t y, bool change = false) { 
	set_pos({x, y}, change); 
}

std::ostream& operator<<(std::ostream& os, const PacMan& pac) { 
	return os << pac.pieza; 
}