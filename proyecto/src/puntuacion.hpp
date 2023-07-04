#pragma once

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "manejoConsola.hpp"

// nombre del archivo que se va a abrir
const char* dataFileName = "others/Data.txt";
const char* othersDir    = "others";

void crearOthers();

using Tecla_t   = std::pair<const std::string, char>;
using Puntaje_t = std::pair<std::string, std::size_t>;
using Data_t    = std::vector<Puntaje_t>;

#define NULLDATA Data_t{ {"NULL", 0} }

void guardarData(Data_t data) {
	static auto ordenarPorDesc = [](const Puntaje_t& left, const Puntaje_t& right) { 
		return left.second > right.second; 
	};

	const auto estaOrdenado = [&] {
		if (data.size() <= 1) {
			return true;
		}

		for (std::size_t i = 1; i < data.size(); i++) {
	    if (ordenarPorDesc(data[i], data[i-1])) {
	      return false;
	    }
		}
    return true;
	}();

	crearOthers();
	
	FILE *dataFile = fopen(dataFileName, "w");
	
	if (dataFileName == NULL) {
		system("cls");
	  throw std::runtime_error("[ERROR] No se pudo abrir el archivo de \"others/Data.txt\".\n");
	}

	if (!estaOrdenado) {
		std::sort(data.begin(), data.end(), ordenarPorDesc);
	}

	for (const auto& d : data) {
		fprintf(dataFile, "%llu %s\n", d.second, d.first.c_str());
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
	  if (fscanf(dataFile, "%llu %[^\n]", &puntuacion, nombre) == EOF) {
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
