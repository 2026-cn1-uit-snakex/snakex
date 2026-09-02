#include "domain/Direction.hpp"
#include "domain/Game.hpp"
#include "platform/Console.hpp"

#include <iostream>

int main() {
  snake::Game game;
  char key = 0;

  console::begin();

  while (!game.is_over()) {
    if (console::key_pressed(key)) {
      if (key == 'q') {
        break;
      }
      if (key == 'w') {
        game.input_direction(snake::Direction::Up);
      } else if (key == 's') {
        game.input_direction(snake::Direction::Down);
      } else if (key == 'a') {
        game.input_direction(snake::Direction::Left);
      } else if (key == 'd') {
        game.input_direction(snake::Direction::Right);
      }
    }

    game.tick();
    console::clear();

    // Render food
    const auto food_pos = game.food();
    console::move_cursor(food_pos.x, food_pos.y);
    std::cout << "*";

    // Render snake
    for (const auto& segment : game.snake().body()) {
      console::move_cursor(segment.x, segment.y);
      std::cout << "O";
    }

    console::sleep_ms(150);
  }

  console::end();
  return 0;
}
