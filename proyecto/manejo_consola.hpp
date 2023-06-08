#pragma once

#include <windows.h>

void gotoxy(std::size_t x, std::size_t y) {
	COORD coord;
  coord.X = static_cast<short>(x);
  coord.Y = static_cast<short>(y);
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ocultar_cursor() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(consoleHandle, &cursorInfo);
  cursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

std::pair<int64_t, int64_t> obtener_centro_consola() {
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);

  auto x = ((consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1) / 2)-25;
  auto y = ((consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1) / 2)-15;

  return {x, y};
}

void print_debug(const std::string& str) {
  #ifdef DEBUG
    std::cout << "\x1B[36m" << "[DEBUG] -> " << str << "\033[0m";
  #else
    (void) str;
  #endif
}
