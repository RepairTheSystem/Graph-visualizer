#include "DrawingFunctions.h"

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