#include "point.h"

Point::Point() : x(0), y(0) {}
Point::Point(float x, float y) : x(x), y(y) {}
Point::Point(const float coords[2]) : x(coords[0]), y(coords[1]) {}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

void Point::setX(float x) {
    this->x = x;
    return;
}

void Point::setY(float y) {
    this->y = y;
    return;
}

float Point::distanceTo(const Point& other) const {
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point& other) const {
   return Point(x - other.x, y - other.y);
}

Point Point::operator/(float divisior) const {
   return Point(x / divisior, y / divisior);
}

void Point::rotate90Clockwise() {
    float temp = x;
    x = y;
    y = temp;
    return;
} 

std::istream& operator>>(std::istream& is, Point& point) {
    is >> point.x >> point.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "Point: (" << point.getX() << " ; " << point.getY() << ")";
    return os;
}