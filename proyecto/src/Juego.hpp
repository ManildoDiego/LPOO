#pragma once

#include <cctype>
#include <vector>
#include <string>
#include <algorithm>

#include "Pieza.hpp"
#include "PacMan.hpp"
#include "manejoConsola.hpp"
#include "puntuacion.hpp"
#include "Mapa.hpp"

extern "C" {
	#include <time.h>
}

#include "Fantasmas/Blinky.hpp"
#include "Fantasmas/Pinky.hpp"
#include "Fantasmas/Inky.hpp"
#include "Fantasmas/Clyde.hpp"

extern std::vector<std::pair<std::string, char>> controles;

#define FILAS_SIZE 31
#define COLUMNAS_SIZE 28

#define ARRIBA    static_cast<char>(72)
#define ABAJO     static_cast<char>(80)
#define DERECHA   static_cast<char>(77)
#define IZQUIERDA static_cast<char>(75)

#define MOVER_ARRIBA(k)    (k == ARRIBA    || k == controles.at(0).second)
#define MOVER_ABAJO(k)     (k == ABAJO     || k == controles.at(1).second)
#define MOVER_DERECHA(k)   (k == DERECHA   || k == controles.at(2).second)
#define MOVER_IZQUIERDA(k) (k == IZQUIERDA || k == controles.at(3).second)

#define DEFAULT_SPRITE static_cast<char>(1)

class Juego final {
	using Coords_t = std::pair<int64_t, int64_t>;

	const std::size_t maxPuntuacion;
	const std::string maxNombre;

	Mapa           _mapa{};
	const Coords_t _pacmanInitPos = {17, 13};
	char           _anterior = '\0';

	std::size_t _puntuacion        = 0;
	std::size_t _vidas             = 3;
	std::size_t _moverFantasma     = 0;
	std::size_t _timerMovFantasmas = 2;

	// vector de punteros de fantasmas (clases abstractas)
	std::vector<Fantasma*> _fantasmas = {
		new Blinky( DEFAULT_SPRITE, {14, 12} ),
		new Pinky ( DEFAULT_SPRITE, {14, 13} ),
		new Inky  ( DEFAULT_SPRITE, {14, 14} ),
		new Clyde ( DEFAULT_SPRITE, {14, 15} ),
	};

	void _ComprobarColisionesFantasmas();
	void _ActualizarFantasmas();
	void _ComprobarColisiones();
	bool _PosicionValida(const Pieza&);
	bool _PosicionValida(const Coords_t&);
public:
	PacMan pacman;

	Juego();
	~Juego();

	friend std::ostream& operator<<(std::ostream&, const Juego&);

	void actualizar(char);
	bool gano();
	bool murio() { return _vidas < 1; }
	std::size_t getPuntuacion() const { return _puntuacion; }
};

Juego::Juego() : maxPuntuacion(leerPuntuacion()), maxNombre(leerNombre()) {
	pacman.pos = _pacmanInitPos;
	pacman.prevPos = pacman.pos;
}

Juego::~Juego() {
	// si la puntuacion actual, es mayor que la maxima, lo guarda
	if (_puntuacion > maxPuntuacion) {
		system("cls");
		std::string nombre{};
		std::cout << "Nueva maxima puntuacion!: " << _puntuacion << std::endl;
		setCursorConsola(true);
		std::cout << "Ingrese nombre del jugador: ";

		while (nombre.empty() || nombre == "NULL" || std::all_of(nombre.begin(), nombre.end(), [](int c) { return std::isspace(c); })) {
      std::getline(std::cin, nombre);
    }

		setCursorConsola(false);

		guardarNombre(nombre);
		guardarPuntuacion(_puntuacion);
	}
}

void Juego::_ComprobarColisionesFantasmas() {
	for (const auto& f : _fantasmas) {
		if (f->pos == pacman.pos) {
			if (f->huyendo) {
				f->murio();
				_puntuacion += 500;
			} 
			
			else {
				pacman.pos = _pacmanInitPos;
				_vidas--;
				system("cls");
				break;
			}
		}
	}
}

void Juego::_ActualizarFantasmas() {
	_moverFantasma++;
	if ((_moverFantasma % _timerMovFantasmas) == 0) {
		for (auto& f : _fantasmas) {
			f->mover(pacman, _mapa);
		}
	}
}

