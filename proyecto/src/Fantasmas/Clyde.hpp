#pragma once

#include "Fantasma.hpp"

struct Clyde final : public Fantasma {
	using Fantasma::Fantasma;

	std::string get_color() const override { return color.orange; }
protected:
	void seguir_pacman(const PacMan& p) override {
		static const double SEGUIR_PACMAN = 8;
		const double distance = std::sqrt(std::pow(p.pos.first - pos.first, 2) + std::pow(p.pos.second - pos.second, 2));

		if (distance >= SEGUIR_PACMAN) {
			pos = _MoverFantasma(pos, pos, p.pos);
			return;
		}

		const int random = (rand() % 3) + 1;
		pos = _MoverRandom(pos, random);
	}
};