#include "domain/Snake.hpp"

#include "platform/Console.hpp"

#include <iostream>

Snake::Snake() {
  length = 3;
  body[0].x = 10;
  body[0].y = 10;
  body[1].x = 11;
  body[1].y = 10;
  body[2].x = 12;
  body[2].y = 10;
}

void Snake::draw() {
  for (int i = 0; i < length; i++) {
    console::move_cursor(body[i].x, body[i].y);
    std::cout << "X";
  }
}

void Snake::move(int direction) {
  for (int i = length - 1; i > 0; i--) {
    body[i] = body[i - 1];
  }
  if (direction == 0) {
    body[0].x = body[0].x + 1;
  }
  if (direction == 1) {
    body[0].y = body[0].y + 1;
  }
  if (direction == 2) {
    body[0].x = body[0].x - 1;
  }
  if (direction == 3) {
    body[0].y = body[0].y - 1;
  }
}
