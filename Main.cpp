#include <iostream>
#include <fstream>
#include "FileLogic.h"
using namespace std;

int main(){
    ifstream inputFile("input.txt"); // file with input data

    int V, E;
    inputFile >> V >> E;

    vector<pair<int, int>> edges;
    for (int i = 0; i < E; i++){
        int u, v;
        inputFile >> u >> v;
        edges.emplace_back(u, v);
    }
    generateGraphImage(edges, V, "GRAPH.bmp");
    return 0;
}