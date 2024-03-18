#include "DrawingFunctions.h"

// Function for drawing a segment based on Bresenhem 
#include "DrawingFunctions.h"

// Function for drawing a line segment using Bresenham's algorithm
void drawLine(vector<uint8_t>& image, int width, const int x1, const int y1, const int x2, const int y2, int red, int green, int blue) {
    // Calculate differences between coordinates
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    // Determine the direction of movement along x and y axes
    int stepX = x1 < x2 ? 1 : -1;
    int stepY = y1 < y2 ? 1 : -1;
    // Initialize error value
    int error = dx - dy;
    // Initialize starting point
    int currentX = x1;
    int currentY = y1;

    // Iterate over the line using Bresenham's algorithm
    while (currentX != x2 || currentY != y2) {
        // Draw a pixel at current position
        drawPixel(image, width, currentX, currentY, red, green, blue);
        // Calculate error offset
        int errorOffset = 2 * error;
        // Update x coordinate
        if (errorOffset > -dy) {
            error -= dy;
            currentX += stepX;
        }
        // Update y coordinate
        if (errorOffset < dx) {
            error += dx;
            currentY += stepY;
        }
    }
}
