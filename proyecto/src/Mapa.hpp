#pragma once

#include <array>

#include "Pieza.hpp"

#define FILAS_SIZE 31
#define COLUMNAS_SIZE 28

struct Mapa_t : public std::array<std::array<Pieza, COLUMNAS_SIZE>, FILAS_SIZE> {
	using Coords_t = std::pair<int64_t, int64_t>;

	static const std::size_t filas    = FILAS_SIZE;
	static const std::size_t columnas = COLUMNAS_SIZE;

	Mapa_t();
private:
	void _LlenarFila(std::size_t, std::size_t, std::size_t, const Pieza&);
	void _LlenarColumna(std::size_t, std::size_t, std::size_t, const Pieza&);
	void _CrearRectangulo(Coords_t, std::size_t, std::size_t);
	void _CrearFrutas();
	void _CrearDisenio();
};

Mapa_t::Mapa_t() {
	// llena el mapa de puntos
	for (std::size_t i = 0; i < filas; i++) {
		for (std::size_t j = 0; j < columnas; j++) {
			this->at(i).at(j) = Piezas.at(Tipo_Pieza::PUNTOS);
		}
	}

	for (std::size_t i = 0; i < filas; i++) {
		this->at(i).at(0)           = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
		this->at(i).at(columnas-1) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
	}

	for (std::size_t j = 0; j < columnas; j++) {
		this->at(0).at(j)        = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
		this->at(filas-1).at(j) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	}

	this->at(0).at(0)        = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	this->at(filas-1).at(0) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

	this->at(filas-1).at(columnas-1) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	this->at(0).at(columnas-1)        = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	_CrearFrutas();
	_CrearDisenio();
}

void Mapa_t::_LlenarFila(std::size_t _inicio, std::size_t _final, std::size_t _fila, const Pieza& pieza = Piezas.at(Tipo_Pieza::VACIO)) {
	for (std::size_t i = _inicio; i < _final; i++) {
		this->at(i).at(_fila) = pieza;
	}
}

void Mapa_t::_LlenarColumna(std::size_t _inicio, std::size_t _final, std::size_t _columna, const Pieza& pieza = Piezas.at(Tipo_Pieza::VACIO)) {
	for (std::size_t j = _inicio; j < _final; j++) {
		this->at(_columna).at(j) = pieza;
	}
}

void Mapa_t::_CrearRectangulo(Coords_t pos, std::size_t w, std::size_t h) {
  std::size_t i, j;

  pos = {pos.first, pos.second};

  this->at(pos.first).at(pos.second) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);


  for (i = pos.first + 1; i < (pos.first + h - 1); i++) {
    this->at(i).at(pos.second) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
    this->at(i).at(pos.second + w - 1) = Piezas.at(Tipo_Pieza::PARED_VERTICAL);
  }
  this->at(i).at(pos.second) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

  for (j = pos.second + 1; j < (pos.second + w - 1); j++) {
    this->at(pos.first).at(j) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
    this->at(pos.first + h - 1).at(j) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
  }
  this->at(pos.first).at(j) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);
  this->at(pos.first + h - 1).at(j) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);

	for (i = pos.first + 1; i < (pos.first + h - 1); i++) {
    for (j = pos.second + 1; j < (pos.second + w - 1); j++) {
      this->at(i).at(j) = Piezas.at(Tipo_Pieza::VACIO);
    }
  }
}

void Mapa_t::_CrearFrutas() { 
	this->at(23).at(1)  = Piezas.at(Tipo_Pieza::FRUTA);
	this->at(23).at(26) = Piezas.at(Tipo_Pieza::FRUTA);
	this->at(3).at(1)   = Piezas.at(Tipo_Pieza::FRUTA);
	this->at(3).at(26)  = Piezas.at(Tipo_Pieza::FRUTA);
}

