#include <cstdlib>
#include <iostream>
#include <array>

using namespace std;

#define CANT_NUMEROS 5

array<double, CANT_NUMEROS> ordenamiento_burbuja(array<double, CANT_NUMEROS> arr) {
	for (size_t i = 0; i < (arr.size() - 1); i++) {
	  for (size_t j = 0; j < (arr.size() - i - 1); j++) {
			if (arr[j] > arr[j + 1]) {
			  double temp = arr[j];
			  arr[j] = arr[j + 1];
			  arr[j + 1] = temp;
			}
	  }
	}

	return arr;
}

int main() {
	array<double, CANT_NUMEROS> numeros;

	for (size_t i = 0; i < numeros.size(); i++) {
		cout << "Ingrese numero real " << i+1 << ": ";
		cin >> numeros.at(i);
	}

	cout << "Array original: ";
	for (const auto& numero : numeros) {
		cout << numero << ' ';
	}

	numeros = ordenamiento_burbuja(numeros);

	cout << "\nArray ordenado: ";
	for (const auto& numero : numeros) {
		cout << numero << ' ';
	}

	return 0;
}