#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "DrawingEngine.h"

using namespace std;

#ifndef FileLog
#define FileLog

void generateGraphImage(const vector<pair<int, int>>& edges, int V, const string& filename) {
    int imageSize = 600; // Размер изображения
    int vertexSize = 10; // Диаметр вершины
    int edgeLength = 10; // Длина ребра

    vector<uint8_t> image(imageSize * imageSize * 3); // RGB изображение

    // Заполнение изображения белым цветом
    for (int i = 0; i < imageSize * imageSize * 3; ++i) {
        image[i] = 255;
    }

    // Определение координат вершин
    vector<Point> vertexCoords(V);
    for (int i = 0; i < V; ++i) {
        double angle = 2 * M_PI * i / V;
        int x = imageSize / 2 + static_cast<int>((imageSize / 3.5 - vertexSize / 2) * cos(angle));
        int y = imageSize / 2 + static_cast<int>((imageSize / 3.5 - vertexSize / 2) * sin(angle));
        vertexCoords[i] = Point(x, y);
    }

    // Отрисовка рёбер
    for (const auto& edge : edges) {
        int u = edge.first, v = edge.second;
        drawLine(image, imageSize, vertexCoords[u].x, vertexCoords[u].y, vertexCoords[v].x, vertexCoords[v].y, 0, 0, 0);
    }

    // Отрисовка вершин
    for (int i = 0; i < V; ++i) {
        // Получаем координаты центра вершины
        int centerX = vertexCoords[i].x;
        int centerY = vertexCoords[i].y;

        // Отрисовываем круг (вершину)
        for (int dx = -vertexSize / 2; dx <= vertexSize / 2; ++dx) {
            for (int dy = -vertexSize / 2; dy <= vertexSize / 2; ++dy) {
                // Проверяем, находится ли текущий пиксель внутри окружности
                if (pow(dx, 2) + pow(dy, 2) <= pow(vertexSize / 2, 2)) {
                    int x = centerX + dx;
                    int y = centerY + dy;
                    // Отрисовываем пиксель (кружок) черного цвета
                    drawPixel(image, imageSize, x, y, 0, 0, 0);
                }
            }
        }
    }

    // Сохранение изображения
    ofstream outputFile(filename, ios::binary);
    if (!outputFile) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }
    outputFile << "BM";
    int fileSize = 54 + 3 * imageSize * imageSize;
    outputFile.write(reinterpret_cast<char*>(&fileSize), 4);
    string reserver = "\0\0\0\0";
    outputFile.write(reinterpret_cast<char*>(&reserver), 4);
    int dataOffset = 54;
    outputFile.write(reinterpret_cast<char*>(&dataOffset), 4);
    int headerSize = 40;
    outputFile.write(reinterpret_cast<char*>(&headerSize), 4);
    outputFile.write(reinterpret_cast<char*>(&imageSize), 4);
    outputFile.write(reinterpret_cast<char*>(&imageSize), 4);
    short planes = 1;
    outputFile.write(reinterpret_cast<char*>(&planes), 2);
    short bpp = 24;
    outputFile.write(reinterpret_cast<char*>(&bpp), 2);
    int compression = 0;
    outputFile.write(reinterpret_cast<char*>(&compression), 4);
    int dataSize = 3 * imageSize * imageSize;
    outputFile.write(reinterpret_cast<char*>(&dataSize), 4);
    int hResolution = 0;
    outputFile.write(reinterpret_cast<char*>(&hResolution), 4);
    int vResolution = 0;
    outputFile.write(reinterpret_cast<char*>(&vResolution), 4);
    int colors = 0;
    outputFile.write(reinterpret_cast<char*>(&colors), 4);
    int importantColors = 0;
    outputFile.write(reinterpret_cast<char*>(&importantColors), 4);
    outputFile.write(reinterpret_cast<char*>(image.data()), dataSize);

    outputFile.close();

    cout << "Изображение графа успешно сгенерировано: " << filename << endl;
}
#endif