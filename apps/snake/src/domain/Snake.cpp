#include "domain/Snake.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace snake {

Snake::Snake()
    : body_{Position{.x = 20, .y = 10},
            Position{.x = 19, .y = 10},
            Position{.x = 18, .y = 10}} {}

Snake::Snake(std::vector<Position> initial_segments)
    : body_(std::move(initial_segments)) {
  if (body_.empty()) {
    throw std::invalid_argument("Snake body cannot be empty");
  }
}

const std::vector<Position>& Snake::body() const noexcept {
  return body_;
}

Position Snake::head() const {
  if (body_.empty()) {
    throw std::out_of_range("Snake has no head");
  }
  return body_.front();
}

Position Snake::tail() const {
  if (body_.empty()) {
    throw std::out_of_range("Snake has no tail");
  }
  return body_.back();
}

std::size_t Snake::length() const noexcept {
  return body_.size();
}

bool Snake::occupies(Position position) const noexcept {
  return std::ranges::any_of(
      body_, [position](const Position& segment) { return segment == position; });
}

bool Snake::occupies_excluding_tail(Position position) const noexcept {
  if (body_.size() <= 1) {
    return false;
  }
  return std::ranges::any_of(
      body_.begin(), body_.end() - 1,
      [position](const Position& segment) { return segment == position; });
}

bool Snake::would_reverse(Direction new_direction) const noexcept {
  if (body_.size() <= 1) {
    return false;
  }
  const Position offset = direction_offset(new_direction);
  const Position candidate_next{.x = head().x + offset.x,
                                .y = head().y + offset.y};
  return candidate_next == body_.at(1);
}

void Snake::step(Position new_head, bool grow) {
  body_.insert(body_.begin(), new_head);
  if (!grow) {
    body_.pop_back();
  }
}

}  // namespace snake
