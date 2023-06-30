#pragma once

#include <cstdlib>
#include <iostream>
#include <windows.h>

// nombre del archivo que se va a abrir
const char* puntajeFileName = "others/Puntaje.txt";
const char* nombreFileName = "others/Nombre.txt";

// guarda la maxima puntuacion
void guardarPuntuacion(std::size_t puntuacion) {
	FILE *archivo;
	archivo = fopen(puntajeFileName, "w");
	
	if (archivo == NULL) {
		system("cls");
	  std::cout << "[ERROR] No se pudo abrir el archivo de puntaje.\n";
	  return;
	}
	
	// imprimo en el archivo la puntuacion
	fprintf(archivo, "%llu", puntuacion);
	fclose(archivo);
}

void guardarNombre(const std::string& nombre) {
	FILE *archivo;
	archivo = fopen(nombreFileName, "w");
	
	if (archivo == NULL) {
		system("cls");
	  std::cout << "[ERROR] No se pudo abrir el archivo de nombre.\n";
	  return;
	}
	
	// guardo en el archivo el nombre
	fprintf(archivo, "%s", nombre.c_str());
	fclose(archivo);
}

// leo puntuacion del archivo
std::size_t leerPuntuacion() {
  std::size_t puntuacionMaxima;
  FILE *archivo;

	// abro el archivo en modo lectura
  archivo = fopen(puntajeFileName, "r");

	// si no existe el archivo, lo creo
  if (archivo == NULL) {
		system("cls");
		std::cout << "Creando archivo de puntaje"; Sleep(500);
		std::cout << '.';                          Sleep(500);
		std::cout << '.';                          Sleep(500);
		std::cout << '.' << std::endl;             Sleep(500);
		
		// lo creo
		archivo = fopen(puntajeFileName, "w+");
	  fclose(archivo);
		// guardo "0" puntos
		guardarPuntuacion(0);

		system("cls");
		std::cout << "Archivo creado!";
		Sleep(1000);
		system("cls");
		// devuelvo que tenia 0 puntos
		return 0;
  }

	// scaneo el puntaje
  fscanf(archivo, "%llu", &puntuacionMaxima);
  fclose(archivo);
  return puntuacionMaxima;
}

std::string leerNombre() {
  char nombre[255];
  FILE *archivo;

	// abro el archivo en modo lectura
  archivo = fopen(nombreFileName, "r");

	// si no existe el archivo, lo creo
  if (archivo == NULL) {
		system("cls");
		std::cout << "Creando archivo de nombre"; Sleep(500);
		std::cout << '.';                         Sleep(500);
		std::cout << '.';                         Sleep(500);
		std::cout << '.' << std::endl;            Sleep(500);
		
		// lo creo
		archivo = fopen(puntajeFileName, "w+");
	  fclose(archivo);
		guardarNombre(" ");

		system("cls");
		std::cout << "Archivo creado!";
		Sleep(1000);
		system("cls");
		return "";
  }

	// scaneo el puntaje
  fscanf(archivo, "%255s", nombre);
  fclose(archivo);
  return nombre;
}