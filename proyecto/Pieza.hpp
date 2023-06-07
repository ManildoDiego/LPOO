#pragma once

#include <map>
#include <string>
#include <ostream>

#include "colors.hpp"

// tipo de la pieza
enum Tipo_Pieza {
  PARED_VERTICAL,     // Simbolo: ║ (azul)
  PARED_HORIZONTAL,   // Simbolo: ═ (azul)

  IN_ABAJO_DERECHA,   // Simbolo: ╔ (azul)
  IN_ABAJO_IZQUIERDA, // Simbolo: ╗ (azul)

  IN_ARRIBA_DERECHA,   // Simbolo: ╚ (azul)
  IN_ARRIBA_IZQUIERDA, // Simbolo: ╝ (azul)

	INTERCECCION_ABAJO, // Simbolo: ╦ (azul)

	PUNTOS, // Simbolo: ■ (blanco)
	VACIO,  // Simbolo: ■ (negro)
	PACMAN, // Simbolo: 😊 (amarillo)
	FRUTA,  // Simbolo: ● (rojo)
};

struct Pieza {
	Pieza()                               : m_sprite('\0'), m_color("") {}
	Pieza(const Pieza& p)                 : m_sprite(p.m_sprite), m_color(p.m_color) {}
	Pieza(char sprite, const char* color) : m_sprite(sprite), m_color(color) {}
	Pieza(char sprite) : m_sprite(sprite), m_color(color.reset) {}

	Pieza& operator=(const Pieza& p) { m_sprite = p.m_sprite; m_color  = p.m_color; return *this;	}

	bool operator==(const Pieza& p) const { return m_sprite == p.m_sprite && m_color == p.m_color; }
	bool operator!=(const Pieza& p) const { return !operator==(p); }

	friend std::ostream& operator<<(std::ostream& os, const Pieza& p) { return os << p.m_color << p.m_sprite; }
private:
	char        m_sprite;
	const char* m_color;
};

const std::map<Tipo_Pieza, Pieza> Piezas = {
	{Tipo_Pieza::PARED_VERTICAL,   Pieza(static_cast<char>(186), color.blue)},
	{Tipo_Pieza::PARED_HORIZONTAL, Pieza(static_cast<char>(205), color.blue)},

	{Tipo_Pieza::IN_ABAJO_DERECHA,   Pieza(static_cast<char>(201), color.blue)},
	{Tipo_Pieza::IN_ABAJO_IZQUIERDA, Pieza(static_cast<char>(187), color.blue)},

	{Tipo_Pieza::IN_ARRIBA_DERECHA,   Pieza(static_cast<char>(200), color.blue)},
	{Tipo_Pieza::IN_ARRIBA_IZQUIERDA, Pieza(static_cast<char>(188), color.blue)},

	{Tipo_Pieza::INTERCECCION_ABAJO, Pieza(static_cast<char>(203), color.blue)},
	
	{Tipo_Pieza::PUNTOS, Pieza(static_cast<char>(219), color.white)},
	{Tipo_Pieza::VACIO,  Pieza(static_cast<char>(' '), color.black)},
	{Tipo_Pieza::PACMAN, Pieza(static_cast<char>(002), color.yellow)},
	{Tipo_Pieza::FRUTA,  Pieza(static_cast<char>(007), color.red)},
};