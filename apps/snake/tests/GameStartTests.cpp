#include "TestHarness.hpp"
#include "domain/Direction.hpp"
#include "domain/Game.hpp"
#include "domain/Position.hpp"

using namespace snake;

TEST_CASE("Game starts with 3 segments at center, direction Right, and score 0") {
  Game game;

  ASSERT_EQ(game.score(), 0);
  ASSERT_FALSE(game.is_over());
  ASSERT_FALSE(game.is_won());
  ASSERT_TRUE(game.direction() == Direction::Right);

  const auto& body = game.snake().body();
  ASSERT_EQ(body.size(), static_cast<std::size_t>(3));

  // Center horizontal positioning: (20,10), (19,10), (18,10)
  ASSERT_TRUE(body[0] == (Position{.x = 20, .y = 10}));
  ASSERT_TRUE(body[1] == (Position{.x = 19, .y = 10}));
  ASSERT_TRUE(body[2] == (Position{.x = 18, .y = 10}));

  // Food is placed within field and not on snake body
  const Position food = game.food();
  ASSERT_TRUE(game.field().is_inside(food));
  ASSERT_FALSE(game.snake().occupies(food));
}
