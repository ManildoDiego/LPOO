#pragma once

#include <cctype>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

#include "Pieza.hpp"
#include "PacMan.hpp"
#include "manejoConsola.hpp"
#include "puntuacion.hpp"
#include "Mapa.hpp"

#include "Fantasmas/Blinky.hpp"
#include "Fantasmas/Pinky.hpp"
#include "Fantasmas/Inky.hpp"
#include "Fantasmas/Clyde.hpp"

extern std::vector<Tecla_t> controles;

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

	Data_t maxPuntuacion;

	Mapa        _mapa{};
	std::size_t _puntuacion    = 0;
	std::size_t _moverFantasma = 0;

	// vector de punteros de fantasmas (clases abstractas)
	std::vector<Fantasma*> _fantasmas = {
		new Blinky( DEFAULT_SPRITE, {14, 12} ),
		new Pinky ( DEFAULT_SPRITE, {14, 13} ),
		new Inky  ( DEFAULT_SPRITE, {14, 14} ),
		new Clyde ( DEFAULT_SPRITE, {14, 15} ),
	};

	PacMan _pacman;

	void _ComprobarColisionesFantasmas();
	void _ActualizarFantasmas();
	void _ComprobarColisiones();
	bool _PosicionValida(const Pieza&);
	bool _PosicionValida(const Coords_t&);
public:

	Juego();
	~Juego();

	friend std::ostream& operator<<(std::ostream&, const Juego&);

	void actualizar(char);
	bool gano();
	bool murio() const { return _pacman.estaMuerto(); }
	std::size_t getPuntuacion() const { return _puntuacion; }
};

Juego::Juego() : maxPuntuacion(leerData()) {}

Juego::~Juego() {
	system("cls");
	std::string nombre{};
	gotoxy(getCentroConsola());
	setCursorConsola(true);
	std::cout << "Ingrese nombre del jugador: ";

	while (nombre.empty() || nombre == "NULL" || std::all_of(nombre.begin(), nombre.end(), [](int c) { return std::isspace(c); })) {
    std::cin >> nombre;
  }

	setCursorConsola(false);

	if (maxPuntuacion != NULLDATA) {
		maxPuntuacion.push_back({nombre, _puntuacion});
	} else {
		maxPuntuacion[0] = {nombre, _puntuacion};
	}

	guardarData(maxPuntuacion);
}

void Juego::_ComprobarColisionesFantasmas() {
	for (const auto& f : _fantasmas) {
		if (f->pos == _pacman.getPos()) {
			if (f->huyendo) {
				f->murio();
				_puntuacion += 500;
			}
			
			else {
				_pacman.murio();
				system("cls");
				break;
			}
		}
	}
}

void Juego::_ActualizarFantasmas() {
	_moverFantasma++;

	for (auto& f : _fantasmas) {
		if ((_moverFantasma % f->timerMovFantasmas) == 0) {
			f->mover(_pacman, _mapa);
		}
	}
}

void Juego::_ComprobarColisiones() {
	_ComprobarColisionesFantasmas();
	
	auto is_hitting = [&](Tipo_Pieza pieza) {
		return _mapa.at(_pacman.getPos().first).at(_pacman.getPos().second) == Piezas.at(pieza);
	};
	
	if (is_hitting(Tipo_Pieza::FRUTA)) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		bool fruta_trampa = ((std::rand() % 4) == 0); // 25%

		_puntuacion += 300;
		_mapa.at(_pacman.getPos().first).at(_pacman.getPos().second) = Piezas.at(Tipo_Pieza::VACIO);

		if (fruta_trampa) {
			for (auto& f : _fantasmas) {
				f->setEnojado();
			}
		} 
		
		else {
			for (auto& f : _fantasmas) {
				f->setHuyendo();
			}
		}
	}

	else if (is_hitting(Tipo_Pieza::PUNTOS)) {
		_puntuacion += 100;
		_mapa.at(_pacman.getPos().first).at(_pacman.getPos().second) = Piezas.at(Tipo_Pieza::VACIO);
	}

	for (auto& f : _fantasmas) {
		f->resetear();
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
	const auto old_position = _pacman.getPos();

	if (_pacman.getPos() == Coords_t{14, 0} && MOVER_IZQUIERDA(k)) {
		_pacman.setPos({14, COLUMNAS_SIZE-1});
	}

	else if (_pacman.getPos() == Coords_t{14, COLUMNAS_SIZE-1} && MOVER_DERECHA(k)) {
		_pacman.setPos({14, 0});
	}

	else if (MOVER_ARRIBA(k))    { _pacman.setPos(_pacman.getPos().first-1, _pacman.getPos().second); }
	else if (MOVER_ABAJO(k))     { _pacman.setPos(_pacman.getPos().first+1, _pacman.getPos().second); }
	else if (MOVER_DERECHA(k))   { _pacman.setPos(_pacman.getPos().first, _pacman.getPos().second+1); }
	else if (MOVER_IZQUIERDA(k)) { _pacman.setPos(_pacman.getPos().first, _pacman.getPos().second-1); }

	if (!_PosicionValida(_pacman.getPos())) {
		_pacman.setPos(old_position, true);
	}
	
	_ActualizarFantasmas();
	_ComprobarColisiones();
}

bool Juego::gano() {
	for (const auto& fila : _mapa) {
		for (const auto& p : fila) {
			if (p == Piezas.at(Tipo_Pieza::PUNTOS) || p == Piezas.at(Tipo_Pieza::FRUTA)) {
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

			if (juego._pacman.getPos() == xy) {
				os << juego._pacman;
				continue;
			}
			
			os << juego._mapa.at(i).at(j);
		}
		os << '\n';
	}

	gotoxy(offset_x, juego._mapa.filas);
	for (std::size_t i = 0; i < juego._pacman.getVidas(); i++) {
		os << juego._pacman << ' ';
	}

	gotoxy(offset_x+juego._mapa.columnas, 0);
	os << color.magenta << "Puntos: " << juego._puntuacion;

	os << color.reset;

	return os;
}
