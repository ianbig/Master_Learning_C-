/* write your class interface in this file
   write function definitions only if they are very short
 */
class Vector2D {
  double x;
  double y;

 public:
  Vector2D();
  Vector2D(double x_arg, double y_arg);
  double getMagnitude() const;
  Vector2D operator+(const Vector2D & rhs) const;
  Vector2D & operator+=(const Vector2D & rhs);
  double dot(const Vector2D & rhs) const;
  void print() const;
};
