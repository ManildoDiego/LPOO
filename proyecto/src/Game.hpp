#pragma once

#include <array>
#include <vector>

#include "Pieza.hpp"
#include "PacMan.hpp"
#include "manejo_consola.hpp"

extern "C" {
	#include <time.h>
}

#define FILAS_SIZE 31
#define COLUMNAS_SIZE 28

extern std::vector<std::pair<const char*, char>> controles;
using Mapa_t = std::array<std::array<Pieza, COLUMNAS_SIZE>, FILAS_SIZE>;

#include "Fantasmas/Blinky.hpp"
#include "Fantasmas/Pinky.hpp"
#include "Fantasmas/Inky.hpp"
#include "Fantasmas/Clyde.hpp"

#define ARRIBA    static_cast<char>(72)
#define ABAJO     static_cast<char>(80)
#define DERECHA   static_cast<char>(77)
#define IZQUIERDA static_cast<char>(75)

#define MOVER_ARRIBA(k)    (k == ARRIBA    || k == controles.at(0).second)
#define MOVER_ABAJO(k)     (k == ABAJO     || k == controles.at(1).second)
#define MOVER_DERECHA(k)   (k == DERECHA   || k == controles.at(2).second)
#define MOVER_IZQUIERDA(k) (k == IZQUIERDA || k == controles.at(3).second)

#define DEFAULT_SPRITE static_cast<char>(1)

struct Game {
	using Coords_t = std::pair<int64_t, int64_t>;
	PacMan pacman;
private:
	const char* name_file = "Puntaje.txt";
	Mapa_t m_map{};

	const Coords_t pacman_init_pos = {17, 13};
	static const std::size_t filas    = FILAS_SIZE;
	static const std::size_t columnas = COLUMNAS_SIZE;
	std::size_t puntuacion = 0;
	std::size_t vidas = 3;
	std::size_t mover_fantasma = 0;
	std::size_t TIMER_MOV_FANTASMAS = 2;

	std::vector<Fantasma*> fantasmas = {
		new Blinky( DEFAULT_SPRITE, {14, 12} ),
		new Pinky ( DEFAULT_SPRITE, {14, 13} ),
		new Inky  ( DEFAULT_SPRITE, {14, 14} ),
		new Clyde ( DEFAULT_SPRITE, {14, 15} ),
	};

	void llenar_mapa(const Pieza&);
	void fill_fila(std::size_t, std::size_t, std::size_t, const Pieza&);
	void fill_columna(std::size_t, std::size_t, std::size_t, const Pieza&);
	void crear_rectangulo(Coords_t, std::size_t, std::size_t);
	void modificar_posicion(const char*);
	void comprobar_colisiones_fantasmas();
	void actualizar_fantasmas();
	void crear_frutas();
	void comprobar_colisiones_fruta();
	bool posicion_valida(const Pieza&);
	void crear_disenio();
public:
	Game();

	friend std::ostream& operator<<(std::ostream&, const Game&);

	void actualizar(char*, char);
	bool murio() { return vidas < 1; }
	size_t get_puntuacion() const { return puntuacion; }
};

void Game::llenar_mapa(const Pieza& p) {
	for (std::size_t i = 0; i < filas; i++) {
		for (std::size_t j = 0; j < columnas; j++) {
			m_map.at(i).at(j) = p;
		}
	}
}

void Game::fill_fila(std::size_t _inicio, std::size_t _final, std::size_t _fila, const Pieza& pieza = Piezas.at(Tipo_Pieza::VACIO)) {
	for (std::size_t i = _inicio; i < _final; i++) {
		m_map.at(i).at(_fila) = pieza;
	}
}

void Game::fill_columna(std::size_t _inicio, std::size_t _final, std::size_t _columna, const Pieza& pieza = Piezas.at(Tipo_Pieza::VACIO)) {
	for (std::size_t j = _inicio; j < _final; j++) {
		m_map.at(_columna).at(j) = pieza;
	}
}

