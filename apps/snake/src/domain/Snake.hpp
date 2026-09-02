#pragma once

#include "domain/Direction.hpp"
#include "domain/Position.hpp"

#include <cstddef>
#include <vector>

namespace snake {

class Snake {
public:
  Snake();
  explicit Snake(std::vector<Position> initial_segments);

  [[nodiscard]] const std::vector<Position>& body() const noexcept;
  [[nodiscard]] Position head() const;
  [[nodiscard]] Position tail() const;
  [[nodiscard]] std::size_t length() const noexcept;

  [[nodiscard]] bool occupies(Position position) const noexcept;
  [[nodiscard]] bool occupies_excluding_tail(Position position) const noexcept;

  [[nodiscard]] bool would_reverse(Direction new_direction) const noexcept;

  void step(Position new_head, bool grow);

private:
  std::vector<Position> body_;
};

}  // namespace snake
