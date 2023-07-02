#pragma once

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <vector>

#include "manejoConsola.hpp"

// nombre del archivo que se va a abrir
const char* dataFileName = "others/Data.txt";
const char* othersDir    = "others";

void crearOthers();

using Data_t = std::vector<std::pair<std::string, std::size_t>>;

#define NULLDATA Data_t{ {"NULL", 0} }

void guardarData(const Data_t& data) {
	crearOthers();
	
	FILE *dataFile = fopen(dataFileName, "w");
	
	if (dataFileName == NULL) {
		system("cls");
	  throw std::runtime_error("[ERROR] No se pudo abrir el archivo de \"others/Data.txt\".\n");
	}
	

	for (const auto& [nombre, puntaje] : data) {
		fprintf(dataFile, "%s %llu\n", nombre.c_str(), puntaje);
	}

	fclose(dataFile);
}

#define __CHAR_BUFFER 255

Data_t leerData() {
	crearOthers();
	
  FILE *dataFile = fopen(dataFileName, "r");

	// si no existe el archivo, lo creo
  if (dataFile == NULL) {
		system("cls");
		gotoxy(getCentroConsola());
		std::cout << "Creando archivo de data"; Sleep(500);
		std::cout << '.';                       Sleep(500);
		std::cout << '.';                       Sleep(500);
		std::cout << '.' << std::endl;          Sleep(500);
		
		// lo creo
		dataFile = fopen(dataFileName, "w+");
	  fclose(dataFile);
		guardarData(NULLDATA);

		system("cls");
		
		gotoxy(getCentroConsola());
		std::cout << "Archivo creado!";
		
		Sleep(1000);
		system("cls");
		
		return NULLDATA;
  }

	Data_t data{};
  char nombre[__CHAR_BUFFER];
	std::size_t puntuacion;

	while (1) {
	  if (fscanf(dataFile, "%s %llu", nombre, &puntuacion) == EOF) {
			break;
		}

		data.push_back({nombre, puntuacion});
	}

	fclose(dataFile);
  return data;
}

extern "C" {
	#include <dirent.h>
}

void crearOthers() {
	bool existeOthers = [] {
		DIR* dir = opendir(othersDir);
	
		if (dir) {
			closedir(dir);
			return true;
		}

		return false;
	}();
	
	if (!existeOthers) {
		mkdir(othersDir);

		leerData();
	}
}
