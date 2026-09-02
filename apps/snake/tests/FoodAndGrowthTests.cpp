#include "TestHarness.hpp"
#include "domain/FoodGenerator.hpp"
#include "domain/Game.hpp"
#include "domain/PlayField.hpp"
#include "domain/Position.hpp"
#include "domain/Snake.hpp"

#include <memory>
#include <vector>

using namespace snake;

class MockSequenceFoodGenerator : public IFoodGenerator {
public:
  explicit MockSequenceFoodGenerator(std::vector<Position> sequence)
      : sequence_(std::move(sequence)) {}

  [[nodiscard]] std::optional<Position> generate(
      const PlayField&,
      std::span<const Position>) override {
    if (index_ < sequence_.size()) {
      return sequence_.at(index_++);
    }
    return std::nullopt;
  }

private:
  std::vector<Position> sequence_;
  std::size_t index_{0};
};

TEST_CASE("Eating food grows snake by 1 segment and increases score by 10") {
  // Start with food at (21, 10), then next food at (22, 10)
  auto mock_gen = std::make_unique<MockSequenceFoodGenerator>(
      std::vector<Position>{Position{.x = 21, .y = 10}, Position{.x = 22, .y = 10}});

  Game game(std::move(mock_gen));

  ASSERT_EQ(game.score(), 0);
  ASSERT_EQ(game.snake().length(), static_cast<std::size_t>(3));
  ASSERT_TRUE(game.food() == (Position{.x = 21, .y = 10}));

  // Tick 1: Head moves to (21, 10), eats food
  game.tick();

  ASSERT_EQ(game.score(), 10);
  ASSERT_EQ(game.snake().length(), static_cast<std::size_t>(4));
  ASSERT_TRUE(game.snake().head() == (Position{.x = 21, .y = 10}));
  // Tail should still be at (18, 10) because snake grew
  ASSERT_TRUE(game.snake().tail() == (Position{.x = 18, .y = 10}));
  // New food is placed at next sequence position
  ASSERT_TRUE(game.food() == (Position{.x = 22, .y = 10}));
}

TEST_CASE("Multiple food items increase score by 10 points each") {
  auto mock_gen = std::make_unique<MockSequenceFoodGenerator>(
      std::vector<Position>{Position{.x = 21, .y = 10}, Position{.x = 22, .y = 10}});

  Game game(std::move(mock_gen));
  game.tick();  // Eats first food -> score 10, length 4
  ASSERT_EQ(game.score(), 10);
  ASSERT_EQ(game.snake().length(), static_cast<std::size_t>(4));

  game.tick();  // Eats second food -> score 20, length 5
  ASSERT_EQ(game.score(), 20);
  ASSERT_EQ(game.snake().length(), static_cast<std::size_t>(5));
}

TEST_CASE("When no free cells remain, the game ends") {
  // Generator returns no free cell
  auto mock_gen = std::make_unique<MockSequenceFoodGenerator>(
      std::vector<Position>{Position{.x = 21, .y = 10}});

  Game game(std::move(mock_gen));
  // Eat first food, no more food available
  game.tick();

  ASSERT_TRUE(game.is_over());
  ASSERT_TRUE(game.is_won());
}
