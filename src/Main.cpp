#include <iostream>
#include <fstream>
#include <vector>

#include "File/FillingFunctions.h"

using namespace std;

int main(){
    ifstream inputFile("examples/input3.txt"); // file with input data
    ofstream outputFile("Graph228", ios::binary);
    int imageSize = 800;
    int V, E;
    inputFile >> V >> E;

    vector<pair<int, int>> edges;
    for (int i = 0; i < E; i++){
        int u, v;
        inputFile >> u >> v;
        edges.emplace_back(u, v);
    }
    fillPixels(outputFile, imageSize, V, edges);
    return 0;
}