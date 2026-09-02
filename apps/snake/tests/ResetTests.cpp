#include "TestHarness.hpp"
#include "domain/Direction.hpp"
#include "domain/Game.hpp"
#include "domain/Position.hpp"

using namespace snake;

TEST_CASE("Reset restores initial game state after game over or play") {
  Game game;

  // Move snake into right boundary to end game
  for (int i = 0; i < 25; ++i) {
    game.tick();
  }
  ASSERT_TRUE(game.is_over());

  // Call reset
  game.reset();

  ASSERT_FALSE(game.is_over());
  ASSERT_FALSE(game.is_won());
  ASSERT_EQ(game.score(), 0);
  ASSERT_TRUE(game.direction() == Direction::Right);

  const auto& body = game.snake().body();
  ASSERT_EQ(body.size(), static_cast<std::size_t>(3));
  ASSERT_TRUE(body[0] == (Position{.x = 20, .y = 10}));
  ASSERT_TRUE(body[1] == (Position{.x = 19, .y = 10}));
  ASSERT_TRUE(body[2] == (Position{.x = 18, .y = 10}));

  ASSERT_TRUE(game.field().is_inside(game.food()));
  ASSERT_FALSE(game.snake().occupies(game.food()));
}
