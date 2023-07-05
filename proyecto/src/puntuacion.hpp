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

#define NULL_DATA Data_t{ {"NULL", 0} }

#define ESHIFT 3
#define __CHAR_BUFFER 1024

void guardarData(Data_t data) {
	crearOthers();
	
	FILE *dataFile = fopen(dataFileName, "w");
	
	if (dataFileName == NULL) {
		system("cls");
	  throw std::runtime_error("[ERROR] No se pudo abrir el archivo de \"others/Data.txt\".\n");
	}

	static const char* scanFormat = (std::string("%llu %") + std::to_string(__CHAR_BUFFER) + "s\n").c_str();

	for (const auto& d : data) {
		fprintf(dataFile, scanFormat, d.second, d.first.c_str());
	}

	fclose(dataFile);
}


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
		guardarData(NULL_DATA);

		system("cls");
		
		gotoxy(getCentroConsola());
		std::cout << "Archivo creado!";
		
		Sleep(1000);
		system("cls");
		
		return NULL_DATA;
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

	std::sort(data.begin(), data.end(), [](Puntaje_t left, Puntaje_t right) { 
		return left.second > right.second;
	});

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
