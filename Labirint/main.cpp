#include <iostream>
#include "maze.h"

int main() {
    std::string inputFile = "ДНК_Лабиринт.bmp";
    std::string outputFile = "Решение_Лабиринт.bmp";

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    std::vector<std::vector<Pixel>> grid;

    std::cout << "Loading BMP file..." << std::endl;
    if (!readBMP(inputFile, grid, fileHeader, infoHeader)) {
        std::cerr << "Error reading file!" << std::endl;
        return 1;
    }

    std::cout << "Searching for path using Lee's algorithm..." << std::endl;
    if (findPath(grid, infoHeader.width, infoHeader.height)) {
        std::cout << "Path found! Saving result..." << std::endl;
        if (writeBMP(outputFile, grid, fileHeader, infoHeader)) {
            std::cout << "Success! Saved as " << outputFile << std::endl;
        }
        else {
            std::cerr << "Error saving result file!" << std::endl;
        }
    }
    else {
        std::cout << "Path not found!" << std::endl;
    }

    return 0;
}