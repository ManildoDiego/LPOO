#include <iostream>

using namespace std;

struct Persona {
	string nombre;
	string apellido;
	int16_t edad;

	friend ostream& operator<<(ostream& os, const Persona& p) {
		return os << "Nombre: " << p.nombre << ", apellido: " << p.apellido << ", edad: " << p.edad;
	}
};

int main() {
	Persona p;

	cout << "Ingrese nombre de la persona: ";
	cin >> p.nombre;
	cout << "Ingrese apellido de la persona: ";
	cin >> p.apellido;
	cout << "Ingrese edad de la persona: ";
	cin >> p.edad;

	cout << "Persona:" << endl;
	cout << p << endl;

	return 0;
}