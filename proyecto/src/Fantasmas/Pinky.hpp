#pragma once

#include "Fantasma.hpp"
// clase derivada de fantasma

struct Pinky final : public Fantasma {
	// uso el mismo constructor de la clase Fantasma
	using Fantasma::Fantasma;
	
	// sobreescribo el metodo _GetColor
	std::string _GetColor() const override { return color.magenta; }
protected:
	// sobreescribo el metodo _SeguirPacman
	void _SeguirPacman(const PacMan& p) override {
		const int64_t target_x = p.pos.first + 4 * (p.pos.first - p.prevPos.first);
		const int64_t target_y = p.pos.second + 4 * (p.pos.second - p.prevPos.second);

		pos = _MoverFantasma(pos, pos, {target_x, target_y});
	}
};