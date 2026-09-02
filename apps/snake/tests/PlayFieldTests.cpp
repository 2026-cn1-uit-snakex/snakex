#include "TestHarness.hpp"
#include "domain/PlayField.hpp"
#include "domain/Position.hpp"

using namespace snake;

TEST_CASE("PlayField dimensions must be 40 wide and 20 high") {
  PlayField field;
  ASSERT_EQ(field.width(), 40);
  ASSERT_EQ(field.height(), 20);
}

TEST_CASE("PlayField playable cells and boundary rules") {
  PlayField field;

  // Corners and center of playable cells
  ASSERT_TRUE(field.is_inside(Position{.x = 0, .y = 0}));
  ASSERT_TRUE(field.is_inside(Position{.x = 39, .y = 0}));
  ASSERT_TRUE(field.is_inside(Position{.x = 0, .y = 19}));
  ASSERT_TRUE(field.is_inside(Position{.x = 39, .y = 19}));
  ASSERT_TRUE(field.is_inside(Position{.x = 20, .y = 10}));

  // Outside boundaries are not playable cells
  ASSERT_FALSE(field.is_inside(Position{.x = -1, .y = 0}));
  ASSERT_FALSE(field.is_inside(Position{.x = 0, .y = -1}));
  ASSERT_FALSE(field.is_inside(Position{.x = 40, .y = 0}));
  ASSERT_FALSE(field.is_inside(Position{.x = 0, .y = 20}));
  ASSERT_FALSE(field.is_inside(Position{.x = 40, .y = 20}));
  ASSERT_FALSE(field.is_inside(Position{.x = -5, .y = -5}));
}
