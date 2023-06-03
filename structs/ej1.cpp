#include <iostream>

using namespace std;

struct Cancion {
	string artista;
	string titulo;
	long double duracion;
	long double tamanio;

	friend ostream& operator<<(ostream& os, const Cancion& c) {
		os << endl;
		os << "Artista: " << c.artista << endl;
		os << "Titulo: " << c.titulo << endl;
		os << "Duracion: " << c.duracion << "s" << endl;
		os << "Tamanio: " << c.tamanio << "KB" << endl;
		return os;
	}
};

int main() {
	Cancion cancion;

	cout << "Ingrese el artista de la cancion: ";
	getline(cin, cancion.artista);
	cout << "Ingrese el titulo de la cancion: ";
	getline(cin, cancion.titulo);
	cout << "Ingrese el duracion en segundos de la cancion: ";
	cin >> cancion.duracion;
	cout << "Ingrese el tamanio (en KB) de la cancion: ";
	cin >> cancion.tamanio;

	cout << cancion << endl;
}