#include "FillingFunctions.h"

void fillPixels(ofstream& outputFile, int imageSize, int V, vector<pair<int, int>> edges, int iterations, int scaleFactor){
    // An array containing information about pixels
    vector<uint8_t> image(imageSize * imageSize * 3);

    fill(image.begin(), image.end(), 255);

    // Determin of the initial coordinates of the vertices on the circle
    vector<Point> vertexCoords = getStartCoords(V, imageSize, 8);

    vector<vector<int>> adjList = edgesToAdjacencyList(edges);
    
    LocAlgorithm algorithm(adjList);

    // Use an algorithm to find the position of the vertices
    for (int i = 0; i < iterations; i++){
        algorithm(vertexCoords);
    }

    scaleAndCenterGraph(vertexCoords, scaleFactor, imageSize);

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

    fillHeader(outputFile, imageSize);
    outputFile.write(reinterpret_cast<char*>(image.data()), 3 * imageSize * imageSize);
    outputFile.close();

    cout << "The image has been saved successfully" << endl;
}