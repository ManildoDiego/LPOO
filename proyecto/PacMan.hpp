#pragma once

#include "Pieza.hpp"
#include "PacMan.hpp"

using Coords_t = std::pair<std::size_t, std::size_t>;

struct PacMan {
	Pieza pieza = Piezas.at(Tipo_Pieza::PACMAN);
	Coords_t pos = {1, 1};

	friend std::ostream& operator<<(std::ostream& os, const PacMan& pac) { return os << pac.pieza; }
};