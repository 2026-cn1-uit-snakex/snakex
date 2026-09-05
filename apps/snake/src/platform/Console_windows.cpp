#include "platform/Console.hpp"

#include <conio.h>
#include <cstdlib>
#include <windows.h>

namespace console {

namespace {
HANDLE output_handle() {
  return GetStdHandle(STD_OUTPUT_HANDLE);
}
} // namespace

bool begin() {
  CONSOLE_CURSOR_INFO cursor_info{};
  if (GetConsoleCursorInfo(output_handle(), &cursor_info) == 0) {
    return false;
  }
  cursor_info.bVisible = FALSE;
  return SetConsoleCursorInfo(output_handle(), &cursor_info) != 0;
}

void end() {
  CONSOLE_CURSOR_INFO cursor_info{};
  if (GetConsoleCursorInfo(output_handle(), &cursor_info) != 0) {
    cursor_info.bVisible = TRUE;
    SetConsoleCursorInfo(output_handle(), &cursor_info);
  }
}

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

Size size() {
  CONSOLE_SCREEN_BUFFER_INFO buffer_info{};
  if (GetConsoleScreenBufferInfo(output_handle(), &buffer_info) == 0) {
    return Size{};
  }
  return Size{.columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1,
              .lines = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1};
}

} // namespace console
