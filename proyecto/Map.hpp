#pragma once

#include <array>
#include <vector>
#include <map>

#include "Pieza.hpp"
#include "PacMan.hpp"
#include "manejo_consola.hpp"
#include "Fantasma.hpp"

extern "C" {
	#include <time.h>
}

#define FILAS_SIZE 26
#define COLUMNAS_SIZE 28

using Coords_t = std::pair<std::size_t, std::size_t>;
using Mapa_t = std::array<std::array<Pieza, COLUMNAS_SIZE>, FILAS_SIZE>;

#define ARRIBA    static_cast<char>(72)
#define ABAJO     static_cast<char>(80)
#define DERECHA   static_cast<char>(77)
#define IZQUIERDA static_cast<char>(75)

class Map {
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

public:
	PacMan pacman;
private:
	std::size_t vidas = 3;
	std::size_t mover_fantasma = 0;

	const std::size_t filas    = FILAS_SIZE;
	const std::size_t columnas = COLUMNAS_SIZE;

	Mapa_t m_map{};

	const char Sprite_Default = static_cast<char>(1);

	std::vector<Fantasma> fantasmas = {
		Fantasma {
			Sprite_Default, 
			color.red, 
			Tipo_Fantasma::BLINKY, 
			{10, 10}
		},
		Fantasma {
			Sprite_Default,
			color.magenta,
			Tipo_Fantasma::PINKY,
			{11, 11}
		},
		Fantasma {
			Sprite_Default,
			color.blue,
			Tipo_Fantasma::INKY,
			{12, 12}
		},
		Fantasma {
			Sprite_Default,
			color.orange,
			Tipo_Fantasma::CLYDE,
			{13, 13}
		},
	};

	void llenar_mapa(const Pieza& p) {
		for (std::size_t i = 0; i < filas; i++) {
			for (std::size_t j = 0; j < columnas; j++) {
				m_map.at(i).at(j) = p;
			}
		}
	}

	void llenar_filas(std::size_t inicio = 0, std::size_t final = FILAS_SIZE) {
		for (std::size_t i = inicio; i < final; i++) {
			m_map.at(i).at(0)          = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
			m_map.at(i).at(columnas-1) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
		}
	}

	void llenar_columnas(std::size_t inicio = 0, std::size_t final = COLUMNAS_SIZE) {
		for (std::size_t j = inicio; j < final; j++) {
			m_map.at(0).at(j)       = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
			m_map.at(filas-1).at(j) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
		}
	}

	void crear_disenio() {
		m_map.at(0).at(columnas/2) = Piezas.at(Tipo_Pieza::INTERCECCION_ABAJO);

		for (std::size_t i = 1; i < 3; i++) {
			m_map.at(i).at(columnas/2) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
		}

		
	}
public:
	Map() {
		const auto& espacio_vacio = Piezas.at(Tipo_Pieza::VACIO);
		llenar_mapa(espacio_vacio);

		llenar_filas(1, filas);
		llenar_columnas(1, columnas/2);


		m_map.at(0).at(0)       = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
		m_map.at(filas-1).at(0) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

		m_map = invertir(m_map);

		m_map.at(filas-1).at(columnas-1) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
		m_map.at(0).at(columnas-1)       = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

		crear_disenio();
	}

	friend std::ostream& operator<<(std::ostream& os, const Map& m) {
		system("cls");
		
		const auto console_coords = obtener_centro_consola();

		const auto& offset_x = console_coords.first;
		const auto& offset_y = console_coords.second;
		
		bool habia_fantasma = false;
		
		for (std::size_t i = 0; i < m.filas; i++) {
			gotoxy(offset_x, offset_y + i);
			for (std::size_t j = 0; j < m.columnas; j++) {
				if (m.pacman.pos == Coords_t{i, j}) {
					os << m.pacman;
					continue;
				}


				for (const auto& f : m.fantasmas) {
					if (f.get_pos() == Coords_t{i, j}) {
						os << f;
						habia_fantasma = true;
						break;
					}
				}

				if (habia_fantasma) {
					habia_fantasma = false;
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

		#ifdef DEBUG
			gotoxy(offset_x, m.filas + offset_y+1);
			print_debug(std::string{color.yellow} + "Pacman pos: {" + std::to_string(m.pacman.pos.first) + ", " + std::to_string(m.pacman.pos.second) + "}\n");

			std::size_t index = 2;
			for (const auto& f : m.fantasmas) {
				gotoxy(offset_x, m.filas + offset_y+index);
				print_debug(f.get_color() + "Fantasma " + std::to_string(f.get_tipo()) + " pos: {" + std::to_string(f.get_pos().first) + ", " + std::to_string(f.get_pos().second) + "}\n");
				index++;
			}
		#endif

		return os;
	}

	void mover_pacman(char k) {
		const auto old_position = pacman.pos;

		if      (k == ARRIBA    || k == 'w' || k == 'i') { pacman.pos.first--; }
		else if (k == ABAJO     || k == 's' || k == 'k') { pacman.pos.first++; }
		else if (k == DERECHA   || k == 'd' || k == 'l') { pacman.pos.second++; }
		else if (k == IZQUIERDA || k == 'a' || k == 'j') { pacman.pos.second--; }

		const auto& pieza = m_map.at(pacman.pos.first).at(pacman.pos.second); 

		if (pieza != Piezas.at(Tipo_Pieza::PACMAN) && pieza != Piezas.at(Tipo_Pieza::PUNTOS) && pieza != Piezas.at(Tipo_Pieza::VACIO)) {
			pacman.pos = old_position;
			return;
		}

		for (const auto& f : fantasmas) {
			if (f.get_pos() == pacman.pos) {
				vidas--;
				break;
			}
		}

		actualizar_fantasmas();
	}

	void actualizar_fantasmas(bool activate = false) {
		mover_fantasma++;
		if ((mover_fantasma % 2) == 0 || activate) {
			for (std::size_t i = 0; i < fantasmas.size(); i++) {
				fantasmas[i].mover(pacman);
			}
		}
	}

	bool murio() { return vidas < 1; }
};