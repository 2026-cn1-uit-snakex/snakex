#pragma once

namespace snake {

struct Position {
  int x{0};
  int y{0};

  [[nodiscard]] friend constexpr bool operator==(const Position& lhs,
                                                 const Position& rhs) noexcept {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
};

}  // namespace snake
