#include <cstdlib>
#include <iostream>
#include <array>

#define CANT_PERSONAS 8

using namespace std;


struct Persona {
	string nombre;

	struct Fecha {
		int16_t dia;
		int16_t mes;
		int16_t anio;

		friend ostream& operator<<(ostream& os, const Fecha& f) { return os << f.dia << '/' << f.mes << '/' << f.anio; }
	} fecha_nacimiento;

	friend ostream& operator<<(ostream& os, const Persona& p) {
		os << "Nombre: " << p.nombre << endl;
		os << "Fecha de nacimiento: " << p.fecha_nacimiento << endl;
		return os;
	}
};

int main() {
	array<Persona, CANT_PERSONAS> persona;

	for (size_t i = 0; i < CANT_PERSONAS; i++) {
		system("cls");
		cout << "Ingrese nombre de la persona: ";
		cin.ignore();
		getline(cin, persona[i].nombre);

		cout << "Ingrese dia en el que nacio la persona: ";
		cin >> persona[i].fecha_nacimiento.dia;

		cout << "Ingrese mes en el que nacio la persona: ";
		cin >> persona[i].fecha_nacimiento.mes;

		cout << "Ingrese anio en el que nacio la persona: ";
		cin >> persona[i].fecha_nacimiento.anio;
	}

	while (1) {
		uint16_t mes;

		do {
			cout << "Ingrese mes: ";
			cin >> mes;

			if (mes == 0) {
				return 0;
			}
		} while (mes < 1 && mes > 12);

		for (const auto& p : persona) {
			if (p.fecha_nacimiento.mes == mes) {
				cout << p << endl << endl;
			}
		}
	}

	return 0;
}