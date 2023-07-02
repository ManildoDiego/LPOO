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
		/*
			hecho con chat gpt
			la pregunta fue -> Necesito una funcion _SeguirPacman que p.pos prediga los movimientos de pacman a 4 casillas de distancia
		*/
		const auto target_x = p.getPos().first + 4 * (p.getPos().first - p.getPrevPos().first);
		const auto target_y = p.getPos().second + 4 * (p.getPos().second - p.getPrevPos().second);

		pos = _MoverFantasma(pos, pos, {target_x, target_y});
	}
};