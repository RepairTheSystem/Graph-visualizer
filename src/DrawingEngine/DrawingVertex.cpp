#include "DrawingFunctions.h"

void drawVertex(vector<uint8_t> &image, int x, int y, int vertexSize, int imageSize){
for (int dx = -vertexSize / 2; dx <= vertexSize / 2; ++dx) {
        for (int dy = -vertexSize / 2; dy <= vertexSize / 2; ++dy) {
            if (pow(dx, 2) + pow(dy, 2) < pow(vertexSize / 2, 2)) {
                int x = x + dx;
                int y = y + dy;
                drawPixel(image, imageSize, x, y, 0, 0, 0);
            }
        }
    }
}