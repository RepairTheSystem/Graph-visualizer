#include "GraphPosition.h"

#define M_PI 3.14

// Function for converting a list of edges to an adjacency list
vector<vector<int>> edgesToAdjacencyList(const vector<pair<int, int>>& edges) {
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

    // Масштабировать координаты вершин
    for (Point& pos : positions) {
        pos.x = (pos.x - centerX) * scaleFactor + centerX + (imageSize / 2.0 - centerX) * (1 - scaleFactor);
        pos.y = (pos.y - centerY) * scaleFactor + centerY + (imageSize / 2.0 - centerY) * (1 - scaleFactor);
    }
}

vector<Point> getStartCoords(int V, int imageSize, int vertexSize){
    vector<Point> vertexCoords;
    for (int i = 0; i < V; ++i) {
        double angle = 2 * M_PI * i / V;
        int x = imageSize / 2 + static_cast<int>((imageSize / 3.5 - vertexSize / 2) * cos(angle));
        int y = imageSize / 2 + static_cast<int>((imageSize / 3.5 - vertexSize / 2) * sin(angle));
        vertexCoords[i] = Point(x, y);
    }
    return vertexCoords;
}
