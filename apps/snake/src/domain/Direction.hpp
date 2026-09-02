#pragma once

#include "domain/Position.hpp"

namespace snake {

enum class Direction { Up, Down, Left, Right };

[[nodiscard]] constexpr bool is_opposite(Direction first,
                                         Direction second) noexcept {
  return (first == Direction::Up && second == Direction::Down) ||
         (first == Direction::Down && second == Direction::Up) ||
         (first == Direction::Left && second == Direction::Right) ||
         (first == Direction::Right && second == Direction::Left);
}

[[nodiscard]] constexpr Position direction_offset(Direction direction) noexcept {
  switch (direction) {
    case Direction::Up:
      return Position{.x = 0, .y = -1};
    case Direction::Down:
      return Position{.x = 0, .y = 1};
    case Direction::Left:
      return Position{.x = -1, .y = 0};
    case Direction::Right:
      return Position{.x = 1, .y = 0};
  }
  return Position{.x = 0, .y = 0};
}

}  // namespace snake
