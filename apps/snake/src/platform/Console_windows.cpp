#include "platform/Console.hpp"

#include <conio.h>
#include <cstdlib>
#include <windows.h>

namespace console {

void begin() {}

void end() {}

void clear() {
  system("cls");
}

void move_cursor(int column, int line) {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void sleep_ms(int milliseconds) {
  Sleep(milliseconds);
}

bool key_pressed(char& key) {
  if (!kbhit()) {
    return false;
  }
  key = getch();
  return true;
}

} // namespace console
