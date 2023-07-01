#pragma once

#include <windows.h>

// va a la posicion x y en la consola
template <typename T1, typename T2>
void gotoxy(T1 x, T2 y) {
	COORD coord;
  coord.X = static_cast<short>(x);
  coord.Y = static_cast<short>(y);
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

template <typename T1, typename T2>
void gotoxy(const std::pair<T1, T2>& coords) {
  gotoxy(coords.first, coords.second);
}

// oculta el cursor en la consola
void setCursorConsola(bool visible = false) {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(consoleHandle, &cursorInfo);
  cursorInfo.bVisible = static_cast<WINBOOL>(visible);
  SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

std::pair<int64_t, int64_t> getCentroConsola() {
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);

  // posiciones de la consola
  const auto x = static_cast<int64_t>(((consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1) / 2)-25);
  const auto y = static_cast<int64_t>(((consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1) / 2)-15);

  return {x, y};
}

void print_debug(const std::string& str) {
  #ifdef DEBUG
    std::cout << "\x1B[36m" << "[DEBUG] -> " << str << "\033[0m";
  #else
    (void) str;
  #endif
}
