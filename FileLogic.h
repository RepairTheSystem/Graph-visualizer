#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "DrawingEngine.h"
#include "FruchtermanReingold.h"

using namespace std;

#ifndef FileLog
#define FileLog

void generateGraphImage(vector<pair<int, int>>& edges, int V, const string& filename) {
    int imageSize = 1000;
    int vertexSize = 8; // Vertex diameter 
    
    vector<uint8_t> image(imageSize * imageSize * 3);

    // Filling the image with white color
    for (int i = 0; i < imageSize * imageSize * 3; ++i) {
        image[i] = 255;
    }

    // Determin of the initial coordinates of the vertices on the circle
    vector<Point> vertexCoords(V);
    for (int i = 0; i < V; ++i) {
        double angle = 2 * M_PI * i / V;
        int x = imageSize / 2 + static_cast<int>((imageSize / 3.5 - vertexSize / 2) * cos(angle));
        int y = imageSize / 2 + static_cast<int>((imageSize / 3.5 - vertexSize / 2) * sin(angle));
        vertexCoords[i] = Point(x, y);
    }
      
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

    // Drawing vertices
    for (int i = 0; i < V; ++i) {
        int centerX = vertexCoords[i].x;
        int centerY = vertexCoords[i].y;

        for (int dx = -vertexSize / 2; dx <= vertexSize / 2; ++dx) {
            for (int dy = -vertexSize / 2; dy <= vertexSize / 2; ++dy) {
                if (pow(dx, 2) + pow(dy, 2) < pow(vertexSize / 2, 2)) {
                    int x = centerX + dx;
                    int y = centerY + dy;
                    drawPixel(image, imageSize, x, y, 0, 0, 0);
                }
            }
        }
    }

    // Drawing numbers
    for (int i = 0; i < V; ++i) {
        int centerX = vertexCoords[i].x;
        int centerY = vertexCoords[i].y;

        drawDigit(i, image, centerX, centerY - 10);
    }

    // Saving image
    ofstream outputFile(filename, ios::binary);
    outputFile << "BM";
    int fileSize = 54 + 3 * imageSize * imageSize;
    outputFile.write(reinterpret_cast<char*>(&fileSize), 4);
    string reserver = "\0\0\0\0";
    outputFile.write(reinterpret_cast<char*>(&reserver), 4);
    int dataOffset = 54;
    outputFile.write(reinterpret_cast<char*>(&dataOffset), 4);
    int headerSize = 40;
    outputFile.write(reinterpret_cast<char*>(&headerSize), 4);
    outputFile.write(reinterpret_cast<char*>(&imageSize), 4);
    outputFile.write(reinterpret_cast<char*>(&imageSize), 4);
    short planes = 1;
    outputFile.write(reinterpret_cast<char*>(&planes), 2);
    short bpp = 24;
    outputFile.write(reinterpret_cast<char*>(&bpp), 2);
    int compression = 0;
    outputFile.write(reinterpret_cast<char*>(&compression), 4);
    int dataSize = 3 * imageSize * imageSize;
    outputFile.write(reinterpret_cast<char*>(&dataSize), 4);
    int hResolution = 0;
    outputFile.write(reinterpret_cast<char*>(&hResolution), 4);
    int vResolution = 0;
    outputFile.write(reinterpret_cast<char*>(&vResolution), 4);
    int colors = 0;
    outputFile.write(reinterpret_cast<char*>(&colors), 4);
    int importantColors = 0;
    outputFile.write(reinterpret_cast<char*>(&importantColors), 4);
    outputFile.write(reinterpret_cast<char*>(image.data()), dataSize);

    outputFile.close();

    cout << "The image has been saved successfully: " << filename << endl;
}
#endif