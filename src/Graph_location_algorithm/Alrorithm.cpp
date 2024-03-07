#include "Alrorithm.h"

// Constructor
LocAlgorithm::LocAlgorithm(const vector<vector<int>> g, double k)
    : adjList(g), kElast(k), kSquared(k * k),
    temp(10 * sqrt(g.size())), force(adjList.size()) {}

void LocAlgorithm::operator()(vector<Point>& positions) {
    Vector2D zero = { 0, 0 };
    fill(force.begin(), force.end(), zero);

    // Calculate repulsion forces between nodes
    for (int v_id = 0; v_id < adjList.size(); v_id++) {
        for (int other_id = v_id + 1; other_id < adjList.size(); ++other_id) {
            Vector2D delta = positions[v_id] - positions[other_id];
            double distance = delta.norm();
            if (distance != 0.0) {
                // Calculate repulsion force based on distance
                double repulsion = kElast * kElast / distance;
                // Apply forces to both nodes
                force[v_id] += delta / distance * repulsion;
                force[other_id] -= delta / distance * repulsion;
            }
        }
    }

    // Calculate attractive forces between connected nodes
    for (int v_id = 0; v_id < adjList.size(); ++v_id) {
        for (int adj_id : adjList[v_id]) {    
            if (adj_id > v_id) {
                Vector2D delta = positions[v_id] - positions[adj_id];
                double distance = delta.norm();
                if (distance != 0.0) {
                    // Calculate attraction force based on distance
                    double attraction = distance * distance / kElast;
                    // Apply forces to both connected nodes
                    force[v_id] -= delta / distance * attraction;
                    force[adj_id] += delta / distance * attraction;
                }
            }
        }
    }

    // Limit maximum node movement by current temperature
    for (int v_id = 0; v_id < adjList.size(); v_id++) {
        double forceNorm = force[v_id].norm();
        if (forceNorm < 2.0) {
            continue;
        }
        // Scale the force to limit movement
        double appForceNorm = std::min(forceNorm, temp);
        Vector2D appForce = force[v_id] / forceNorm * appForceNorm;

        positions[v_id] += appForce;
    }

    // Cool down temperature, reducing movement
    if (temp > 1) {
        // Fast cooldown until temperature reaches 1
        temp *= 0.97;
    } else {
        // Stay at low temperature to stabilize positions
        temp = 1;
    }
}
