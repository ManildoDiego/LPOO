#include <iostream>
#include <array>

using namespace std;

#define NOT_IN_LIMITS(n) (n < 1 || n > 3)

inline char get_player(std::size_t index) { return ((index % 2) == 0) ? 'X' : 'O'; } 

void print_board(array<array<char, 3>, 3> board) {
  cout << "     |     |     " << endl;
  cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  " << endl;
  cout << "_____|_____|_____" << endl;
  cout << "     |     |     " << endl;
  cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  " << endl;
  cout << "_____|_____|_____" << endl;
  cout << "     |     |     " << endl;
  cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  " << endl;
  cout << "     |     |     " << endl;
}

char check_winner(array<array<char, 3>, 3> board) {
  for (std::size_t i = 0; i < 3; i++) {
    if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
      return board[i][0];
    }
  }

  for (std::size_t j = 0; j < 3; j++) {
    if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
      return board[0][j];
    }
  }

  if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return board[0][0];
  }

  if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return board[0][2];
  }

  return '\0';
}

int main() {
	array<array<char, 3>, 3> board{};
	board.fill({' ', ' ', ' '});

	char ganador = '\0';

	for (std::size_t i = 0; ganador == '\0'; i++) {
		uint64_t fila, columna;

		char current_player = get_player(i);

		out_of_limits:
		
		system("cls");
		
		cout << "Juega " << current_player << endl;
		print_board(board);

		cout << "Ingrese fila: ";
		cin >> fila;
		cout << "Ingrese columna: ";
		cin >> columna;

		if (NOT_IN_LIMITS(fila) || NOT_IN_LIMITS(columna)) {
			goto out_of_limits;
		}

		board[fila-1][columna-1] = current_player;
		ganador = check_winner(board);
	}

	return 0;
}