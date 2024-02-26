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

void scaleAndCenterGraph(std::vector<Point>& positions, double scale_factor, size_t image_width, size_t image_height) {
    // Найти текущие границы графа
    double min_x = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::lowest();
    double min_y = std::numeric_limits<double>::max();
    double max_y = std::numeric_limits<double>::lowest();

    for (const Point& pos : positions) {
        min_x = std::min(min_x, pos.x);
        max_x = std::max(max_x, pos.x);
        min_y = std::min(min_y, pos.y);
        max_y = std::max(max_y, pos.y);
    }

    // Найти центр масс графа
    double center_x = (min_x + max_x) / 2.0;
    double center_y = (min_y + max_y) / 2.0;

    // Масштабировать координаты вершин
    for (Point& pos : positions) {
        pos.x = (pos.x - center_x) * scale_factor + center_x + (image_width / 2.0 - center_x) * (1 - scale_factor);
        pos.y = (pos.y - center_y) * scale_factor + center_y + (image_height / 2.0 - center_y) * (1 - scale_factor);
    }
}


#endif