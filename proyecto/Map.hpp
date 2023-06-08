#pragma once

#include <array>
#include <vector>
#include <map>

#include "Pieza.hpp"
#include "PacMan.hpp"
#include "manejo_consola.hpp"

extern "C" {
	#include <time.h>
}

#define FILAS_SIZE 31
#define COLUMNAS_SIZE 28

using Mapa_t = std::array<std::array<Pieza, COLUMNAS_SIZE>, FILAS_SIZE>;

#include "Fantasma.hpp"

extern std::vector<std::pair<std::string, char>> controles;

#define ARRIBA    static_cast<char>(72)
#define ABAJO     static_cast<char>(80)
#define DERECHA   static_cast<char>(77)
#define IZQUIERDA static_cast<char>(75)

#define MOVER_ARRIBA(k)    (k == ARRIBA    || k == controles.at(0).second)
#define MOVER_ABAJO(k)     (k == ABAJO     || k == controles.at(1).second)
#define MOVER_DERECHA(k)   (k == DERECHA   || k == controles.at(2).second)
#define MOVER_IZQUIERDA(k) (k == IZQUIERDA || k == controles.at(3).second)

struct Map {
	PacMan pacman;
	using Coords_t = std::pair<int64_t, int64_t>;
private:
	std::size_t puntuacion = 0;
	const Coords_t pacman_init_pos = {17, 13};
	std::size_t vidas = 3;
	std::size_t mover_fantasma = 0;
	std::size_t TIMER_MOV_FANTASMAS = 2;

	const std::size_t filas    = FILAS_SIZE;
	const std::size_t columnas = COLUMNAS_SIZE;

	Mapa_t m_map{};

	const char Sprite_Default = static_cast<char>(1);

	std::vector<Fantasma> fantasmas = {
		Fantasma {
			Sprite_Default, 
			color.red, 
			Tipo_Fantasma::BLINKY, 
			{14, 12}
		},
		Fantasma {
			Sprite_Default,
			color.magenta,
			Tipo_Fantasma::PINKY,
			{14, 13}
		},
		Fantasma {
			Sprite_Default,
			color.blue,
			Tipo_Fantasma::INKY,
			{14, 14}
		},
		Fantasma {
			Sprite_Default,
			color.orange,
			Tipo_Fantasma::CLYDE,
			{14, 15}
		},
	};

	static Mapa_t invertir(const Mapa_t& mapa) {
    Mapa_t duplicado = mapa;

    std::size_t mitad = mapa[0].size() / 2;

    for (std::size_t i = 0; i < mapa.size(); i++) {
      for (std::size_t j = 0; j < mitad; j++) {
        duplicado[i][mitad + j] = mapa[i][mitad - 1 - j];
      }
    }

    return duplicado;
	}

	void modificar_posicion(char k) {
		if (pacman.pos == Coords_t{14, 0} && MOVER_IZQUIERDA(k)) {
			pacman.set_pos({14, COLUMNAS_SIZE-1});
		}

		else if (pacman.pos == Coords_t{14, COLUMNAS_SIZE-1} && MOVER_DERECHA(k)) {
			pacman.set_pos({14, 0});
		}

		else if (MOVER_ARRIBA(k))    { pacman.set_pos(pacman.pos.first-1, pacman.pos.second); }
		else if (MOVER_ABAJO(k))     { pacman.set_pos(pacman.pos.first+1, pacman.pos.second); }
		else if (MOVER_DERECHA(k))   { pacman.set_pos(pacman.pos.first, pacman.pos.second+1); }
		else if (MOVER_IZQUIERDA(k)) { pacman.set_pos(pacman.pos.first, pacman.pos.second-1); }
	}

	void llenar_mapa(const Pieza& p) {
		for (std::size_t i = 0; i < filas; i++) {
			for (std::size_t j = 0; j < columnas; j++) {
				if (i == (FILAS_SIZE/2) && j == (COLUMNAS_SIZE/2)) {
					m_map.at(i).at(j) = 'M';
					continue;
				}

				m_map.at(i).at(j) = p;
			}
		}
	}

