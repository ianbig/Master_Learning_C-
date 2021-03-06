#include "point.hpp"

#include <cmath>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double x_square = pow(x - p.x, 2), y_square = pow(y - p.y, 2);

  return sqrt(x_square + y_square);
}
