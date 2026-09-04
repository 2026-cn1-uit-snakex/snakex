#include "domain/Direction.hpp"
#include "domain/Game.hpp"
#include "domain/PlayField.hpp"
#include "platform/Console.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace {

constexpr int TickIntervalMs = 150;
constexpr int EndScreenPollMs = 50;
constexpr int RequiredColumns = snake::FieldWidth + 2;
constexpr int RequiredLines = snake::FieldHeight + 3;

void draw_boundary(const snake::PlayField& field) {
  const int width = field.width();
  const int height = field.height();
  const std::string horizontal_border(static_cast<std::size_t>(width + 2), '#');

  console::move_cursor(0, 0);
  std::cout << horizontal_border;

  for (int y = 0; y < height; ++y) {
    console::move_cursor(0, y + 1);
    std::cout << '#';
    console::move_cursor(width + 1, y + 1);
    std::cout << '#';
  }

  console::move_cursor(0, height + 1);
  std::cout << horizontal_border;
}

void draw_play_state(const snake::Game& game) {
  console::clear();
  draw_boundary(game.field());

  const auto food_pos = game.food();
  console::move_cursor(food_pos.x + 1, food_pos.y + 1);
  std::cout << '*';

  for (const auto& segment : game.snake().body()) {
    console::move_cursor(segment.x + 1, segment.y + 1);
    std::cout << 'O';
  }

  console::move_cursor(0, game.field().height() + 2);
  std::cout << "Score: " << game.score();
  std::cout.flush();
}

void draw_end_screen(const snake::Game& game) {
  console::clear();
  console::move_cursor(0, 0);
  std::cout << "Game over! Final score: " << game.score() << "\n";
  std::cout << "Press r to play again, q to exit.";
  std::cout.flush();
}

[[nodiscard]] bool console_large_enough() {
  const auto console_size = console::size();
  if (console_size.columns <= 0 || console_size.lines <= 0) {
    // The console did not report a usable size: skip the check rather than
    // fail a console that may in fact be large enough.
    return true;
  }
  return console_size.columns >= RequiredColumns &&
         console_size.lines >= RequiredLines;
}

int report_failure(const std::string& message) {
  console::end();
  std::cerr << message << '\n';
  return 1;
}

snake::Direction key_to_direction(char key, bool& recognized) {
  recognized = true;
  switch (key) {
    case 'w':
      return snake::Direction::Up;
    case 's':
      return snake::Direction::Down;
    case 'a':
      return snake::Direction::Left;
    case 'd':
      return snake::Direction::Right;
    default:
      recognized = false;
      return snake::Direction::Right;
  }
}

// Plays until the snake dies or the player quits. Returns false when the
// player quit during play, true when the game ended on its own.
bool play_round(snake::Game& game) {
  while (!game.is_over()) {
    char key = 0;
    if (console::key_pressed(key)) {
      if (key == 'q') {
        return false;
      }
      bool recognized = false;
      const snake::Direction direction = key_to_direction(key, recognized);
      if (recognized) {
        game.input_direction(direction);
      }
    }

    game.tick();
    draw_play_state(game);
    console::sleep_ms(TickIntervalMs);
  }
  return true;
}

// Shows the end screen and waits for the player to restart or quit. Returns
// false when the player chose to quit.
bool run_end_screen(const snake::Game& game) {
  draw_end_screen(game);

  while (true) {
    char key = 0;
    if (console::key_pressed(key)) {
      if (key == 'q') {
        return false;
      }
      if (key == 'r') {
        return true;
      }
    }
    console::sleep_ms(EndScreenPollMs);
  }
}

}  // namespace

int main() {
  if (!console::begin()) {
    return report_failure("Error: the console cannot enter the required mode.");
  }

  if (!console_large_enough()) {
    std::ostringstream message;
    message << "Error: the console is too small. Required size: "
            << RequiredColumns << " columns by " << RequiredLines << " lines.";
    return report_failure(message.str());
  }

  snake::Game game;

  while (play_round(game) && run_end_screen(game)) {
    game.reset();
  }

  console::end();
  return 0;
}
