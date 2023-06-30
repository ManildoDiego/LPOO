#pragma once

#include <map>
#include <string>
#include <ostream>

#include "colors.hpp"

// tipo de la pieza
enum class Tipo_Pieza {
  PARED_VERTICAL,     // Simbolo: ║ (azul)
  PARED_HORIZONTAL,   // Simbolo: ═ (azul)

  IN_ABAJO_DERECHA,   // Simbolo: ╔ (azul)
  IN_ABAJO_IZQUIERDA, // Simbolo: ╗ (azul)

  IN_ARRIBA_DERECHA,   // Simbolo: ╚ (azul)
  IN_ARRIBA_IZQUIERDA, // Simbolo: ╝ (azul)

	INTERCECCION_ABAJO, // Simbolo: ╦ (azul)

	BARRERA,

	PUNTOS, // Simbolo: ■ (blanco)
	VACIO,  // Simbolo: ■ (negro)
	PACMAN, // Simbolo: 😊 (amarillo)
	FRUTA,  // Simbolo: ● (rojo)
};

struct Pieza final {
	// constructor default
	Pieza()                               : _sprite('\0'), _color("") {}
	// constructor de copia
	Pieza(const Pieza& p)                 : _sprite(p._sprite), _color(p._color) {}
	// constructor normal
	Pieza(char sprite, std::string color) : _sprite(sprite), _color(color) {}
	// constructor normal sin color
	Pieza(char sprite)                    : _sprite(sprite), _color(color.reset) {}

	// operador= de copia
	Pieza& operator=(const Pieza& p) { _sprite = p._sprite; _color = p._color; return *this;	}

	// operadores de comparacion
	bool operator==(const Pieza& p) const { return _sprite == p._sprite && _color == p._color; }
	bool operator!=(const Pieza& p) const { return !operator==(p); }

	// metodo de imprimir sprite
	friend std::ostream& operator<<(std::ostream& os, const Pieza& p) { return os << p._color << p._sprite; }
private:
	char        _sprite;
	std::string _color;
};

/*
	Diccionario de piezas:
		key = Tipo_Pieza
		value = Pieza
*/
const std::map<Tipo_Pieza, Pieza> Piezas = {
	{ Tipo_Pieza::PARED_VERTICAL,      Pieza(static_cast<char>(186), color.blue)   },
	{ Tipo_Pieza::PARED_HORIZONTAL,    Pieza(static_cast<char>(205), color.blue)   },
	{ Tipo_Pieza::IN_ABAJO_DERECHA,    Pieza(static_cast<char>(201), color.blue)   },
	{ Tipo_Pieza::IN_ABAJO_IZQUIERDA,  Pieza(static_cast<char>(187), color.blue)   },
	{ Tipo_Pieza::IN_ARRIBA_DERECHA,   Pieza(static_cast<char>(200), color.blue)   },
	{ Tipo_Pieza::IN_ARRIBA_IZQUIERDA, Pieza(static_cast<char>(188), color.blue)   },
	{ Tipo_Pieza::INTERCECCION_ABAJO,  Pieza(static_cast<char>(203), color.blue)   },
	{ Tipo_Pieza::BARRERA, 					   Pieza(static_cast<char>(205), color.reset)  },
	{ Tipo_Pieza::PUNTOS,  					   Pieza(static_cast<char>('.'), color.white)  },
	{ Tipo_Pieza::VACIO,   					   Pieza(static_cast<char>(' '), color.black)  },
	{ Tipo_Pieza::PACMAN,  					   Pieza(static_cast<char>(002), color.yellow) },
	{ Tipo_Pieza::FRUTA,   					   Pieza(static_cast<char>(254), color.red)    },
};
