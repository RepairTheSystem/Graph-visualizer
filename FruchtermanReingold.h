#include <vector>
#include <cmath>

#include "MathEngine.h"
using std::vector; // [comment] А почему в других местах делали using namespace std, а тут только вектор? Нет единообразия
// [comment] но я бы порекомендовал везде поступать как тут, чтобы избежать конфликта имен

#ifndef Algos
#define Algos
class FruchtermanReingold {
public:
    FruchtermanReingold(vector<vector<int>> adj_list, double k = 30.0); // [comment] тут имя параметра списка смежности отличается от имени в реализации, некрасиво
    void operator()(vector<Point>& positions);

private:
    vector<Vector2D> force;
    const vector<vector<int>> adj_list;
    vector<std::pair<int, int>> edges; // [comment] А это нам зачем?)
    const double kEasticity;
    const double kSquared; // [comment] Почему где-то переменные snake_case, а где-то camelCase?
    double temp;
};

// [comment] Раз уж ты разделил объявление и определение класса и методов, то лучше разделить их по .cpp и .h файлам

FruchtermanReingold::FruchtermanReingold(const vector<vector<int>> g, double k)
    : adj_list(g), kEasticity(k), kSquared(k * k),
    temp(10 * sqrt(g.size())), force(adj_list.size()) {}

void FruchtermanReingold::operator()(vector<Point>& positions) {
    Vector2D zero = { 0, 0 };
    fill(force.begin(), force.end(), zero);

    // calculate the repulsion forces
    for (int v_id = 0; v_id < adj_list.size(); v_id++) {
        for (int other_id = v_id + 1; other_id < adj_list.size(); ++other_id) {
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
    for (int v_id = 0; v_id < adj_list.size(); ++v_id) {
        for (int adj_id : adj_list[v_id]) {    
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
    for (int v_id = 0; v_id < adj_list.size(); v_id++) {
        double forceNorm = force[v_id].norm();
        if (forceNorm < 1.0) {
            continue;
        }
        double appForceNorm = std::min(forceNorm, temp);
        Vector2D appForce = force[v_id] / forceNorm * appForceNorm;

        positions[v_id] += appForce;
    }

   // [comment] Было бы круто сделать возможность кастомизировать стратегию понижения температуры
    // Cool down 
    if (temp > 1) {
        temp *= 0.97;
    } else {
        temp = 1;
    }
}


#endif
