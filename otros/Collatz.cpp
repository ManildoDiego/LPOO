#include <iostream>

using namespace std;

// También  conocida como conjetura 3n+1 o conjetura de Ulam

// Considere el siguiente proceso repetitivo para un número entero dado: 
// si el número es 1, el proceso termina. De lo contrario, si es par se divide entre 2, y si es impar se multiplica por 3 y se le suma 1. 

int main() {
	// declaro un numero de 64bits sin signo
	uint64_t n;
	cout << "Ingrese numero entero mayor que 1: ";
	cin >> n;

	// si el numero es < 1 significa que no puede realizar este procedimiento
	if (n < 1) {
		cout << "Numero invalido: " << n << endl;
		return 1;
	}

	cout << "Sucesion:" << endl;
	while (n != 1) {
		// si el numero es divisible por 2 lo divido por 2
		if ((n % 2) == 0) {
			n /= 2;
		} 
		
		// si no, lo multiplico por 3 y le sumo 1
		else {
			n = (n * 3) + 1;
		}
		
		cout << n << ' ';
	}

	return 0;
}