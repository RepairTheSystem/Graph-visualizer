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
        for (size_t other_id = v_id + 1; other_id < adj_list.size(); ++other_id) {
            Vector2D delta = positions[v_id] - positions[other_id];
            double distance = delta.norm();
            if (distance != 0.0) {
                double repulsion = k_ * k_ / distance;
                mvmts_[v_id] += delta / distance * repulsion;
                mvmts_[other_id] -= delta / distance * repulsion;
            }
        }
    }

    // Вычисляем притягивающие силы
    for (size_t v_id = 0; v_id < adj_list.size(); ++v_id) {
        for (size_t adj_id : adj_list[v_id]) {
            if (adj_id > v_id) {
                Vector2D delta = positions[v_id] - positions[adj_id];
                double distance = delta.norm();
                if (distance != 0.0) {
                    double attraction = distance * distance / k_;
                    mvmts_[v_id] -= delta / distance * attraction;
                    mvmts_[adj_id] += delta / distance * attraction;
                }
            }
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
    if (temp_ > 1) {
        temp_ *= 0.97;
    } else {
        temp_ = 1;
    }
}


#endif