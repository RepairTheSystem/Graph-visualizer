#include <vector>
#include <algorithm>
#include "MathStructures.h"

using std::vector;
using std::pair;

#ifndef GraphToList
#define GraphToList

void scaleAndCenterGraph(vector<Point>& positions, double scaleFactor, int imageSize);

void scaleAndCenterGraph(vector<Point>& positions, double scaleFactor, int imageSize);

vector<Point> getStartCoords(int V, int imageSize, int vertexSize);

// Function for converting a list of edges to an adjacency list
vector<vector<int>> edgesToAdjacencyList(const vector<pair<int, int>>& edges);
#endif //GraphToList