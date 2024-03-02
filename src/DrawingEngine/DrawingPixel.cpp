#include "DrawingFunctions.h"

// Function for rendering a pixel on an image
void drawPixel(vector<uint8_t>& image, int width, int x, int y, int red, int green, int blue) {
    int index = (y * width + x) * 3;
    if (x >= 0 && x < width && y >= 0 && y < width){
        image[index] = blue;
        image[index + 1] = green;
        image[index + 2] = red;
    }
}