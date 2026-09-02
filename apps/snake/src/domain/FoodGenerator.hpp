#pragma once

#include "domain/PlayField.hpp"
#include "domain/Position.hpp"

#include <algorithm>
#include <optional>
#include <random>
#include <span>
#include <vector>

namespace snake {

class IFoodGenerator {
public:
  virtual ~IFoodGenerator() = default;

  [[nodiscard]] virtual std::optional<Position> generate(
      const PlayField& field, std::span<const Position> occupied_cells) = 0;
};

class RandomFoodGenerator : public IFoodGenerator {
public:
  RandomFoodGenerator() : rng_(std::random_device{}()) {}

  explicit RandomFoodGenerator(std::mt19937::result_type seed) : rng_(seed) {}

  [[nodiscard]] std::optional<Position> generate(
      const PlayField& field,
      std::span<const Position> occupied_cells) override {
    std::vector<Position> free_cells;
    free_cells.reserve(static_cast<std::size_t>(field.width() * field.height()));

    for (int y = 0; y < field.height(); ++y) {
      for (int x = 0; x < field.width(); ++x) {
        Position candidate{.x = x, .y = y};
        const bool is_occupied = std::ranges::any_of(
            occupied_cells,
            [candidate](const Position& occupied) { return occupied == candidate; });
        if (!is_occupied) {
          free_cells.push_back(candidate);
        }
      }
    }

    if (free_cells.empty()) {
      return std::nullopt;
    }

    std::uniform_int_distribution<std::size_t> dist(0, free_cells.size() - 1);
    const std::size_t selected_index = dist(rng_);
    return free_cells.at(selected_index);
  }

private:
  std::mt19937 rng_;
};

}  // namespace snake