void Mapa_t::_CrearDisenio() {
	// portal izquierdo, parte de arriba
	_CrearRectangulo({9, 0}, 6, 5);
	_LlenarFila(9, 14, 0);
	this->at(9).at(0)  = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	this->at(13).at(0) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	// portal izquierdo, parte de abajo
	_CrearRectangulo({15, 0}, 6, 5);
	_LlenarFila(14, 20, 0);
	this->at(15).at(0) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	this->at(19).at(0) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	
	// portal derecho, parte de arriba
	_CrearRectangulo({9, 22}, 6, 5);
	_LlenarFila(9, 14, COLUMNAS_SIZE-1);
	this->at(9).at(COLUMNAS_SIZE-1)  = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	this->at(13).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);

	// portal derecho, parte de abajo
	_CrearRectangulo({15, 22}, 6, 5);
	_LlenarFila(14, 20, COLUMNAS_SIZE-1);
	this->at(15).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	this->at(19).at(COLUMNAS_SIZE-1) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pared vertical parte de arriba
	const auto first_pos = (columnas/2)-1;
	_CrearRectangulo({0, first_pos}, 2, 5);
	this->at(0).at(first_pos)   = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);
	this->at(0).at(first_pos+1) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	// deformacion del mapa {24, 0}
	_CrearRectangulo({24, 0}, 3, 2);
	this->at(24).at(0) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	this->at(25).at(0) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	// deformacion del mapa {24, 25}
	_CrearRectangulo({24, 25}, 3, 2);
	this->at(24).at(27) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	this->at(25).at(27) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);
	
	// rectangulo posicion {2, 2}
	_CrearRectangulo({2, 2}, 4, 3);
	// rectangulo posicion {2, 22}
	_CrearRectangulo({2, 22}, 4, 3);

	// rectangulo posicion {2, 16}
	_CrearRectangulo({2, 16}, 5, 3);
	// rectangulo posicion {2, 7}
	_CrearRectangulo({2, 7}, 5, 3);

	// rectangulo posicion {6, 2}
	_CrearRectangulo({6, 2}, 4, 2);
	// rectangulo posicion {6, 7}
	_CrearRectangulo({6, 22}, 4, 2);
	
	// pieza de la posicion {6, 7} del mapa 
	_CrearRectangulo({9, 8}, 4, 2);
	_CrearRectangulo({6, 7}, 2, 8);
	this->at(9).at(8) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
	this->at(10).at(8) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	// pieza de la posicion {6, 19} del mapa 
	_CrearRectangulo({9, 16}, 4, 2);
	_CrearRectangulo({6, 19}, 2, 8);
	this->at(9).at(19) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	this->at(10).at(19) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pieza de la posicion {6, 10} del mapa 
	_CrearRectangulo({7, 13}, 2, 4);
	_CrearRectangulo({6, 10}, 8, 2);
	this->at(7).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	this->at(7).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pieza de la posicion {18, 10} del mapa 
	_CrearRectangulo({19, 13}, 2, 4);
	_CrearRectangulo({18, 10}, 8, 2);
	this->at(19).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	this->at(19).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pieza de la posicion {24, 10} del mapa 
	_CrearRectangulo({25, 13}, 2, 4);
	_CrearRectangulo({24, 10}, 8, 2);
	this->at(25).at(14) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);
	this->at(25).at(13) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// reactangulo posicion {15, 7}
	_CrearRectangulo({15, 7}, 2, 5);
	// reactangulo posicion {15, 19}
	_CrearRectangulo({15, 19}, 2, 5);

	// capsula fantasmas
	_CrearRectangulo({12, 10}, 8, 5);
	_LlenarColumna(12, 16, 12);

	// reactangulo posicion {21, 7}
	_CrearRectangulo({21, 7}, 5, 2);
	// reactangulo posicion {21, 16}
	_CrearRectangulo({21, 16}, 5, 2);

	// pieza de la posicion {21, 4} del mapa 
	_CrearRectangulo({21, 2}, 4, 2);
	_CrearRectangulo({21, 4}, 2, 5);
	this->at(21).at(4) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	this->at(22).at(4) = Piezas.at(Tipo_Pieza::IN_ABAJO_IZQUIERDA);

	// pieza de la posicion {21, 22} del mapa 
	_CrearRectangulo({21, 22}, 4, 2);
	_CrearRectangulo({21, 22}, 2, 5);
	this->at(21).at(23) = Piezas.at(Tipo_Pieza::PARED_HORIZONTAL);
	this->at(22).at(23) = Piezas.at(Tipo_Pieza::IN_ABAJO_DERECHA);

	// pieza de la posicion {24, 7} del mapa 
	_CrearRectangulo({27, 2}, 10, 2);
	_CrearRectangulo({24, 7}, 2, 4);
	this->at(27).at(7) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	this->at(27).at(8) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);

	// pieza de la posicion {24, 19} del mapa 
	_CrearRectangulo({27, 16}, 10, 2);
	_CrearRectangulo({24, 19}, 2, 4);
	this->at(27).at(19) = Piezas.at(Tipo_Pieza::IN_ARRIBA_IZQUIERDA);
	this->at(27).at(20) = Piezas.at(Tipo_Pieza::IN_ARRIBA_DERECHA);
}