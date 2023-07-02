#pragma once

#include "Fantasma.hpp"

// clase derivada de fantasma
struct Blinky final : public Fantasma {
	// uso el mismo constructor de la clase Fantasma
	using Fantasma::Fantasma;
	
	// sobreescribo el metodo _GetColor
	std::string _GetColor() const override { return color.red; }
protected:
	// sobreescribo el metodo _SeguirPacman
	void _SeguirPacman(const PacMan& p) override {
		pos = _MoverFantasma(pos, pos, p.getPos());
	}
};

