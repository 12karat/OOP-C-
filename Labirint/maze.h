#pragma once
#include <vector>
#include <string>
#include "bmp.h"

// Функция для поиска пути волновым алгоритмом
bool findPath(std::vector<std::vector<Pixel>>& grid, int width, int height);

// Функции чтения и записи BMP
bool readBMP(const std::string& filename, std::vector<std::vector<Pixel>>& grid, BMPFileHeader& fileHeader, BMPInfoHeader& infoHeader);
bool writeBMP(const std::string& filename, const std::vector<std::vector<Pixel>>& grid, const BMPFileHeader& fileHeader, const BMPInfoHeader& infoHeader);