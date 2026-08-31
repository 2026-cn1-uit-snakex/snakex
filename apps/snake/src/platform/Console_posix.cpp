#include "platform/Console.hpp"

#include <chrono>
#include <cstdio>
#include <termios.h>
#include <thread>
#include <unistd.h>

namespace console {

namespace {
termios& saved_mode() {
  static termios mode{};
  return mode;
}
} // namespace

void begin() {
  tcgetattr(STDIN_FILENO, &saved_mode());
  termios mode = saved_mode();
  mode.c_lflag = mode.c_lflag & ~(ICANON | ECHO);
  mode.c_cc[VMIN] = 0;
  mode.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &mode);
}

void end() {
  tcsetattr(STDIN_FILENO, TCSANOW, &saved_mode());
}

void clear() {
  printf("\x1b[2J\x1b[H");
}

void move_cursor(int column, int line) {
  printf("\x1b[%d;%dH", line + 1, column + 1);
}

void sleep_ms(int milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool key_pressed(char& key) {
  return read(STDIN_FILENO, &key, 1) == 1;
}

} // namespace console
