#include "domain/Snake.hpp"
#include "platform/Console.hpp"

int main() {
  Snake snake;
  int direction = 0;
  char key = 0;

  console::begin();

  while (true) {
    if (console::key_pressed(key)) {
      if (key == 'q') {
        break;
      }
      if (key == 'a') {
        direction = 2;
      }
      if (key == 'w') {
        direction = 3;
      }
      if (key == 'd') {
        direction = 0;
      }
      if (key == 'x') {
        direction = 1;
      }
    }
    console::clear();
    snake.draw();
    snake.move(direction);
    console::sleep_ms(300);
  }

  console::end();

  return 0;
}
