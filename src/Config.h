#include <string>
#include <fstream>

#ifndef Variable
#define Variable

int imageSize = 500; // Resolution
std::ifstream inputFile("../examples/input5.txt"); // Path to input data
std::ofstream outputFile("Graph228.bmp", std::ios::binary); // Name of output file
int vertexSize = 8; // Diametr of vertex
int scaleFactor = 2; // Scaling graph size 
int iteration = 100; // Count of algorithms iterations

#endif