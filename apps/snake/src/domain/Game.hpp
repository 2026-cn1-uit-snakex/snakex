#pragma once

#include "domain/Direction.hpp"
#include "domain/FoodGenerator.hpp"
#include "domain/PlayField.hpp"
#include "domain/Position.hpp"
#include "domain/Snake.hpp"

#include <memory>
#include <optional>

namespace snake {

constexpr int PointsPerFood = 10;

class Game {
public:
  Game();
  explicit Game(std::unique_ptr<IFoodGenerator> food_generator);
  Game(std::unique_ptr<IFoodGenerator> food_generator,
       PlayField field,
       Snake initial_snake,
       Direction initial_direction);

  [[nodiscard]] const PlayField& field() const noexcept;
  [[nodiscard]] const Snake& snake() const noexcept;
  [[nodiscard]] Direction direction() const noexcept;
  [[nodiscard]] Position food() const noexcept;
  [[nodiscard]] int score() const noexcept;
  [[nodiscard]] bool is_over() const noexcept;
  [[nodiscard]] bool is_won() const noexcept;

  void input_direction(Direction new_direction);
  void tick();
  void reset();

private:
  void spawn_food();

  PlayField field_{};
  Snake snake_{};
  Direction current_direction_{Direction::Right};
  std::optional<Direction> pending_direction_{std::nullopt};
  Position food_{};
  int score_{0};
  bool is_over_{false};
  bool is_won_{false};
  std::unique_ptr<IFoodGenerator> food_generator_;
};

}  // namespace snake
