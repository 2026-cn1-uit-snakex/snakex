#pragma once

namespace console {

void begin();
void end();
void clear();
void move_cursor(int column, int line);
void sleep_ms(int milliseconds);
bool key_pressed(char& key);

} // namespace console
