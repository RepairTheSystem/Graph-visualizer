#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

#ifndef FileLog
#define FileLog

void generateGraphImage(vector<pair<int, int>>& edges, int V, const string& filename) {
    int imageSize = 1000;
    int vertexSize = 8; // Vertex diameter 
    

    
    vector<Point> vertexCoords(V);
    
      
    // Redefining the type of edges
    vector<vector<int>> adjList = edgesToAdjacencyList(edges);
    FruchtermanReingold algorithm(adjList);

    for (int i = 0; i < 100; i++){
        algorithm(vertexCoords);
    }

    scaleAndCenterGraph(vertexCoords, 1.4, imageSize);

    // Drawing edges
    for (const auto& edge : edges) {
        int u = edge.first, v = edge.second;
        drawLine(image, imageSize, vertexCoords[u].x, vertexCoords[u].y, vertexCoords[v].x, vertexCoords[v].y, 0, 0, 0);
    }

    // Drawing numbers
    for (int i = 0; i < V; ++i) {
        int centerX = vertexCoords[i].x;
        int centerY = vertexCoords[i].y;

        drawDigit(i, image, centerX, centerY - 10);
    }

    // Saving image
    ofstream outputFile(filename, ios::binary);
    
    outputFile.write(reinterpret_cast<char*>(image.data()), dataSize);

    outputFile.close();

    cout << "The image has been saved successfully: " << filename << endl;
}


#endif