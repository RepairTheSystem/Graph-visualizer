#include <vector>
#include <cmath>

using namespace std;

#ifndef MathEngine
#define MathEngine

struct Point;

// Vector2D in plane
struct Vector2D {
    double dx, dy;

    Vector2D() : dx(0), dy(0) {}
    Vector2D(double _x, double _y) : dx(_x), dy(_y) {};

    double norm();
    explicit operator Point() const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator*=(double scalar);
    Vector2D& operator/=(double scalar);
};
// Dot in plane
struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {};
    explicit operator Vector2D() const;
    Point& operator+=(const Vector2D& vector);
    Point& operator-=(const Vector2D& vector);
};

Point operator+(const Point& point, const Vector2D& vector);

Point operator-(const Point& point, const Vector2D& vector);

Vector2D operator-(const Point& lhs, const Point& rhs);

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);

Vector2D operator*(const Vector2D& vector, double scalar);

Vector2D operator*(double scalar, const Vector2D& vector);

Vector2D operator/(const Vector2D& vector, double scalar);

#endif