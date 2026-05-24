#include "maze.h"
#include <fstream>
#include <queue>
#include <cmath>
#include <iostream>

struct Point {
    int x, y;
};

// Направления движения: вверх, вниз, влево, вправо
int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

bool readBMP(const std::string& filename, std::vector<std::vector<Pixel>>& grid, BMPFileHeader& fileHeader, BMPInfoHeader& infoHeader) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (infoHeader.bitCount != 24) return false;

    grid.resize(infoHeader.height, std::vector<Pixel>(infoHeader.width));

    int padding = (4 - (infoHeader.width * 3) % 4) % 4;
    file.seekg(fileHeader.offsetData, std::ios::beg);

    for (int i = 0; i < infoHeader.height; ++i) {
        for (int j = 0; j < infoHeader.width; ++j) {
            file.read(reinterpret_cast<char*>(&grid[i][j]), sizeof(Pixel));
        }
        file.seekg(padding, std::ios::cur);
    }

    return true;
}

bool writeBMP(const std::string& filename, const std::vector<std::vector<Pixel>>& grid, const BMPFileHeader& fileHeader, const BMPInfoHeader& infoHeader) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    int padding = (4 - (infoHeader.width * 3) % 4) % 4;
    char padBytes[3] = { 0, 0, 0 };

    for (int i = 0; i < infoHeader.height; ++i) {
        for (int j = 0; j < infoHeader.width; ++j) {
            file.write(reinterpret_cast<const char*>(&grid[i][j]), sizeof(Pixel));
        }
        file.write(padBytes, padding);
    }

    return true;
}

bool findPath(std::vector<std::vector<Pixel>>& grid, int width, int height) {
    Point start = { -1, -1 };
    Point end = { -1, -1 };

    // Сканируем изображение, чтобы найти стартовую (зеленую) и конечную (красную) точки
    // Используем более мягкие пороги для определения цветов
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Pixel p = grid[y][x];

            // Зеленый цвет (старт) - зеленый канал доминирует
            if (p.g > 150 && p.r < 100 && p.b < 100) {
                start = { x, y };
            }
            // Красный цвет (финиш) - красный канал доминирует
            if (p.r > 150 && p.g < 100 && p.b < 100) {
                end = { x, y };
            }
        }
    }

    std::cout << "Image size: " << width << "x" << height << std::endl;
    std::cout << "Start found at: (" << start.x << ", " << start.y << ")" << std::endl;
    std::cout << "End found at: (" << end.x << ", " << end.y << ")" << std::endl;

    if (start.x == -1 || end.x == -1) {
        std::cerr << "Error: Could not find start or end point!" << std::endl;
        return false;
    }

    // Карта расстояний для волнового алгоритма (-1 — не посещено, -2 — стена)
    std::vector<std::vector<int>> dist(height, std::vector<int>(width, -1));

    // Определяем стены - черные или близкие к черному
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Pixel p = grid[y][x];
            // Стена - если все компоненты цвета темные (черный или близкий к черному)
            if (p.r < 50 && p.g < 50 && p.b < 50) {
                dist[y][x] = -2; // стена
            }
        }
    }

    // Волновой алгоритм (BFS)
    std::queue<Point> q;
    q.push(start);
    dist[start.y][start.x] = 0;

    bool found = false;

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.x == end.x && curr.y == end.y) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (dist[ny][nx] == -1) { // Если клетка свободна и еще не посещена
                    dist[ny][nx] = dist[curr.y][curr.x] + 1;
                    q.push({ nx, ny });
                }
            }
        }
    }

    // Если путь найден, восстанавливаем его от конца к началу
    if (found) {
        std::cout << "Path found! Length: " << dist[end.y][end.x] << " steps" << std::endl;

        Point curr = end;
        while (curr.x != start.x || curr.y != start.y) {
            // Закрашиваем путь синим цветом (кроме старта и финиша)
            if (!(curr.x == end.x && curr.y == end.y)) {
                grid[curr.y][curr.x] = { 255, 0, 0 }; // BGR: Синий цвет
            }

            for (int i = 0; i < 4; ++i) {
                int nx = curr.x + dx[i];
                int ny = curr.y + dy[i];

                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    if (dist[ny][nx] == dist[curr.y][curr.x] - 1) {
                        curr = { nx, ny };
                        break;
                    }
                }
            }
        }
        return true;
    }

    std::cout << "Path not found!" << std::endl;
    return false;
}