#pragma once

namespace console {

struct Size {
  int columns{0};
  int lines{0};
};

[[nodiscard]] bool begin();
void end();
void clear();
void move_cursor(int column, int line);
void sleep_ms(int milliseconds);
bool key_pressed(char& key);
[[nodiscard]] Size size();

} // namespace console
