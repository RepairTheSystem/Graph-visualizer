#include "MathStructures.h"

struct Point;
// Vector2D in plane
double Vector2D::norm() {
    return std::sqrt(dx * dx + dy * dy);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    dx += other.dx;
    dy += other.dy;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    dx -= other.dx;
    dy -= other.dy;
    return *this;
}

Vector2D& Vector2D::operator*=(double scalar) {
    dx *= scalar;
    dy *= scalar;
    return *this;
}

Vector2D& Vector2D::operator/=(double scalar) {
    if (scalar != 0) {
        dx /= scalar;
        dy /= scalar;
    }
    return *this;
}


Point operator+(const Point& point, const Vector2D& vector) {
    return { point.x + vector.dx, point.y + vector.dy };
}

Point operator-(const Point& point, const Vector2D& vector) {
    return { point.x - vector.dx, point.y - vector.dy };
}

Vector2D operator-(const Point& lhs, const Point& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) {
    return { lhs.dx + rhs.dx, lhs.dy + rhs.dy };
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) {
    return { lhs.dx - rhs.dx, lhs.dy - rhs.dy };
}

Vector2D operator*(const Vector2D& vector, double scalar) {
    return { static_cast<double >(vector.dx * scalar), static_cast<double >(vector.dy * scalar) };
}

Vector2D operator*(double scalar, const Vector2D& vector) {
    return vector * scalar;
}

Vector2D operator/(const Vector2D& vector, double scalar) {
    return { static_cast<double >(vector.dx / scalar), static_cast<double>(vector.dy / scalar) };
}
