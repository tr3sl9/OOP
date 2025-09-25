#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

class Point {
private: 
    float x, y;

public:
    // Конструкторы
    Point();
    Point(float x, float y);
    Point(const float coords[2]);
    
    // Геттеры
    float getX() const;
    float getY() const;

    // Сеттеры
    void setX(float x);
    void setY(float y);
    
    // Методы
    float distanceTo(const Point& other) const;
    Point operatorPlus(const Point& other) const;
    Point operatorMinus(const Point& other) const;
    Point operatorDivision(float divisor) const;
    void rotate90Clockwise();
    
    // Ввод/вывод
    friend std::istream& operator>>(std::istream& is, Point& point);
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};

#endif