void Game::crear_rectangulo(Coords_t pos, std::size_t w, std::size_t h) {
  std::size_t i, j;

  pos = {pos.first, pos.second};

  m_map.at(pos.first).at(pos.second) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);


  for (i = pos.first + 1; i < (pos.first + h - 1); i++) {
    m_map.at(i).at(pos.second) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
    m_map.at(i).at(pos.second + w - 1) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
  }
  m_map.at(i).at(pos.second) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

  for (j = pos.second + 1; j < (pos.second + w - 1); j++) {
    m_map.at(pos.first).at(j) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
    m_map.at(pos.first + h - 1).at(j) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
  }
  m_map.at(pos.first).at(j) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);
  m_map.at(pos.first + h - 1).at(j) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);

	for (i = pos.first + 1; i < (pos.first + h - 1); i++) {
    for (j = pos.second + 1; j < (pos.second + w - 1); j++) {
      m_map.at(i).at(j) = Piezas.at(Tipo_Pieza::VACIO);
    }
  }
}

void Game::modificar_posicion(const char* k) {	
	if (pacman.pos == Coords_t{14, 0} && MOVER_IZQUIERDA(*k)) {
		pacman.set_pos({14, COLUMNAS_SIZE-1});
	}

	else if (pacman.pos == Coords_t{14, COLUMNAS_SIZE-1} && MOVER_DERECHA(*k)) {
		pacman.set_pos({14, 0});
	}

	else if (MOVER_ARRIBA(*k))    { pacman.set_pos(pacman.pos.first-1, pacman.pos.second); }
	else if (MOVER_ABAJO(*k))     { pacman.set_pos(pacman.pos.first+1, pacman.pos.second); }
	else if (MOVER_DERECHA(*k))   { pacman.set_pos(pacman.pos.first, pacman.pos.second+1); }
	else if (MOVER_IZQUIERDA(*k)) { pacman.set_pos(pacman.pos.first, pacman.pos.second-1); }
}

void Game::comprobar_colisiones_fantasmas() {
	for (const auto& f : fantasmas) {
		if (f->pos == pacman.pos && !f->huyendo) {
			pacman.pos = pacman_init_pos;
			vidas--;
			break;
		}
		
		if (f->huyendo && pacman.pos == f->pos) {
			f->pos = f->init_pos;
			puntuacion += 500;
		}
	}
}

void Game::actualizar_fantasmas() {
	mover_fantasma++;
	if ((mover_fantasma % TIMER_MOV_FANTASMAS) == 0) {
		for (auto& f : fantasmas) {
			f->mover(pacman, m_map);
		}
	}
}

void Game::crear_frutas() { 
	auto is = [&](std::size_t i, std::size_t j, Tipo_Pieza pieza) {
		return m_map.at(i).at(j) == Piezas.at(pieza);
	};

	for (std::size_t i = 0; i < filas; i++) {
		for (std::size_t j = 0; j < columnas; j++) {
			if (is(i, j, Tipo_Pieza::VACIO)) {
				m_map.at(i).at(j) = Piezas.at(Tipo_Pieza::PUNTOS);
			}
		}
	}
	
	m_map.at(23).at(1)  = Piezas.at(Tipo_Pieza::FRUTA);
	m_map.at(23).at(26) = Piezas.at(Tipo_Pieza::FRUTA);
	m_map.at(3).at(1)   = Piezas.at(Tipo_Pieza::FRUTA);
	m_map.at(3).at(26)  = Piezas.at(Tipo_Pieza::FRUTA);
}

void Game::comprobar_colisiones_fruta() {
	auto is_hitting = [&](Tipo_Pieza pieza) {
		return m_map.at(pacman.pos.first).at(pacman.pos.second) == Piezas.at(pieza);
	};
	
	if (is_hitting(Tipo_Pieza::FRUTA)) {
		srand(time(0));

		bool fruta_trampa = ((rand() % 4) == 0);
		puntuacion += 300;
		m_map.at(pacman.pos.first).at(pacman.pos.second) = Piezas.at(Tipo_Pieza::VACIO);

		if (fruta_trampa) {
			system("pause");
			for (auto& f : fantasmas) {
				f->enojado = true;
				f->reset_timer = 40;
			}

			TIMER_MOV_FANTASMAS = 1;
		} else {
			for (auto& f : fantasmas) {
				f->huyendo = true;
				f->reset_timer = 40;
			}

			TIMER_MOV_FANTASMAS = 3;
		}
		 

	}

	else if (is_hitting(Tipo_Pieza::PUNTOS)) {
		puntuacion += 100;
		m_map.at(pacman.pos.first).at(pacman.pos.second) = Piezas.at(Tipo_Pieza::VACIO);
	}

	for (auto& f : fantasmas) {
		bool reset = f->resetear();
		if (reset) {
			TIMER_MOV_FANTASMAS = 2;
		}
	}
}

