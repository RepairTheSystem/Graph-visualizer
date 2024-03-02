#include "DrawingFunctions.h"

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
        int offset = 2 * err;
        if (offset > -dy) {
            err -= dy;
            x += sx;
        }
        if (offset < dx) {
            err += dx;
            y += sy;
        }
    }
}