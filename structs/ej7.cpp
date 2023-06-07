#include <cstdlib>
#include <iostream>
#include <array>

#define CANT_PERSONAS 50

using namespace std;

// Realizar un programa que sea capaz de almacenar los datos de 50 personas: 
// nombre, dirección, teléfono, edad (usando una tabla de structs). 
// Deberá ir pidiendo los datos uno por uno, hasta que un nombre se introduzca vacío (se pulse Intro sin teclear nada). 
// Entonces deberá aparecer un menú que permita:
// Mostrar la lista de todos los nombres, 
// Mostrar las personas de una cierta edad; 
// Mostrar las personas cuya inicial sea la que el usuario indique; 
// Salir del programa. (lógicamente, este menú debe repetirse hasta que se escoja la opción de “salir”).

struct Persona {
	string nombre{};
	string direccion;
	uint64_t telefono;
	uint16_t edad;

	bool empty() const { return nombre.empty(); }

	friend ostream& operator<<(ostream& os, const Persona& p) {
		os << "Nombre: " << p.nombre << endl;
		os << "Edad: " << p.edad << endl;
		os << "Direccion: " << p.direccion << endl;
		os << "Telefono: " << p.telefono << endl;
		return os;
	}
};

int main() {
	array<Persona, CANT_PERSONAS> persona;

	for (size_t i = 0; i < CANT_PERSONAS; i++) {
		system("cls");
		cout << "Ingrese nombre de la persona: ";
		cin >> persona[i].nombre;

		if (persona[i].nombre.empty()) {
			break;
		}

		cout << "Ingrese edad de la persona: ";
		cin >> persona[i].edad;
		cout << "Ingrese telefono de la persona: ";
		cin >> persona[i].telefono;
		cout << "Ingrese direccion de la persona: ";
		cin >> persona[i].direccion;
	}

	while (1) {
		int opcion;

		cout << "Que desea realizar?" << endl;
		cout << "1. Mostrar todos los nombres" << endl;
		cout << "2. Mostrar todas las personas de una determinada edad" << endl;
		cout << "3. Mostrar todas las personas de una determinada inicial" << endl;
		cout << "4. Salir" << endl;
		cout << "Ingrese opcion: ";
		cin >> opcion;

		switch (opcion) {
			case 1:
				for (const auto& p : persona) {
					if (!p.empty()) {
						cout << p << endl;
					}
				}
				break;
			case 2: {
				uint16_t edad;
				cout << "Ingrese edad de las personas: ";
				cin >> edad;

				for (const auto& p : persona) {
					if (!p.empty() && edad == p.edad) {
						cout << p << endl;
					}
				}
				
				break;
			}
			case 3: {
				char inicial;
				cout << "Ingrese inicial de las personas: ";
				cin >> inicial;

				for (const auto& p : persona) {
					if (!p.empty() && inicial == p.nombre[0]) {
						cout << p << endl;
					}
				}
				
				break;
			}

			case 4: return 0;
			
			default: 
				cout << "Opcion invalida!\n"; 
				break;
		}
	}

	return 0;
}