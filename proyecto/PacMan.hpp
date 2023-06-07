#pragma once

#include "Pieza.hpp"
#include "PacMan.hpp"


struct PacMan {
	using Coords_t = std::pair<int64_t, int64_t>;
	Pieza pieza = Piezas.at(Tipo_Pieza::PACMAN);
	Coords_t pos = {1, 1};
	Coords_t prev_pos = {1, 1};

	friend std::ostream& operator<<(std::ostream& os, const PacMan& pac) { return os << pac.pieza; }
};