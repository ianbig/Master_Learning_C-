#include "./circle.hpp"

Circle::Circle(Point center_args, const double radius_args) :
    center(center_args),
    radius(radius_args) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  // no intersection
  double d = center.distanceFrom(otherCircle.center);
  if (radius + otherCircle.radius < d) {
    return 0.0;
  }
  double r1 = radius, r2 = otherCircle.radius;
  // one circle within another
  if (std::abs(r1 - r2) >= d) {
    if (r1 > r2) {
      return PI * r2 * r2;
    }

    return PI * r1 * r1;
  }
  // calculate intersection
  double ang1 = std::acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
  double ang2 = std::acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));

  return ang1 * r1 * r1 + ang2 * r2 * r2 - r1 * d * std::sin(ang1);
}