	void llenar_filas(std::size_t _inicio = 0, std::size_t _final = FILAS_SIZE) {
		for (std::size_t i = _inicio; i < _final; i++) {
			m_map.at(i).at(0)          = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
			m_map.at(i).at(columnas-1) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
		}
	}

	void llenar_columnas(std::size_t _inicio = 0, std::size_t _final = COLUMNAS_SIZE) {
		for (std::size_t j = _inicio; j < _final; j++) {
			m_map.at(0).at(j)       = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
			m_map.at(filas-1).at(j) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
		}
	}

	void vaciar_fila(std::size_t _inicio, std::size_t _final, std::size_t _fila, const Pieza& pieza = Piezas.at(Tipo_Pieza::VACIO)) {
		for (std::size_t i = _inicio; i < _final; i++) {
			m_map.at(i).at(_fila) = pieza;
		}
	}

	void vaciar_columna(std::size_t _inicio, std::size_t _final, std::size_t _columna, const Pieza& pieza = Piezas.at(Tipo_Pieza::VACIO)) {
		for (std::size_t j = _inicio; j < _final; j++) {
			m_map.at(_columna).at(j) = pieza;
		}
	}

	void crear_rectangulo(Coords_t pos, std::size_t w, std::size_t h) {
    pos = {pos.first - 1, pos.second - 1};

    m_map.at(pos.first).at(pos.second) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

    std::size_t i, j;

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
	}

	void comprobar_colisiones_fantasmas() {
		for (const auto& f : fantasmas) {
			if (f.pos == pacman.pos) {
				pacman.pos = pacman_init_pos;
				vidas--;
				break;
			}
		}
	}

	void actualizar_fantasmas(bool activate = false) {
		mover_fantasma++;
		if ((mover_fantasma % TIMER_MOV_FANTASMAS) == 0 || activate) {
			for (std::size_t i = 0; i < fantasmas.size(); i++) {
				fantasmas[i].mover(pacman, m_map);
			}
		}
	}

	void crear_frutas() {
		m_map.at(3).at(1) = Piezas.at(Tipo_Pieza::FRUTA);
	}

	void comprobar_colisiones_fruta() {
		if (m_map.at(pacman.pos.first).at(pacman.pos.second) == Piezas.at(Tipo_Pieza::FRUTA)) {
			puntuacion += 100;
			m_map.at(pacman.pos.first).at(pacman.pos.second) = Piezas.at(Tipo_Pieza::VACIO);

			for (auto& f : fantasmas) {
				f.change_color(color.cyan);
				f.huyendo = true;
			}

			TIMER_MOV_FANTASMAS = 3;
		}

		for (auto& f : fantasmas) {
			f.resetear();
		}
	}

	bool posicion_valida(const Pieza&);

	void crear_disenio();
public:
	Map() {
		pacman.pos = pacman_init_pos;
		pacman.prev_pos = pacman.pos;
		
		const auto& espacio_vacio = Piezas.at(Tipo_Pieza::VACIO);
		llenar_mapa(espacio_vacio);

		llenar_filas();
		llenar_columnas(1, columnas/2);

		m_map.at(0).at(0)       = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
		m_map.at(filas-1).at(0) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

		m_map = invertir(m_map);

		m_map.at(filas-1).at(columnas-1) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
		m_map.at(0).at(columnas-1)       = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

		crear_disenio();
		crear_frutas();
	}

