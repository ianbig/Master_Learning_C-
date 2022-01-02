#ifndef _CIRCLE_HPP
#define _CIRCLE_HPP

#include <cmath>
#include <iostream>

#include "point.hpp"

#define PI 3.1415926535

class Circle {
  Point center;
  const double radius;

 public:
  Circle(Point center_args, const double radius_args);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif
