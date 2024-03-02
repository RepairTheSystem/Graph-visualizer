#include "FillingFunctions.h"

void fillHeader(ofstream& outputFile, int imageSize){
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
}