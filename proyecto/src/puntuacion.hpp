#pragma once

#include <cstdlib>
#include <iostream>
#include <windows.h>

const char* file_name = "Puntaje.txt";

// guarda la maxima puntuacion
void guardarPuntuacion(std::size_t puntuacionMaxima) {
	FILE *archivo;
	archivo = fopen(file_name, "w");
	
	if (archivo == NULL) {
	  std::cout << "No se pudo abrir el archivo.\n";
	  return;
	}
	
	fprintf(archivo, "%llu", puntuacionMaxima);
	fclose(archivo);
}

std::size_t leerPuntuacion() {
  std::size_t puntuacionMaxima;
  FILE *archivo;

  archivo = fopen(file_name, "r");

  if (archivo == NULL) {
		system("cls");
		std::cout << "Creando archivo de puntaje"; Sleep(500);
		std::cout << '.';                          Sleep(500);
		std::cout << '.';                          Sleep(500);
		std::cout << '.' << std::endl;             Sleep(500);
		
		archivo = fopen(file_name, "w+");
	  fclose(archivo);
		guardarPuntuacion(0);

		system("cls");
		std::cout << "Archivo creado!";
		Sleep(1000);
		system("cls");
		return 0;
  }

  fscanf(archivo, "%llu", &puntuacionMaxima);
  fclose(archivo);
  return puntuacionMaxima;
}