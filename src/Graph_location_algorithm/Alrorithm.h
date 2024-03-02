#include <vector>
#include <cmath>

#include "../Math/MathStructures.h"
using std::vector;

#ifndef Algos
#define Algos
class FruchtermanReingold {
public:
    FruchtermanReingold(vector<vector<int>> adjList, double k = 30.0);
    void operator()(vector<Point>& positions);

private:
    const vector<vector<int>> adjList;
    const double kEasticity;
    const double kSquared;
    double temp;
    vector<Vector2D> force;
};


#endif