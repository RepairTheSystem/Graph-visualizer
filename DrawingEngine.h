#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "MathEngine.h"

using namespace std;

#ifndef Draw_Engine
#define Draw_Engine

// Функция для отрисовки пикселя на изображении
void drawPixel(vector<uint8_t>& image, int width, int x, int y, int red, int green, int blue) {
    int index = (y * width + x) * 3;
    if (x >= 0 && x < width && y >= 0 && y < width){ // исправь на нормальную величину
        image[index] = blue;
        image[index + 1] = green;
        image[index + 2] = red;
    }
}

// Функция для отрисовки отрезка по Брезенхему
void drawLine(vector<uint8_t>& image, int width, int x1, int y1, int x2, int y2, int red, int green, int blue) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    int x = x1;
    int y = y1;

    while (x != x2 || y != y2) {
        drawPixel(image, width, x, y, red, green, blue);
        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (err2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

#endif