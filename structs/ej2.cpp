#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_CANCIONES 100

struct Cancion {
	string artista;
	string titulo;
	size_t duracion;
	size_t tamanio;

	friend ostream& operator<<(ostream& os, const Cancion& c) {
		os << "Artista: " << c.artista << endl;
		os << "Titulo: " << c.titulo << endl;
		os << "Duracion: " << c.duracion << "s" << endl;
		os << "Tamanio: " << c.tamanio << "KB" << endl;
		return os;
	}
};

int main() {
	vector<Cancion> canciones{};
	size_t i = 0;

	while (1) {
		uint16_t opcion;
		system("cls");

		cout << "Que desea realizar?" << endl;
		cout << "1. Anadir una cancion" << endl;
		cout << "2. Mostrar titulo de todas las canciones" << endl;
		cout << "3. Buscar un artista / titulo" << endl;

		do {
			cout << "Ingrese opcion: ";
			cin >> opcion;
			if (opcion < 1 || opcion > 3) {
				cout << "La opcion " << opcion << " no existe" << endl;
			}
		} while (opcion < 1 || opcion > 3);

		system("cls");

		switch (opcion) {
			case 1: {
				if (i >= MAX_CANCIONES) {
					cout << "Ya se llego al maximo de canciones!\n";
					system("pause");
					break;
				}

				cin.ignore(); 

				Cancion temp;
				cout << "Ingrese el artista de la cancion: ";
				std::getline(cin, temp.artista);
				cout << "Ingrese el titulo de la cancion: ";
				std::getline(cin, temp.titulo);
				cout << "Ingrese el duracion en segundos de la cancion: ";
				cin >> temp.duracion;
				cout << "Ingrese el tamanio (en KB) de la cancion: ";
				cin >> temp.tamanio;
				
				canciones.push_back(temp);

				i++;
				break;
			}
			case 2:
				if (canciones.empty()) {
					cout << "No hay canciones\n";
					system("pause");
					break;
				}

				for (const auto& c : canciones) {
					cout << c << endl;
				}
				system("pause");
				break;

			case 3:
				string to_find;
				cout << "Ingrese nombre del artista / titulo de la cancion: ";
				cin >> to_find;

				for (const auto& c : canciones) {
					if (c.artista == to_find || c.titulo == to_find) {
						cout << "Cancion encontrada:" << endl;
						cout << c << endl;
						break;
					}
				}

				cout << "No se encontro artista / titulo de la cancion \"" << to_find << '\"' << endl;
				system("pause");
				break;
		}

		system("cls");

		char seguir;
		cout << "Desea continuar? (s/n): ";
		cin >> seguir;
		if (seguir == 'N' || seguir == 'n') 
			return 0; 
	}
}