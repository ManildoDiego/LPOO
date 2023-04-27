#include <iostream>
#include <array>

using namespace std;

using Tablero_t = array<array<char, 3>, 3>;

#define NOT_IN_LIMITS(n) (n < 1 || n > 3)

inline char get_player(std::size_t index) { return ((index % 2) == 0) ? 'X' : 'O'; } 

void print_board(Tablero_t t) {
  cout << "     |     |     " << endl;
  cout << "  " << t[0][0] << "  |  " << t[0][1] << "  |  " << t[0][2] << "  " << endl;
  cout << "_____|_____|_____" << endl;
  cout << "     |     |     " << endl;
  cout << "  " << t[1][0] << "  |  " << t[1][1] << "  |  " << t[1][2] << "  " << endl;
  cout << "_____|_____|_____" << endl;
  cout << "     |     |     " << endl;
  cout << "  " << t[2][0] << "  |  " << t[2][1] << "  |  " << t[2][2] << "  " << endl;
  cout << "     |     |     " << endl;
}

char check_winner(Tablero_t t) {
  for (std::size_t i = 0; i < 3; i++) {
    if (t[i][0] != ' ' && t[i][0] == t[i][1] && t[i][1] == t[i][2]) {
      return t[i][0];
    }
  }

  for (std::size_t j = 0; j < 3; j++) {
    if (t[0][j] != ' ' && t[0][j] == t[1][j] && t[1][j] == t[2][j]) {
      return t[0][j];
    }
  }

  if (t[0][0] != ' ' && t[0][0] == t[1][1] && t[1][1] == t[2][2]) {
    return t[0][0];
  }

  if (t[0][2] != ' ' && t[0][2] == t[1][1] && t[1][1] == t[2][0]) {
    return t[0][2];
  }

  return '\0';
}

bool check_ficha(Tablero_t t, size_t i, size_t j) { return t[i-1][j-1] != ' '; }

void check_full_board(Tablero_t t) {
  // confirmo si no hay espacios vacios
  for (size_t i = 0; i < t.size(); i++) {
		for (size_t j = 0; j < t.size(); j++) {
			if (t[i][j] == ' ') return;
		}
	}

  // imprimo el tablero
	system("cls");
  print_board(t);
  cout << "Emapatron" << endl;
  // return 0;
  exit(0);
}

int main() {
	Tablero_t tablero{};
  // por cada fila la relleno con un array de espacios
	tablero.fill({' ', ' ', ' '});

	char ganador = '\0';
  char current_player;

	for (std::size_t i = 0; ganador == '\0'; i++) {
		uint64_t fila, columna;

		current_player = get_player(i);

		out_of_limits:
		
		system("cls");
		
		cout << "Juega " << current_player << endl;
		print_board(tablero);

		cout << "Ingrese fila: ";
		cin >> fila;
		cout << "Ingrese columna: ";
		cin >> columna;

		if (NOT_IN_LIMITS(fila) || NOT_IN_LIMITS(columna) || check_ficha(tablero, fila, columna)) {
			goto out_of_limits;
		}

		tablero[fila-1][columna-1] = current_player;
		ganador = check_winner(tablero);
    check_full_board(tablero);
	}

	system("cls");
  print_board(tablero);
  cout << "Gano " << ganador;

	return 0;
}