#include <vector>
#include <cmath>

#include "MathEngine.h"
using std::vector;

#ifndef Algos
#define Algos
class FruchtermanReingold {
public:
    FruchtermanReingold(vector<vector<int>> adj_list, double k = 30.0);
    void operator()(vector<Point>& positions);

private:
    const vector<vector<int>> adj_list;
    const double k_;
    const double k_squared_;
    double temp_;
    vector<std::pair<int, int>> edges_;
    vector<Vector2D> mvmts_;
};

FruchtermanReingold::FruchtermanReingold(const vector<vector<int>> g, double k)
    : adj_list(g)
    , k_(k)
    , k_squared_(k * k)
    , temp_(10 * sqrt(g.size()))
    , mvmts_(adj_list.size()) {}

void FruchtermanReingold::operator()(vector<Point>& positions) {
    Vector2D zero = { 0, 0 };
    fill(mvmts_.begin(), mvmts_.end(), zero);

    // Repulsion force between vertice pairs
    for (int v_id = 0; v_id < adj_list.size(); v_id++) {
        for (int other_id = v_id + 1; other_id < adj_list.size(); other_id++) {
            if (v_id == other_id) {
                continue;
            }

            Vector2D delta = positions[v_id] - positions[other_id];
            double distance = delta.norm();
            // TODO: handle distance == 0.0

            // > 1000.0: not worth computing
            if (distance > 1000.0) {
                continue;
            }

            double repulsion = k_squared_ / distance;

            mvmts_[v_id] += delta / distance * repulsion;
            mvmts_[other_id] -= delta / distance * repulsion;
        }

        // Attraction force between edges
        for (int adj_id : adj_list[v_id]) {
            if (adj_id > v_id) {
                continue;
            }

            Vector2D delta = positions[v_id] - positions[adj_id];
            double distance = delta.norm();
            if (distance == 0.0) {
                continue;
            }

            double attraction = distance * distance / k_;

            mvmts_[v_id] -= delta / distance * attraction;
            mvmts_[adj_id] += delta / distance * attraction;
        }
    }
    /* 
    for (int v_id = 0; v_id < adj_list.size(); v_id++) {
        cout << positions[v_id].x << " " << positions[v_id].y << endl;
    }
    */

    // Max movement capped by current temperature
    for (int v_id = 0; v_id < adj_list.size(); v_id++) {
        double mvmt_norm = mvmts_[v_id].norm();
        // < 1.0: not worth computing
        if (mvmt_norm < 1.0) {
            continue;
        }
        double capped_mvmt_norm = std::min(mvmt_norm, temp_);
        Vector2D capped_mvmt = mvmts_[v_id] / mvmt_norm * capped_mvmt_norm;

        positions[v_id] += capped_mvmt;
    }
    /* 
    cout << "-----------------" << endl;
    for (int v_id = 0; v_id < adj_list.size(); v_id++) {
        cout << positions[v_id].x << " " << positions[v_id].y << endl;
    }
    */

    // Cool down fast until we reach 1.5, then stay at low temperature
    if (temp_ > 1.5) {
        temp_ *= 0.85;
    } else {
        temp_ = 1.5;
    }
}


#endif