Game::Game() {
	pacman.pos = pacman_init_pos;
	pacman.prev_pos = pacman.pos;
	
	const auto& espacio_vacio = Piezas.at(Tipo_Pieza::VACIO);
	llenar_mapa(espacio_vacio);

	for (std::size_t i = 0; i < filas; i++) {
		m_map.at(i).at(0)          = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
		m_map.at(i).at(columnas-1) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
	}

	for (std::size_t j = 0; j < columnas; j++) {
		m_map.at(0).at(j)       = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
		m_map.at(filas-1).at(j) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	}

	m_map.at(0).at(0)       = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	m_map.at(filas-1).at(0) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

	m_map.at(filas-1).at(columnas-1) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(0).at(columnas-1)       = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	crear_frutas();
	crear_disenio();
}

void Game::crear_disenio() {
	// portal izquierdo, parte de arriba
	crear_rectangulo({9, 0}, 6, 5);
	fill_fila(9, 14, 0);
	m_map.at(9).at(0)  = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	m_map.at(13).at(0) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	// portal izquierdo, parte de abajo
	crear_rectangulo({15, 0}, 6, 5);
	fill_fila(14, 20, 0);
	m_map.at(15).at(0) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	m_map.at(19).at(0) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	
	// portal derecho, parte de arriba
	crear_rectangulo({9, 22}, 6, 5);
	fill_fila(9, 14, COLUMNAS_SIZE-1);
	m_map.at(9).at(COLUMNAS_SIZE-1)  = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(13).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);

	// portal derecho, parte de abajo
	crear_rectangulo({15, 22}, 6, 5);
	fill_fila(14, 20, COLUMNAS_SIZE-1);
	m_map.at(15).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	m_map.at(19).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pared vertical parte de arriba
	const auto first_pos = (columnas/2)-1;
	crear_rectangulo({0, first_pos}, 2, 5);
	m_map.at(0).at(first_pos)   = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);
	m_map.at(0).at(first_pos+1) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	// deformacion del mapa {24, 0}
	crear_rectangulo({24, 0}, 3, 2);
	m_map.at(24).at(0) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	m_map.at(25).at(0) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	// deformacion del mapa {24, 25}
	crear_rectangulo({24, 25}, 3, 2);
	m_map.at(24).at(27) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(25).at(27) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);
	
	// rectangulo posicion {2, 2}
	crear_rectangulo({2, 2}, 4, 3);
	// rectangulo posicion {2, 22}
	crear_rectangulo({2, 22}, 4, 3);

	// rectangulo posicion {2, 16}
	crear_rectangulo({2, 16}, 5, 3);
	// rectangulo posicion {2, 7}
	crear_rectangulo({2, 7}, 5, 3);

	// rectangulo posicion {6, 2}
	crear_rectangulo({6, 2}, 4, 2);
	// rectangulo posicion {6, 7}
	crear_rectangulo({6, 22}, 4, 2);
	
	// pieza de la posicion {6, 7} del mapa 
	crear_rectangulo({9, 8}, 4, 2);
	crear_rectangulo({6, 7}, 2, 8);
	m_map.at(9).at(8) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	m_map.at(10).at(8) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	// pieza de la posicion {6, 19} del mapa 
	crear_rectangulo({9, 16}, 4, 2);
	crear_rectangulo({6, 19}, 2, 8);
	m_map.at(9).at(19) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(10).at(19) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pieza de la posicion {6, 10} del mapa 
	crear_rectangulo({7, 13}, 2, 4);
	crear_rectangulo({6, 10}, 8, 2);
	m_map.at(7).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	m_map.at(7).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pieza de la posicion {18, 10} del mapa 
	crear_rectangulo({19, 13}, 2, 4);
	crear_rectangulo({18, 10}, 8, 2);
	m_map.at(19).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	m_map.at(19).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pieza de la posicion {24, 10} del mapa 
	crear_rectangulo({25, 13}, 2, 4);
	crear_rectangulo({24, 10}, 8, 2);
	m_map.at(25).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	m_map.at(25).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// reactangulo posicion {15, 7}
	crear_rectangulo({15, 7}, 2, 5);
	// reactangulo posicion {15, 19}
	crear_rectangulo({15, 19}, 2, 5);

	// capsula fantasmas
	crear_rectangulo({12, 10}, 8, 5);
	fill_columna(12, 16, 12);

	// reactangulo posicion {21, 7}
	crear_rectangulo({21, 7}, 5, 2);
	// reactangulo posicion {21, 16}
	crear_rectangulo({21, 16}, 5, 2);

	// pieza de la posicion {21, 4} del mapa 
	crear_rectangulo({21, 2}, 4, 2);
	crear_rectangulo({21, 4}, 2, 5);
	m_map.at(21).at(4) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	m_map.at(22).at(4) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pieza de la posicion {21, 22} del mapa 
	crear_rectangulo({21, 22}, 4, 2);
	crear_rectangulo({21, 22}, 2, 5);
	m_map.at(21).at(23) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	m_map.at(22).at(23) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	// pieza de la posicion {24, 7} del mapa 
	crear_rectangulo({27, 2}, 10, 2);
	crear_rectangulo({24, 7}, 2, 4);
	m_map.at(27).at(7) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(27).at(8) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

	// pieza de la posicion {24, 19} del mapa 
	crear_rectangulo({27, 16}, 10, 2);
	crear_rectangulo({24, 19}, 2, 4);
	m_map.at(27).at(19) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(27).at(20) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
}

