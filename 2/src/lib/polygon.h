#ifndef POLYGON_H
#define POLYGON_H

#include <algorithm>
#include <iostream>
#include <cmath>

#include "point.h"

class Polygon {
private:
    size_t point_count_;
    Point* point_array_;
    
public:
    Polygon() = default;

    Polygon(const Point& vertex): point_count_(1), point_array_(new Point[point_count_]) {
        point_array_[point_count_ - 1] = vertex;
    }

    Polygon(const size_t vertex_count) : point_count_(vertex_count), point_array_(new Point[point_count_]) {}

    Polygon(const size_t vertex_count, const Point* const vertex_array) : point_count_(vertex_count), point_array_(new Point[point_count_]) {
        std::copy_n(vertex_array, point_count_, point_array_);
    }

    ~Polygon() { delete[] point_array_; }

    Polygon(const Polygon& other): point_count_(other.point_count_), point_array_(new Point[point_count_]) {
        std::copy_n(other.point_array_, point_count_, point_array_);
    }

    Polygon& operator=(const Polygon& other) {
        if (this != &other) {
            delete[] point_array_;
            point_count_ = other.point_count_;
            point_array_ = new Point[point_count_];
            std::copy_n(other.point_array_, point_count_, point_array_);
        }
        return *this;
    }
    
    Polygon(Polygon&& other) noexcept : point_count_(other.point_count_), point_array_(other.point_array_) {
        other.point_count_ = 0;
        other.point_array_ = nullptr;
    }

    Polygon& operator=(Polygon&& other) noexcept {
        if (this != &other) {
            delete[] point_array_;
            point_array_ = other.point_array_;
            point_count_ = other.point_count_;
            other.point_array_ = nullptr;
            other.point_count_ = 0;
        }
        return *this;
    }

    Point centerOfMass() const {
        float sumX = 0;
        float sumY = 0;
        std::for_each(point_array_, point_array_ + point_count_, [&](Point &point) {
            sumX += point.getX();
            sumY += point.getY();
        });
        
        return Point(sumX / point_count_, sumY / point_count_);
    }

    Polygon& operator+=(const Point& point) {
        Point* new_point_array = new Point[point_count_ + 1];
        for (size_t i = 0; i < point_count_; i++) {
            new_point_array[i] = point_array_[i];
        }
        new_point_array[point_count_] = point;
        delete[] point_array_;
        point_array_ = new_point_array;
        point_count_++;

        return *this;
    }

    Point& operator[](size_t index) {
        return point_array_[index];
    }

    void rotate(const Point& center, size_t angle) {
        angle = angle % 360;
        angle = angle < 0 ? angle + 360 : angle;
        if (angle % 90 != 0) {
            throw std::invalid_argument("the angle is not a multiple of 90 degrees");
        }

        int steps = angle / 90;
        for (int s = 0; s < steps; ++s) {
            for (int i = 0; i < point_count_; ++i) {
                Point relative = point_array_[i] - center;
                Point rotated(relative.getY(), -relative.getX());
                point_array_[i] = rotated + center;
            }   
        }

        return;
    }

    void move(const Point& vector) {
        for (size_t i = 0; i < point_count_; i++) {
            point_array_[i] = point_array_[i] + vector;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
        os << poly.point_count_ << " ";
        for (int i = 0; i < poly.point_count_; ++i) {
            os << poly.point_array_[i] << " ";
        }

        return os;
    }

    friend std::istream& operator>>(std::istream& is, Polygon& poly) {
        int numVertices;
        is >> numVertices;
        Point* points = new Point[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            is >> points[i];
        }
        poly = Polygon(numVertices, points);
        delete[] points;

        return is;
    }
};

#endif