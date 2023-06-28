#pragma once

#include "Fantasma.hpp"

struct Inky final : public Fantasma {
	using Fantasma::Fantasma;
	
	std::string get_color() const override { return color.blue; }
protected:
	void seguir_pacman(const PacMan& p) override {
		const int64_t target_x = p.pos.first + 2 * (p.pos.first - pos.first);
		const int64_t target_y = p.pos.second + 2 * (p.pos.second - pos.second);

		pos = _MoverFantasma(pos, pos, {target_x, target_y});
	}
};