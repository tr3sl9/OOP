#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
    float x_, y_;

public:
    Point(float x = 0, float y = 0);
    Point(const float coords[2]);
    
    // Геттеры/сеттеры
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    
    // Операции
    float distanceTo(const Point& other) const;
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point operator/(float divisor) const;
    Point rotate90Clockwise() const;
    
    // Ввод/вывод
    friend std::istream& operator>>(std::istream& is, Point& p);
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif