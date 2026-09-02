#pragma once

#include "domain/Position.hpp"

namespace snake {

constexpr int FieldWidth = 40;
constexpr int FieldHeight = 20;

class PlayField {
public:
  [[nodiscard]] constexpr int width() const noexcept { return FieldWidth; }

  [[nodiscard]] constexpr int height() const noexcept { return FieldHeight; }

  [[nodiscard]] constexpr bool is_inside(Position position) const noexcept {
    return position.x >= 0 && position.x < FieldWidth && position.y >= 0 &&
           position.y < FieldHeight;
  }
};

}  // namespace snake
