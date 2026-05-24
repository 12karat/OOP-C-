#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <string>
#include <vector>

// Структура для хранения координат точки
struct Point {
    double x;
    double y;
};

// Абстрактный базовый класс "Геометрическая фигура"
class Shape {
public:
    virtual ~Shape() {}
    virtual double calc_area() = 0;      // Расчет площади фигуры
    virtual double calc_perimetr() = 0;  // Вычисление периметра фигуры
    virtual void name() = 0;             // Вывод названия фигуры
};

// Класс Круг
class Circle : public Shape {
private:
    Point center;
    double radius;
public:
    Circle(Point c, double r);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

// Класс Эллипс
class Ellipse : public Shape {
private:
    Point center;
    double radius_x;
    double radius_y;
public:
    Ellipse(Point c, double rx, double ry);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

// Класс Треугольник
class Triangle : public Shape {
private:
    double side_a, side_b, side_c;
public:
    Triangle(double a, double b, double c);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

// Класс Прямоугольник
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

// Класс Многоугольник
class Polygon : public Shape {
private:
    std::vector<Point> vertices;
public:
    Polygon(const std::string& filename); // Конструктор для чтения из файла границ
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

#endif // GEOMETRY_H