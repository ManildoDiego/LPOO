#pragma once

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <stdexcept>

extern "C" {
	#include <dirent.h>
}

// nombre del archivo que se va a abrir
const char* puntajeFileName = "others/Puntaje.txt";
const char* nombreFileName = "others/Nombre.txt";
const char* othersDir = "others";

bool existeOthers() {
	DIR* dir = opendir(othersDir);
	
	if (dir) {
		closedir(dir);
		return true;
	}

	return false;
}

void crearOthers() {
	mkdir(othersDir);
}

void crearOthersSiNoExiste();

// guarda la maxima puntuacion
void guardarPuntuacion(std::size_t puntuacion) {
	crearOthersSiNoExiste();
	
	FILE *archivo = fopen(puntajeFileName, "w");
	
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
	crearOthersSiNoExiste();
	
	FILE *archivo = fopen(nombreFileName, "w");
	
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
	crearOthersSiNoExiste();
	
  std::size_t puntuacionMaxima;
	// abro el archivo en modo lectura
  FILE *archivo = fopen(puntajeFileName, "r");

	// si no existe el archivo lanzo una excepcion
  if (archivo == NULL) {
		throw std::runtime_error("[ERROR] No existe el archivo");
  }

	// scaneo el puntaje
  fscanf(archivo, "%llu", &puntuacionMaxima);
  fclose(archivo);
  return puntuacionMaxima;
}

#define __CHAR_BUFFER 255

std::string leerNombre() {
	crearOthersSiNoExiste();
	
  char nombre[__CHAR_BUFFER];
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
		guardarNombre("NULL");

		system("cls");
		std::cout << "Archivo creado!";
		Sleep(1000);
		system("cls");
		return "NULL";
  }

	// scaneo el puntaje
  auto out = fgets(nombre, __CHAR_BUFFER, archivo);
	if (out == NULL) {
		return "NULL";
	}
  fclose(archivo);
  return nombre;
}

void crearOthersSiNoExiste() {
	if (!existeOthers()) {
		crearOthers();

		system("cls");
		std::cout << "Creando archivos"; Sleep(500);
		std::cout << '.';                Sleep(500);
		std::cout << '.';                Sleep(500);
		std::cout << '.' << std::endl;   Sleep(500);
		
		// creo archivo de puntaje
		FILE* archivo = fopen(puntajeFileName, "w+");
	  fclose(archivo);
		// guardo "0" puntos
		guardarPuntuacion(0);
		// creo archivo de nombre
		archivo = fopen(puntajeFileName, "w");
	  fclose(archivo);
		guardarNombre("NULL");


		system("cls");
		std::cout << "Archivos creados!";
		Sleep(1000);
		system("cls");
	}
}
