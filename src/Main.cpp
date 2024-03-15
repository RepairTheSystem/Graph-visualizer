#include <iostream>
#include <fstream>
#include <vector>

#include "File/FillingFunctions.h"
#include "Parametr.h"

using namespace std;

int main(){
    int vertexNum, edgesNum;
    inputFile >> vertexNum >> edgesNum;

    vector<std::pair<int, int>> edges;
    for (int i = 0; i < edgesNum; i++){
        int u, v;
        inputFile >> u >> v;
        u--; v--;
        edges.emplace_back(u, v);
    }

    fillPixels(outputFile, imageSize, vertexNum, edges, iteration, scaleFactor);
    return 0;
}