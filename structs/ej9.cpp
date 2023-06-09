#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_CANCIONES 100

struct Cancion {
	string artista;
	string titulo;
	string nombreCompleto;
	struct Duracion {
		size_t minutos;
		size_t segundos;
		
		friend ostream& operator<<(ostream& os, const Duracion& d) { return os << d.minutos << "m " << d.segundos << "s"; }
	} duracion;
	size_t tamanio;

	friend ostream& operator<<(ostream& os, const Cancion& c) {
		os << "Artista: " << c.artista << endl;
		os << "Titulo: " << c.titulo << endl;
		os << "Nombre: " << c.nombreCompleto << endl;
		os << "Duracion: " << c.duracion << endl;
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
				temp.nombreCompleto = temp.artista + " - " + temp.titulo;
				cout << "Ingrese el duracion en minutos de la cancion: ";
				cin >> temp.duracion.minutos;
				cout << "Ingrese el duracion en segundos de la cancion: ";
				cin >> temp.duracion.segundos;
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
				cout << "Ingrese parte del nombre del artista / titulo de la cancion: ";
				cin.ignore();
				std::getline(cin, to_find);

				bool encontrado = false;
				for (const auto& c : canciones) {
			    if (c.nombreCompleto.find(to_find) != string::npos) {
		        if (!encontrado) {
	            cout << "Canciones encontradas:" << endl;
	            encontrado = true;
		        }
		        cout << c << endl;
			    }
				}

				if (!encontrado) {
			    cout << "No se encontraron canciones que coincidan con \"" << to_find << '\"' << endl;
				}
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