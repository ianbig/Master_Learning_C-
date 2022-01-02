#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

Vector2D::Vector2D() : x(0), y(0) {
}

Vector2D::Vector2D(double x_arg, double y_arg) : x(x_arg), y(y_arg) {
}

double Vector2D::getMagnitude() const {
  double x_pow = std::pow(x, 2.0);
  double y_pow = std::pow(y, 2.0);

  return std::sqrt(x_pow + y_pow);
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;

  ans.x = x + rhs.x;
  ans.y = y + rhs.y;

  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;

  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  double ans = 0.0;
  ans = x * rhs.x + y * rhs.y;

  return ans;
}

void Vector2D::print() const {
  std::printf("<%.2f, %.2f>", x, y);
}
