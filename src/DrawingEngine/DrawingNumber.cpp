<<<<<<< HEAD:src/DrawingEngine/DrawingNumber.cpp
#include "DrawingFunctions.h"
=======
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::vector;

#ifndef Draw_Engine
#define Draw_Engine

// Function for rendering a pixel on an image
void drawPixel(vector<uint8_t>& image, int width, int x, int y, int red, int green, int blue) {
    int index = (y * width + x) * 3;
    if (x >= 0 && x < width && y >= 0 && y < width){
        image[index] = blue;
        image[index + 1] = green;
        image[index + 2] = red;
    }
}

// Function for drawing a segment based on Bresenhem 
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
>>>>>>> f9d1b60e854651be4c6f446570073e8ed7b61348:DrawingEngine.h

// Function for drawing a numbers
void drawDigit(int num, vector<uint8_t> &image, int posX, int posY){
    vector<vector<vector<bool>>> nums = {
        { // 0
            {1, 1, 1},
            {1, 0, 1},
            {1, 0, 1},
            {1, 0, 1},
            {1, 1, 1}
        },
        { // 1
            {1, 1, 1},
            {0, 1, 0},
            {0, 1, 0},
            {1, 1, 0},
            {0, 1, 0}
        },
        { // 2
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1}
        },
        { // 3
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1}
        },
        { // 4
            {0, 0, 1},
            {0, 0, 1},
            {1, 1, 1},
            {1, 0, 1},
            {1, 0, 1}
        },
        { // 5
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1}
        },
        { // 6
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1}
        },
        { // 7
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
            {1, 1, 1}
        },
        { // 8
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1}
        },
        { // 9
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1}
        }
    };

    int offset = 0;
    // Parsing numbers into digits
    vector<int> digits = {};
    if (num == 0)
        digits.push_back(0);
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    reverse(digits.begin(), digits.end());

    // Rendering
    for (int index = 0; index < digits.size(); index++) {
        int currentNum = digits[index];
        for (int i = 0; i < nums[currentNum].size(); i++) {
            for (int j = 0; j < nums[currentNum][i].size(); j++){
                if (nums[currentNum][i][j])
                    drawPixel(image, sqrt(image.size() / 3), posX + j + offset, posY+i, 255, 0, 0);
            }
        }
        offset += 5;
    }
}