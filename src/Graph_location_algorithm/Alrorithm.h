#include <vector>
#include <cmath>

#include "../Math/MathStructures.h"
using std::vector;

#ifndef Algos
#define Algos
class LocAlgorithm {
public:
    LocAlgorithm(vector<vector<int>> adjList, double k = 30.0);
    void operator()(vector<Point>& positions);

private:
    const vector<vector<int>> adjList;
    const double kElast;
    const double kSquared;
    double temp;
    vector<Vector2D> force;
};


#endif