	friend std::ostream& operator<<(std::ostream& os, const Map& m) {
		system("cls");
		
	#ifdef DEBUG
		gotoxy(0, 0);
		os << "Pacman coords: {" << m.pacman.pos.first << ", " << m.pacman.pos.second << "}";
	#endif // DEBUG
		const auto console_coords = obtener_centro_consola();

		const auto& offset_x = console_coords.first;
		const auto& offset_y = console_coords.second;
		
		bool habia_fantasma = false;

		for (std::size_t i = 0; i < m.filas; i++) {
			gotoxy(offset_x, offset_y + i);
			for (std::size_t j = 0; j < m.columnas; j++) {
				for (const auto& f : m.fantasmas) {
					if (f.pos == Coords_t{i, j}) {
						os << f;
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

		gotoxy(offset_x, m.filas + offset_y);
		for (std::size_t i = 0; i < m.vidas; i++) {
			os << m.pacman << ' ';
		}

		os << color.reset;

		return os;
	}

	void actualizar(char* k, char anterior) {
		const auto old_position = pacman.pos;

		modificar_posicion(*k);

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

	bool murio() { return vidas < 1; }
};

void Map::crear_disenio() {
	crear_rectangulo({10, 1}, 6, 5);
	vaciar_fila(9, 14, 0);
	m_map.at(9).at(0)  = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	m_map.at(13).at(0) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);

	crear_rectangulo({16, 1}, 6, 5);
	vaciar_fila(14, 20, 0);
	m_map.at(15).at(0) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	m_map.at(19).at(0) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	
	crear_rectangulo({10, 23}, 6, 5);
	vaciar_fila(9, 14, COLUMNAS_SIZE-1);
	m_map.at(9).at(COLUMNAS_SIZE-1)  = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(13).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);

	crear_rectangulo({16, 23}, 6, 5);
	vaciar_fila(14, 20, COLUMNAS_SIZE-1);
	m_map.at(15).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	m_map.at(19).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);


	const auto first_pos = (columnas/2);
	crear_rectangulo({1, first_pos}, 2, 4);
	
	m_map.at(0).at(first_pos-1) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);
	m_map.at(0).at(first_pos) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	crear_rectangulo({3, 3}, 4, 3);
	crear_rectangulo({3, 23}, 4, 3);

	crear_rectangulo({3, 17}, 5, 3);
	crear_rectangulo({3, 8}, 5, 3);

	crear_rectangulo({7, 3}, 4, 2);
	crear_rectangulo({7, 23}, 4, 2);
	
	crear_rectangulo({10, 9}, 4, 2);
	crear_rectangulo({7, 8}, 2, 8);
	m_map.at(9).at(8) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	m_map.at(10).at(8) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	crear_rectangulo({16, 8}, 2, 5);
	crear_rectangulo({16, 20}, 2, 5);

	// capsula fantasmas
	crear_rectangulo({13, 11}, 8, 5);
	vaciar_columna(12, 16, 12);

	crear_rectangulo({22, 8}, 5, 2);
	crear_rectangulo({22, 17}, 5, 2);

	crear_rectangulo({10, 17}, 4, 2);
	crear_rectangulo({7, 20}, 2, 8);
	m_map.at(9).at(19) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(10).at(19) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	crear_rectangulo({8, 14}, 2, 4);
	crear_rectangulo({7, 11}, 8, 2);
	m_map.at(7).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	m_map.at(7).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	crear_rectangulo({20, 14}, 2, 4);
	crear_rectangulo({19, 11}, 8, 2);
	m_map.at(19).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	m_map.at(19).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	crear_rectangulo({26, 14}, 2, 4);
	crear_rectangulo({25, 11}, 8, 2);
	m_map.at(25).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	m_map.at(25).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	crear_rectangulo({25, 1}, 3, 2);
	m_map.at(24).at(0) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	m_map.at(25).at(0) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	crear_rectangulo({25, 26}, 3, 2);
	m_map.at(24).at(27) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(25).at(27) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);
	
	crear_rectangulo({22, 3}, 4, 2);
	crear_rectangulo({22, 5}, 2, 5);
	m_map.at(21).at(4) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	m_map.at(22).at(4) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	crear_rectangulo({22, 23}, 4, 2);
	crear_rectangulo({22, 23}, 2, 5);
	m_map.at(21).at(23) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	m_map.at(22).at(23) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	crear_rectangulo({28, 3}, 10, 2);
	crear_rectangulo({25, 8}, 2, 4);
	m_map.at(27).at(7) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(27).at(8) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

	crear_rectangulo({28, 17}, 10, 2);
	crear_rectangulo({25, 20}, 2, 4);
	m_map.at(27).at(19) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	m_map.at(27).at(20) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
}

bool Map::posicion_valida(const Pieza& p) {
	return 
	p == Piezas.at(Tipo_Pieza::PACMAN) || 
	p == Piezas.at(Tipo_Pieza::PUNTOS) || 
	p == Piezas.at(Tipo_Pieza::VACIO)  || 
	p == Piezas.at(Tipo_Pieza::FRUTA);
}