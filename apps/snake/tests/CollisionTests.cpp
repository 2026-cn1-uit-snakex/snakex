#include "TestHarness.hpp"
#include "domain/Direction.hpp"
#include "domain/FoodGenerator.hpp"
#include "domain/Game.hpp"
#include "domain/PlayField.hpp"
#include "domain/Position.hpp"
#include "domain/Snake.hpp"

#include <memory>
#include <vector>

using namespace snake;

class MockFoodAt : public IFoodGenerator {
public:
  explicit MockFoodAt(Position pos) : pos_(pos) {}

  [[nodiscard]] std::optional<Position> generate(
      const PlayField&,
      std::span<const Position>) override {
    return pos_;
  }

private:
  Position pos_;
};

TEST_CASE("Collision with right boundary ends game") {
  // Spawn snake near right edge: head at (39, 10)
  Snake custom_snake({Position{.x = 39, .y = 10},
                      Position{.x = 38, .y = 10},
                      Position{.x = 37, .y = 10}});
  Game game(std::make_unique<MockFoodAt>(Position{.x = 0, .y = 0}),
            PlayField{},
            std::move(custom_snake),
            Direction::Right);

  ASSERT_FALSE(game.is_over());
  game.tick();  // Head moves to (40, 10), outside boundary
  ASSERT_TRUE(game.is_over());
}

TEST_CASE("Collision with left boundary ends game") {
  Snake custom_snake({Position{.x = 0, .y = 10},
                      Position{.x = 1, .y = 10},
                      Position{.x = 2, .y = 10}});
  Game game(std::make_unique<MockFoodAt>(Position{.x = 20, .y = 0}),
            PlayField{},
            std::move(custom_snake),
            Direction::Left);

  ASSERT_FALSE(game.is_over());
  game.tick();  // Head moves to (-1, 10)
  ASSERT_TRUE(game.is_over());
}

TEST_CASE("Collision with top boundary ends game") {
  Snake custom_snake({Position{.x = 10, .y = 0},
                      Position{.x = 10, .y = 1},
                      Position{.x = 10, .y = 2}});
  Game game(std::make_unique<MockFoodAt>(Position{.x = 0, .y = 19}),
            PlayField{},
            std::move(custom_snake),
            Direction::Up);

  ASSERT_FALSE(game.is_over());
  game.tick();  // Head moves to (10, -1)
  ASSERT_TRUE(game.is_over());
}

TEST_CASE("Collision with bottom boundary ends game") {
  Snake custom_snake({Position{.x = 10, .y = 19},
                      Position{.x = 10, .y = 18},
                      Position{.x = 10, .y = 17}});
  Game game(std::make_unique<MockFoodAt>(Position{.x = 0, .y = 0}),
            PlayField{},
            std::move(custom_snake),
            Direction::Down);

  ASSERT_FALSE(game.is_over());
  game.tick();  // Head moves to (10, 20)
  ASSERT_TRUE(game.is_over());
}

TEST_CASE("Self collision with snake body ends game") {
  // Construct snake of 5 segments in a hook:
  // head at (10, 10), (10, 11), (9, 11), (9, 10), (9, 9)
  // Moving Up to (10, 9), then Left to (9, 9) would collide with (9, 9)
  Snake custom_snake({Position{.x = 10, .y = 10},
                      Position{.x = 10, .y = 11},
                      Position{.x = 9, .y = 11},
                      Position{.x = 9, .y = 10},
                      Position{.x = 8, .y = 10},
                      Position{.x = 8, .y = 9}});
  Game game(std::make_unique<MockFoodAt>(Position{.x = 0, .y = 0}),
            PlayField{},
            std::move(custom_snake),
            Direction::Left);

  // Moving Left brings head to (9, 10) which is occupied by body segment 3
  game.tick();
  ASSERT_TRUE(game.is_over());
}

TEST_CASE("Tail-chase exception: moving into cell vacated by tail on same tick is not a collision") {
  // 4-segment loop: head at (10, 10), (10, 11), (11, 11), tail at (11, 10)
  // Moving Right moves head to (11, 10).
  // Without food, tail at (11, 10) vacates on the same tick.
  Snake custom_snake({Position{.x = 10, .y = 10},
                      Position{.x = 10, .y = 11},
                      Position{.x = 11, .y = 11},
                      Position{.x = 11, .y = 10}});
  // Food is placed elsewhere (0, 0)
  Game game(std::make_unique<MockFoodAt>(Position{.x = 0, .y = 0}),
            PlayField{},
            std::move(custom_snake),
            Direction::Right);

  game.tick();

  // Should NOT be game over because tail moved
  ASSERT_FALSE(game.is_over());
  ASSERT_TRUE(game.snake().head() == (Position{.x = 11, .y = 10}));
  ASSERT_TRUE(game.snake().tail() == (Position{.x = 11, .y = 11}));
}

TEST_CASE("Tail-chase collision: moving into tail cell while eating food is a collision") {
  // 4-segment loop: head at (10, 10), (10, 11), (11, 11), tail at (11, 10)
  // Food IS at (11, 10).
  // Snake eats food -> grows -> tail at (11, 10) does NOT vacate -> collision!
  Snake custom_snake({Position{.x = 10, .y = 10},
                      Position{.x = 10, .y = 11},
                      Position{.x = 11, .y = 11},
                      Position{.x = 11, .y = 10}});
  Game game(std::make_unique<MockFoodAt>(Position{.x = 11, .y = 10}),
            PlayField{},
            std::move(custom_snake),
            Direction::Right);

  game.tick();

  ASSERT_TRUE(game.is_over());
}
