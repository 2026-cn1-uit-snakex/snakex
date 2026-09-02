#include "domain/Game.hpp"

#include <utility>

namespace snake {

Game::Game() : Game(std::make_unique<RandomFoodGenerator>()) {}

Game::Game(std::unique_ptr<IFoodGenerator> food_generator)
    : food_generator_(std::move(food_generator)) {
  spawn_food();
}

Game::Game(std::unique_ptr<IFoodGenerator> food_generator,
           PlayField field,
           Snake initial_snake,
           Direction initial_direction)
    : field_(field),
      snake_(std::move(initial_snake)),
      current_direction_(initial_direction),
      food_generator_(std::move(food_generator)) {
  spawn_food();
}

const PlayField& Game::field() const noexcept {
  return field_;
}

const Snake& Game::snake() const noexcept {
  return snake_;
}

Direction Game::direction() const noexcept {
  return current_direction_;
}

Position Game::food() const noexcept {
  return food_;
}

int Game::score() const noexcept {
  return score_;
}

bool Game::is_over() const noexcept {
  return is_over_;
}

bool Game::is_won() const noexcept {
  return is_won_;
}

void Game::input_direction(Direction new_direction) {
  if (is_over_) {
    return;
  }

  // Reversal check: verify against current moving snake
  if (snake_.would_reverse(new_direction)) {
    return;
  }

  // Last-input coalescing: record the last valid input
  pending_direction_ = new_direction;
}

void Game::tick() {
  if (is_over_) {
    return;
  }

  // Apply pending direction if any
  if (pending_direction_.has_value()) {
    if (!snake_.would_reverse(pending_direction_.value())) {
      current_direction_ = pending_direction_.value();
    }
    pending_direction_.reset();
  }

  const Position offset = direction_offset(current_direction_);
  const Position new_head{.x = snake_.head().x + offset.x,
                          .y = snake_.head().y + offset.y};

  // Check boundary collision
  if (!field_.is_inside(new_head)) {
    is_over_ = true;
    return;
  }

  const bool eating_food = (new_head == food_);

  // Check body collision with tail-chase exception
  // If eating food, tail will NOT vacate on this tick, so check against entire body.
  // If not eating food, tail vacates on this tick, so check against body excluding tail.
  const bool body_collision = eating_food
                                  ? snake_.occupies(new_head)
                                  : snake_.occupies_excluding_tail(new_head);

  if (body_collision) {
    is_over_ = true;
    return;
  }

  // Advance snake
  snake_.step(new_head, eating_food);

  if (eating_food) {
    score_ += PointsPerFood;
    spawn_food();
  }
}

void Game::reset() {
  snake_ = Snake{};
  current_direction_ = Direction::Right;
  pending_direction_.reset();
  score_ = 0;
  is_over_ = false;
  is_won_ = false;
  spawn_food();
}

void Game::spawn_food() {
  if (!food_generator_) {
    return;
  }

  const auto next_pos = food_generator_->generate(field_, snake_.body());
  if (next_pos.has_value()) {
    food_ = next_pos.value();
  } else {
    // No free cells remain - the snake fills the play field
    is_over_ = true;
    is_won_ = true;
  }
}

}  // namespace snake
