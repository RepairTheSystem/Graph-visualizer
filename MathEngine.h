#include <vector>
#include <algorithm>

using std::vector;
using std::min;
using std::max;

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

// Function for converting a list of edges to an adjacency list
vector<vector<int>> edgesToAdjacencyList(const vector<std::pair<int, int>>& edges) {
    int maxVertex = -1;
    for (const auto& edge : edges) {
        maxVertex = max(maxVertex, max(edge.first, edge.second));
    }

    vector<vector<int>> adjacencyList(maxVertex + 1);
    for (const auto& edge : edges) {
        adjacencyList[edge.first].push_back(edge.second);
        adjacencyList[edge.second].push_back(edge.first);
    }

    return adjacencyList;
}

void scaleAndCenterGraph(vector<Point>& positions, double scaleFactor, int imageSize) {
    double minX = 999999999;
    double maxX = -999999999;
    double minY = 999999999;
    double maxY = -999999999;

    for (const Point& pos : positions) {
        minX = min(minX, pos.x);
        maxX = max(maxX, pos.x);
        minY = min(minY, pos.y);
        maxY = max(maxY, pos.y);
    }

    // the center of mass of the graph
    double centerX = (minX + maxX) / 2.0;
    double centerY = (minY + maxY) / 2.0;

    // Scale the coordinates of the vertices
    for (Point& pos : positions) {
        pos.x = (pos.x - centerX) * scaleFactor + centerX + (imageSize / 2.0 - centerX) * (1 - scaleFactor);
        pos.y = (pos.y - centerY) * scaleFactor + centerY + (imageSize / 2.0 - centerY) * (1 - scaleFactor);
    }
}


#endif