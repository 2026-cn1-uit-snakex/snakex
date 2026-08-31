#pragma once

struct Point {
  int x, y;
};

class Snake {
public:
  Point body[100];
  int length;

  Snake();

  void draw();
  void move(int direction);
};
