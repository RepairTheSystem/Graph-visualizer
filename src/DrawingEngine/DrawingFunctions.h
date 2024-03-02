#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::vector;

#ifndef Draw_Engine
#define Draw_Engine

void drawPixel(vector<uint8_t>& image, int width, int x, int y, int red, int green, int blue);

void drawLine(vector<uint8_t>& image, int width, int x1, int y1, int x2, int y2, int red, int green, int blue);

void drawDigit(int num, vector<uint8_t> &image, int posX, int posY);
 
void drawVertex(vector<uint8_t> &image, int x, int y);
#endif