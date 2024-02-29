#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#ifndef Draw_Engine
#define Draw_Engine

// [comment] Функция не защищена от дурачков: если я передам в качестве параметра red число 1337, все будет ОК, но это же не так?
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

// [comment] очень-очень большая страшная функция, которую будет страшно и сложно дебагать, если что-то пойдет не так
// [comment] я бы разбил ее на несколько более маленьких, она даже в два монитора не влезает :)
// Function for drawing a numbers
void drawDigit(int num, vector<uint8_t> &image, int posX, int posY){
    // [comment] это лучше сделать константой, а то каждый раз при вызове функции мы создаем и удаляем объект, который можно 1 раз создать и юзать
    // [comment] а чтобы к константе не получил доступ кто-нибудь плохой (я могу потом лично объяснить зачем это) лучше все завернуть в класс
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
	// [comment] Проблема во всем коде: при работе с векторами ты пользуешься для перебора типом int. Проблема в том, что на 64-битных платформах тип size_t будет иметь размер 
	// [comment] 64 бита, а на  32-битных платформах -- 32 бита. Из за этого int может переполниться при проходе, и будет очень грустно 
        for (int i = 0; i < nums[currentNum].size(); i++) {
            for (int j = 0; j < nums[currentNum][i].size(); j++){ // [comment] кодстайл :(
                if (nums[currentNum][i][j])
                    drawPixel(image, sqrt(image.size() / 3), posX + j + offset, posY+i, 123, 123, 123); 
            }
        }
        offset += 5;
    }
}
#endif
