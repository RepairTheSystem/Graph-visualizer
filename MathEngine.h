#include <vector>
#include <algorithm>

using std::vector;

#ifndef MathEngine
#define MathEngine

struct Point;

// Vector2D in plane
struct Vector2D {
    double dx, dy;

    Vector2D() : dx(0), dy(0) {}
    Vector2D(double _x, double _y) : dx(_x), dy(_y) {};

    double norm() const {
        return sqrt(dx * dx + dy * dy);
    }
    explicit operator Point() const;
    Vector2D& operator+=(const Vector2D& other) {
        dx += other.dx;
        dy += other.dy;
        return *this;
    }
    Vector2D& operator-=(const Vector2D& other) {
        dx -= other.dx;
        dy -= other.dy;
        return *this;
    }
    Vector2D& operator*=(double scalar) {
        dx *= scalar;
        dy *= scalar;
        return *this;
    }

    Vector2D& operator/=(double scalar) {
        dx /= scalar;
        dy /= scalar;
        return *this;
    }
};
// Dot in plane
struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {};
    explicit operator Vector2D() const;
    Point& operator+=(const Vector2D& vector) {
        x += vector.dx;
        y += vector.dy;
        return *this;
    }
    Point& operator-=(const Vector2D& vector) {
        x -= vector.dx;
        y -= vector.dy;
        return *this;
    }
};

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

// Функция для преобразования списка рёбер в список смежности
vector<vector<int>> edgesToAdjacencyList(const vector<std::pair<int, int>>& edges) {
    int maxVertex = -1;
    for (const auto& edge : edges) {
        maxVertex = std::max(maxVertex, std::max(edge.first, edge.second));
    }

    // Увеличим размер adjacencyList до максимального номера вершины + 1
    vector<vector<int>> adjacencyList(maxVertex + 1);
    for (const auto& edge : edges) {
        adjacencyList[edge.first].push_back(edge.second);
        adjacencyList[edge.second].push_back(edge.first);
    }

    return adjacencyList;
}
#endif