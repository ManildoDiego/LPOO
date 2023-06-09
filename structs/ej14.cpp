#include <iostream>
#include <array>

using namespace std;

#define N 7

array<double, N> ordenamiento_burbuja(array<double, N> arr) {
	for (size_t i = 0; i < arr.size() - 1; i++) {
	  for (size_t j = 0; j < arr.size() - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        double temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
	  }

	  cout << "Paso " << i + 1 << ": ";
	  for (auto num : arr) {
      cout << num << " ";
	  }
	  cout << endl;
	}

	return arr;
}

array<double, N> ordenamiento_seleccion(array<double, N> arr) {
	for (size_t i = 0; i < arr.size() - 1; i++) {
	  size_t minIndex = i;
	  for (size_t j = i + 1; j < arr.size(); j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
	  }
	  double temp = arr[i];
	  arr[i] = arr[minIndex];
	  arr[minIndex] = temp;

	  cout << "Paso " << i + 1 << ": ";
	  for (auto num : arr) {
      cout << num << " ";
	  }
	  cout << endl;
	}

	return arr;
}

array<double, N> ordenamiento_insercion(array<double, N> arr) {
	for (int i = 1; i < arr.size(); i++) {
	  int key = arr[i];
	  int j = i - 1;
	  while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
	  }
	  arr[j + 1] = key;

	  cout << "Paso " << i << ": ";
	  for (auto num : arr) {
      cout << num << " ";
	  }
	  cout << endl;
	}

	return arr;
}

int main() {
  array<double, N> arr = {64, 34, 25, 12, 22, 11, 90};

  cout << "Ordenamiento burbuja:" << endl;
  ordenamiento_burbuja(arr);
  cout << endl;

  cout << "Ordenamiento por seleccion:" << endl;
  ordenamiento_seleccion(arr);
  cout << endl;

  cout << "Ordenamiento por insercion:" << endl;
  ordenamiento_insercion(arr);
  cout << endl;

  return 0;
}