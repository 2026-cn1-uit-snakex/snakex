#include "platform/Console.hpp"

#include <chrono>
#include <cstdio>
#include <sys/ioctl.h>
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

bool begin() {
  if (isatty(STDIN_FILENO) == 0) {
    return false;
  }
  if (tcgetattr(STDIN_FILENO, &saved_mode()) == -1) {
    return false;
  }
  termios mode = saved_mode();
  mode.c_lflag = mode.c_lflag & ~(ICANON | ECHO);
  mode.c_cc[VMIN] = 0;
  mode.c_cc[VTIME] = 0;
  if (tcsetattr(STDIN_FILENO, TCSANOW, &mode) == -1) {
    return false;
  }
  printf("\x1b[?25l");
  return true;
}

void end() {
  tcsetattr(STDIN_FILENO, TCSANOW, &saved_mode());
  printf("\x1b[?25h");
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

Size size() {
  winsize window_size{};
  if (ioctl(STDIN_FILENO, TIOCGWINSZ, &window_size) == -1) {
    return Size{};
  }
  return Size{.columns = window_size.ws_col, .lines = window_size.ws_row};
}

} // namespace console
