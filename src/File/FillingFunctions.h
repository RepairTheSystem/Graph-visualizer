#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "../Math/GraphPosition.h"
#include "../Graph_location_algorithm/Alrorithm.h"
#include "../DrawingEngine/DrawingFunctions.h"

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;

#ifndef FillFunc
#define FillFunc

void fillHeader(ofstream& outputFile, int imageSize);
void fillPixels(ofstream& outputFile, int imageSize,  int V, vector<pair<int, int>> edges,
                 int iterations, int scaleFactor);
#endif