void Juego::_ComprobarColisiones() {
	_ComprobarColisionesFantasmas();
	
	auto is_hitting = [&](Tipo_Pieza pieza) {
		return _mapa.at(pacman.pos.first).at(pacman.pos.second) == Piezas.at(pieza);
	};
	
	if (is_hitting(Tipo_Pieza::FRUTA)) {
		srand(static_cast<unsigned int>(time(0)));

		bool fruta_trampa = ((rand() % 4) == 0);
		_puntuacion += 300;
		_mapa.at(pacman.pos.first).at(pacman.pos.second) = Piezas.at(Tipo_Pieza::VACIO);

		if (fruta_trampa) {
			for (auto& f : _fantasmas) {
				f->enojado = true;
				f->resetTimer = 40;
			}

			_timerMovFantasmas = 1;
		} else {
			for (auto& f : _fantasmas) {
				f->huyendo = true;
				f->resetTimer = 40;
			}

			_timerMovFantasmas = 3;
		}
	}

	else if (is_hitting(Tipo_Pieza::PUNTOS)) {
		_puntuacion += 100;
		_mapa.at(pacman.pos.first).at(pacman.pos.second) = Piezas.at(Tipo_Pieza::VACIO);
	}

	for (auto& f : _fantasmas) {
		bool reset = f->resetear();
		if (reset) {
			_timerMovFantasmas = 2;
		}
	}
}

bool Juego::_PosicionValida(const Pieza& p) {
	return 
		p == Piezas.at(Tipo_Pieza::PACMAN) ||
		p == Piezas.at(Tipo_Pieza::PUNTOS) ||
		p == Piezas.at(Tipo_Pieza::VACIO)  ||
		p == Piezas.at(Tipo_Pieza::FRUTA);
}

bool Juego::_PosicionValida(const Coords_t& c) {
	const auto& p = _mapa.at(c.first).at(c.second);

	return _PosicionValida(p);
}

void Juego::actualizar(char k) {
	const auto old_position = pacman.pos;

	if (pacman.pos == Coords_t{14, 0} && MOVER_IZQUIERDA(k)) {
		pacman.setPos({14, COLUMNAS_SIZE-1});
	}

	else if (pacman.pos == Coords_t{14, COLUMNAS_SIZE-1} && MOVER_DERECHA(k)) {
		pacman.setPos({14, 0});
	}

	else if (MOVER_ARRIBA(k))    { pacman.setPos(pacman.pos.first-1, pacman.pos.second); }
	else if (MOVER_ABAJO(k))     { pacman.setPos(pacman.pos.first+1, pacman.pos.second); }
	else if (MOVER_DERECHA(k))   { pacman.setPos(pacman.pos.first, pacman.pos.second+1); }
	else if (MOVER_IZQUIERDA(k)) { pacman.setPos(pacman.pos.first, pacman.pos.second-1); }

	const auto& pieza = _mapa.at(pacman.pos.first).at(pacman.pos.second); 

	if (!_PosicionValida(pieza)) {
		pacman.setPos(old_position, true);
	}
	
	_ActualizarFantasmas();
	_ComprobarColisiones();
}

bool Juego::gano() {
	for (const auto& fila : _mapa) {
		for (const auto& p : fila) {
			if (p == Piezas.at(Tipo_Pieza::PUNTOS)) {
				return false;
			}

			if (p == Piezas.at(Tipo_Pieza::FRUTA)) {
				return false;
			}
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream& os, const Juego& juego) {
	const auto offset_x = getCentroConsola().first;
	Coords_t xy;
	
	bool habiaFantasma = false;

	for (std::size_t i = 0; i < juego._mapa.filas; i++) {
		gotoxy(offset_x, i);
		for (std::size_t j = 0; j < juego._mapa.columnas; j++) {
			xy = {i, j};
			
			for (const auto& f : juego._fantasmas) {
				if (f->pos == xy) {
					os << *f;
					habiaFantasma = true;
					break;
				}
			}

			if (habiaFantasma) {
				habiaFantasma = false;
				continue;
			}

			if (juego.pacman.pos == xy) {
				os << juego.pacman;
				continue;
			}
			
			os << juego._mapa.at(i).at(j);
		}
		os << '\n';
	}

	gotoxy(offset_x, juego._mapa.filas);
	for (std::size_t i = 0; i < juego._vidas; i++) {
		os << juego.pacman << ' ';
	}

	gotoxy(offset_x+juego._mapa.columnas, 0);
	os << color.magenta << "Puntos: " << juego._puntuacion;

	if (juego.maxNombre != "NULL") {
		gotoxy(offset_x+juego._mapa.columnas, 3);
		os << color.blue << "Maxima puntuacion: " << juego.maxPuntuacion << " hecha por \"" << juego.maxNombre << "\"";
	}

	os << color.reset;

	return os;
}
