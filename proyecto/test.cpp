#include <iostream>

using namespace std;

int main() {
	auto sumar = [](int a, int b) { return a+b; };
	
	
	cout << sumar(1, 2);
}