bool Game::posicion_valida(const Pieza& p) {
	return 
	p == Piezas.at(Tipo_Pieza::PACMAN) || 
	p == Piezas.at(Tipo_Pieza::PUNTOS) || 
	p == Piezas.at(Tipo_Pieza::VACIO)  || 
	p == Piezas.at(Tipo_Pieza::FRUTA);
}

void Game::actualizar(char* k, char anterior) {
	const auto old_position = pacman.pos;

	modificar_posicion(k);

	const auto& pieza = m_map.at(pacman.pos.first).at(pacman.pos.second); 

	if (!posicion_valida(pieza)) {
		pacman.set_pos(old_position, true);
		*k = anterior;
		actualizar_fantasmas();
		return;
	}

	actualizar_fantasmas();
	comprobar_colisiones_fantasmas();
	comprobar_colisiones_fruta();
}

std::ostream& operator<<(std::ostream& os, const Game& m) {
	const auto offset_x = obtener_centro_consola().first;

#ifdef DEBUG
	gotoxy(0, 0);
	os << "Pacman coords: {" << m.pacman.pos.first << ", " << m.pacman.pos.second << "}";
#endif // DEBUG
	
	bool habia_fantasma = false;

	for (std::size_t i = 0; i < m.filas; i++) {
		gotoxy(offset_x, i);
		for (std::size_t j = 0; j < m.columnas; j++) {
			for (const auto& f : m.fantasmas) {
				if (f->pos == Coords_t{i, j}) {
					os << *f;
					habia_fantasma = true;
					break;
				}
			}

			if (habia_fantasma) {
				habia_fantasma = false;
				continue;
			}

			if (m.pacman.pos == Coords_t{i, j}) {
				os << m.pacman;
				continue;
			}
			
			os << m.m_map.at(i).at(j);
		}
		os << '\n';
	}

	gotoxy(offset_x, m.filas);
	for (std::size_t i = 0; i < m.vidas; i++) {
		os << m.pacman << ' ';
	}

	gotoxy(offset_x+m.columnas, 0);
	os << color.magenta << "Puntos: " << m.puntuacion;

	os << color.reset;

	return os;
}
