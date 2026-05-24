#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <cmath>
#include <algorithm>
#include "Geometry.h"

const int GRID_SIZE = 200;

struct GridPoint {
    int r, c;
};

// Функция распознавания типа фигуры по ее контуру
std::string classify_shape(const std::vector<GridPoint>& pixels) {
    // Точки и мелкие черточки (шум) игнорируем
    if (pixels.size() < 8) return "noise";

    int min_r = GRID_SIZE, max_r = 0;
    int min_c = GRID_SIZE, max_c = 0;

    for (const auto& p : pixels) {
        if (p.r < min_r) min_r = p.r;
        if (p.r > max_r) max_r = p.r;
        if (p.c < min_c) min_c = p.c;
        if (p.c > max_c) max_c = p.c;
    }

    double height = max_r - min_r + 1;
    double width = max_c - min_c + 1;

    // Фактическая длина контура (количество символов)
    double contour_length = pixels.size();

    // Ожидаемые периметры для разных геометрических структур
    double rect_perimeter = 2.0 * (width + height);
    double circle_perimeter = M_PI * ((width + height) / 2.0);

    // Для треугольника теоретический периметр контура (в пиксельной сетке)
    // ведет себя близко к гипотенузе + катетам описанного бокса
    double tri_perimeter = width + height + std::hypot(width, height);

    // Вычисляем отклонения от эталонов
    double diff_rect = std::abs(contour_length - rect_perimeter) / rect_perimeter;
    double diff_circle = std::abs(contour_length - circle_perimeter) / circle_perimeter;
    double diff_tri = std::abs(contour_length - tri_perimeter) / tri_perimeter;

    // Сравниваем пропорции сторон (для круга они должны быть близки к 1:1)
    double aspect_ratio = width / height;
    if (aspect_ratio > 1.0) aspect_ratio = 1.0 / aspect_ratio;

    // Выбираем наилучшее совпадение по минимальной ошибке
    if (diff_rect < diff_circle && diff_rect < diff_tri && diff_rect < 0.25) {
        return "rectangle";
    }
    if (diff_circle < diff_rect && diff_circle < diff_tri && diff_circle < 0.25 && aspect_ratio > 0.75) {
        return "circle";
    }
    if (diff_tri < diff_rect && diff_tri < diff_circle && diff_tri < 0.25) {
        return "triangle";
    }

    return "doodle"; // Если ни один шаблон не подошел — это каракуля
}

int main() {
    // Открываем входную карту символов
    std::ifstream infile("input1.dat");
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open input1.dat" << std::endl;
        return 1;
    }

    std::vector<std::string> grid(GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (!std::getline(infile, grid[i])) {
            grid[i] = std::string(GRID_SIZE, ' ');
        }
        if (grid[i].size() < GRID_SIZE) {
            grid[i].append(GRID_SIZE - grid[i].size(), ' ');
        }
    }
    infile.close();

    std::vector<std::vector<bool>> visited(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));

    int rectangles = 0;
    int circles = 0;
    int triangles = 0;
    int doodles = 0;

    // Смещения для 8-связного поиска соседей
    int dr[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    int dc[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

    for (int r = 0; r < GRID_SIZE; ++r) {
        for (int c = 0; c < GRID_SIZE; ++c) {
            // Если нашли непустой символ контура и он еще не обработан
            if (grid[r][c] != ' ' && grid[r][c] != '.' && !visited[r][c]) {
                std::vector<GridPoint> component;
                std::queue<GridPoint> q;

                q.push({ r, c });
                visited[r][c] = true;

                // Сборка контура одной фигуры через BFS
                while (!q.empty()) {
                    GridPoint curr = q.front();
                    q.pop();
                    component.push_back(curr);

                    for (int i = 0; i < 8; ++i) {
                        int nr = curr.r + dr[i];
                        int nc = curr.c + dc[i];

                        if (nr >= 0 && nr < GRID_SIZE && nc >= 0 && nc < GRID_SIZE) {
                            if (grid[nr][nc] != ' ' && grid[nr][nc] != '.' && !visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q.push({ nr, nc });
                            }
                        }
                    }
                }

                // Классификация собранного контура
                std::string type = classify_shape(component);
                if (type == "rectangle") rectangles++;
                else if (type == "circle") circles++;
                else if (type == "triangle") triangles++;
                else if (type == "doodle") doodles++;
            }
        }
    }

    // Сохранение итоговой статистики в файл output.txt
    std::ofstream outfile("output.txt");
    if (outfile.is_open()) {
        outfile << "rectangles: " << rectangles << "\n";
        outfile << "circles: " << circles << "\n";
        outfile << "triangles: " << triangles << "\n";
        outfile << "doodles: " << doodles << "\n";
        outfile.close();
        std::cout << "Results successfully saved to output.txt" << std::endl;
    }

    // Демонстрация работы конструктора Многоугольника (Polygon) из файла
    Polygon poly("granitsy-uchastka2.txt");
    std::cout << "\n--- Polygon Data from File ---" << std::endl;
    // std::fixed заставит выводить числа полностью, а не через "e"
    std::cout << std::fixed;
    std::cout << "Area: " << poly.calc_area() << std::endl;
    std::cout << "Perimeter: " << poly.calc_perimetr() << std::endl;

    return 0;
}