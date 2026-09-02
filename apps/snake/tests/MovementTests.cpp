#include "TestHarness.hpp"
#include "domain/Direction.hpp"
#include "domain/Game.hpp"
#include "domain/Position.hpp"

using namespace snake;

TEST_CASE("Snake moves forward by one cell per tick in current direction") {
  Game game;
  const Position initial_head = game.snake().head();
  game.tick();
  const Position new_head = game.snake().head();

  ASSERT_EQ(new_head.x, initial_head.x + 1);
  ASSERT_EQ(new_head.y, initial_head.y);
}

TEST_CASE("Direction change applies on next tick") {
  Game game;
  game.input_direction(Direction::Down);
  // Before tick, direction is still Right
  ASSERT_TRUE(game.direction() == Direction::Right);

  game.tick();
  // After tick, direction is Down and head moved down
  ASSERT_TRUE(game.direction() == Direction::Down);
  ASSERT_TRUE(game.snake().head() == (Position{.x = 20, .y = 11}));
}

TEST_CASE("Reversal rule ignores input opposite to movement") {
  Game game;
  // Snake starts moving Right with 3 segments
  game.input_direction(Direction::Left);
  game.tick();

  // Direction should remain Right, head moves to (21, 10)
  ASSERT_TRUE(game.direction() == Direction::Right);
  ASSERT_TRUE(game.snake().head() == (Position{.x = 21, .y = 10}));
}

TEST_CASE("Input coalescing applies the last valid input in one tick interval") {
  Game game;
  // Moving Right: input Up, then Left (invalid reversal), then Down
  game.input_direction(Direction::Up);
  game.input_direction(Direction::Left);  // Invalid reversal ignored, pending stays Up
  game.input_direction(Direction::Down);  // Valid, pending becomes Down

  game.tick();
  ASSERT_TRUE(game.direction() == Direction::Down);
  ASSERT_TRUE(game.snake().head() == (Position{.x = 20, .y = 11}));
}

TEST_CASE("Input coalescing keeps earlier valid turn if last input is an invalid reversal") {
  Game game;
  // Moving Right: input Up (valid), then Left (invalid reversal)
  game.input_direction(Direction::Up);
  game.input_direction(Direction::Left);

  game.tick();
  ASSERT_TRUE(game.direction() == Direction::Up);
  ASSERT_TRUE(game.snake().head() == (Position{.x = 20, .y = 9}));
}
