#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_IMAGENES 700

struct Imagen {
	string nombre;
	struct Pixeles {
		size_t ancho;
		size_t alto;

		friend ostream& operator<<(ostream& os, const Pixeles& p) {
			return os << p.ancho << 'x' << p.alto;
		}
	} dimensiones;
	long double tamanio;

	friend ostream& operator<<(ostream& os, const Imagen& i) {
		os << "Nombre: " << i.nombre << endl;
		os << "Dimensiones: " << i.dimensiones << " pixeles" << endl;
		os << "Tamanio: " << i.tamanio << "KB" << endl;
		return os;
	}
};

int main() {
	vector<Imagen> imagenes{};
	size_t i = 0;

	while (1) {
		uint16_t opcion;
		system("cls");

		cout << "Que desea realizar?" << endl;
		cout << "1. Anadir una ficha" << endl;
		cout << "2. Ver todas las fichas" << endl;
		cout << "3. Buscar ficha" << endl;

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
				if (i >= MAX_IMAGENES) {
					cout << "Ya se llego al maximo de fichas!\n";
					system("pause");
					break;
				}

				cin.ignore(); 

				Imagen temp;
				cout << "Ingrese el nombre de la ficha: ";
				std::getline(cin, temp.nombre);
				cout << "Ingrese el tamanio (en KB) de la ficha: ";
				cin >> temp.tamanio;
				cout << "Ingrese ancho de la ficha: ";
				cin >> temp.dimensiones.ancho;
				cout << "Ingrese alto de la ficha: ";
				cin >> temp.dimensiones.alto;
				
				imagenes.push_back(temp);

				i++;
				break;
			}
			case 2:
				if (imagenes.empty()) {
					cout << "No hay fichas\n";
					system("pause");
					break;
				}

				for (const auto& imagen : imagenes) {
					cout << imagen << endl;
				}
				system("pause");
				break;

			case 3:
				string to_find;
				cout << "Ingrese nombre de la ficha: ";
				cin >> to_find;

				for (const auto& imagen : imagenes) {
					if (imagen.nombre == to_find) {
						cout << "Ficha encontrada:" << endl;
						cout << imagen << endl;
						break;
					}
				}

				cout << "No se encontro ficha de la imagen \"" << to_find << '\"' << endl;
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