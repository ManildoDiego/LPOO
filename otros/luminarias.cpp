#include <iostream>
#include <array>

using namespace std;

const int NUM_CALLES = 5;
const int NUM_LUCES = 15;

struct Calle {
	using Luces = array<bool, NUM_LUCES>;

	Luces luz;
	int max_luces;

	void encender_luz(int num_luz, int num_calle) {
    if (num_luz > NUM_LUCES || num_luz <= 0) {
      std::cout << "El numero de luz ingresado no es valido." << std::endl;
      return;
    }

    if (max_luces == 0) {
      std::cout << "No se pueden encender mas luces en esta calle." << std::endl;
      return;
    }

    int num_luces_encendidas = 0;
    for (int i = 0; i < NUM_LUCES; i++) {
      if (luz[i]) {
        num_luces_encendidas++;
      }
    }

    if (max_luces) {
      std::cout << "Se ha alcanzado el máximo de luces encendidas en esta calle." << std::endl;
      return;
    }

    luz[num_luz - 1] = true;
    std::cout << "Se ha encendido la luz " << num_luz << " en la calle " << num_calle << "." << std::endl;

    max_luces--;
	}

};
	
template <std::size_t Nm>
using Calles = array<Calle, Nm>;

int main() {
	Calles<NUM_CALLES> calles;

	for (size_t i = 0; i < NUM_CALLES; i++) {
		cout << "Ingrese numero de luces de la calle " << i+1 << ": ";
		cin >> calles[i].max_luces;
	}

	while (true) {
		std::size_t calle;
		cout << "Ingrese calle que quiere prender luz (si ingresa 0 termina el programa): ";
	}
}