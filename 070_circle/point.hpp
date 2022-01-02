#ifndef _POINT_CPP
#define _POINT_CPP
#include <iostream>

class Point {
  double x;
  double y;

 public:
  Point() : x(0), y(0) {}
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};

#endif
