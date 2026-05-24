#define _USE_MATH_DEFINES  // Добавляем эту строчку, чтобы заработал M_PI
#include "Geometry.h"
#include <iostream>
#include <cmath>
#include <fstream>

// Реализация класса Circle
Circle::Circle(Point c, double r) : center(c), radius(r) {}
double Circle::calc_area() { return M_PI * radius * radius; }
double Circle::calc_perimetr() { return 2.0 * M_PI * radius; }
void Circle::name() { std::cout << "Circle" << std::endl; }

// Реализация класса Ellipse
Ellipse::Ellipse(Point c, double rx, double ry) : center(c), radius_x(rx), radius_y(ry) {}
double Ellipse::calc_area() { return M_PI * radius_x * radius_y; }
double Ellipse::calc_perimetr() {
    return M_PI * (3.0 * (radius_x + radius_y) - std::sqrt((3.0 * radius_x + radius_y) * (radius_x + 3.0 * radius_y)));
}
void Ellipse::name() { std::cout << "Ellipse" << std::endl; }

// Реализация класса Triangle
Triangle::Triangle(double a, double b, double c) : side_a(a), side_b(b), side_c(c) {}
double Triangle::calc_area() {
    double p = calc_perimetr() / 2.0;
    return std::sqrt(p * (p - side_a) * (p - side_b) * (p - side_c));
}
double Triangle::calc_perimetr() { return side_a + side_b + side_c; }
void Triangle::name() { std::cout << "Triangle" << std::endl; }

// Реализация класса Rectangle
Rectangle::Rectangle(double w, double h) : width(w), height(h) {}
double Rectangle::calc_area() { return width * height; }
double Rectangle::calc_perimetr() { return 2.0 * (width + height); }
void Rectangle::name() { std::cout << "Rectangle" << std::endl; }

// Реализация класса Polygon (Чтение из granitsy-uchastka2.txt)
Polygon::Polygon(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    int count;
    if (file >> count) {
        for (int i = 0; i < count; ++i) {
            Point p;
            if (file >> p.x >> p.y) {
                vertices.push_back(p);
            }
        }
    }
    file.close();
}
double Polygon::calc_area() {
    double area = 0.0;
    size_t n = vertices.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}
double Polygon::calc_perimetr() {
    double perim = 0.0;
    size_t n = vertices.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        perim += std::hypot(vertices[i].x - vertices[j].x, vertices[i].y - vertices[j].y);
    }
    return perim;
}
void Polygon::name() { std::cout << "Polygon" << std::endl; }