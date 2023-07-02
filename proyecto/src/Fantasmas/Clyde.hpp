#pragma once

#include "Fantasma.hpp"

// clase derivada de fantasma
struct Clyde final : public Fantasma {
	// uso el mismo constructor de la clase Fantasma
	using Fantasma::Fantasma;

	// sobreescribo el metodo _GetColor
	std::string _GetColor() const override { return color.orange; }
protected:
	// sobreescribo el metodo _SeguirPacman
	void _SeguirPacman(const PacMan& p) override {
		/*
			hecho con chat gpt
			la pregunta fue -> Necesito una funcion _SeguirPacman que si p.pos sea mayor o igual que la distancia del pacman lo siga
		*/
		static const double SEGUIR_PACMAN = 8;
		const double distance = std::sqrt(std::pow(p.getPos().first - pos.first, 2) + std::pow(p.getPos().second - pos.second, 2));

		if (distance >= SEGUIR_PACMAN) {
			pos = _MoverFantasma(pos, pos, p.getPos());
			return;
		}

		const int random = (rand() % 3) + 1;
		pos = _MoverRandom(pos, random);
	}
};