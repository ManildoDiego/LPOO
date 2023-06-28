#pragma once

#include "Fantasma.hpp"

struct Pinky final : public Fantasma {
	using Fantasma::Fantasma;
	
	std::string get_color() const override { return color.magenta; }
protected:
	void _M_mover(const PacMan& p) override {
		const int64_t target_x = p.pos.first + 4 * (p.pos.first - p.prev_pos.first);
		const int64_t target_y = p.pos.second + 4 * (p.pos.second - p.prev_pos.second);

		pos = _MoverFantasma(pos, pos, {target_x, target_y});
	}
};