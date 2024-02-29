#include <vector>
#include <cmath>

#include "MathEngine.h"
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

FruchtermanReingold::FruchtermanReingold(const vector<vector<int>> g, double k)
    : adjList(g), kEasticity(k), kSquared(k * k),
    temp(10 * sqrt(g.size())), force(adjList.size()) {}

void FruchtermanReingold::operator()(vector<Point>& positions) {
    Vector2D zero = { 0, 0 };
    fill(force.begin(), force.end(), zero);

    // Сalculate the repulsion forces
    for (int v_id = 0; v_id < adjList.size(); v_id++) {
        for (int other_id = v_id + 1; other_id < adjList.size(); ++other_id) {
            Vector2D delta = positions[v_id] - positions[other_id];
            double distance = delta.norm();
            if (distance != 0.0) {
                double repulsion = kEasticity * kEasticity / distance;
                force[v_id] += delta / distance * repulsion;
                force[other_id] -= delta / distance * repulsion;
            }
        }
    }

    // Calculate the attractive forces
    for (int v_id = 0; v_id < adjList.size(); ++v_id) {
        for (int adj_id : adjList[v_id]) {    
            if (adj_id > v_id) {
                Vector2D delta = positions[v_id] - positions[adj_id];
                double distance = delta.norm();
                if (distance != 0.0) {
                    double attraction = distance * distance / kEasticity;
                    force[v_id] -= delta / distance * attraction;
                    force[adj_id] += delta / distance * attraction;
                }
            }
        
        }
    }

    // Max movement capped by current temperature
    for (int v_id = 0; v_id < adjList.size(); v_id++) {
        double forceNorm = force[v_id].norm();
        if (forceNorm < 2.0) {
            continue;
        }
        double appForceNorm = std::min(forceNorm, temp);
        Vector2D appForce = force[v_id] / forceNorm * appForceNorm;

        positions[v_id] += appForce;
    }

    // Cool down fast until we reach 1.5, then stay at low temperature
    if (temp > 1) {
        temp *= 0.97;
    } else {
        temp = 1;
    }
}


#endif