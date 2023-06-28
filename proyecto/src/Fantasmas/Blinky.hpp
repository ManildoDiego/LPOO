#pragma once

#include "Fantasma.hpp"

struct Blinky final : public Fantasma {
	using Fantasma::Fantasma;
	
	std::string get_color() const override { return color.red; }
protected:
	void seguir_pacman(const PacMan& p) override {
		pos = _MoverFantasma(pos, pos, p.pos);
	}
};

