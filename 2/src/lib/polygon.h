/**
 * @file polygon.h
 * @brief Заголовочный файл класса Polygon для работы с многоугольниками
 */

#ifndef POLYGON_H
#define POLYGON_H

#include <algorithm>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>

#include "point.h"

/**
 * @class Polygon
 * @brief Класс для представления многоугольника как набора точек
 * 
 * Класс Polygon представляет многоугольник как массив точек (вершин).
 * Предоставляет методы для создания, модификации и геометрических
 * преобразований многоугольников.
 */
class Polygon {
private:
    size_t point_count_ = 0; ///< Количество вершин многоугольника
    Point* point_array_ = nullptr; ///< Массив вершин многоугольника
    
public:
    /**
     * @brief Конструктор по умолчанию
     * 
     * Создает пустой многоугольник (0 вершин).
     */
    Polygon() = default;

    /**
     * @brief Конструктор с одной вершиной
     * @param vertex Единственная вершина многоугольника
     */
    Polygon(const Point& vertex): point_count_(1), point_array_(new Point[point_count_]) {
        point_array_[point_count_ - 1] = vertex;
    }

    /**
     * @brief Конструктор с заданным количеством вершин
     * @param vertex_count Количество вершин (создаются точки (0,0))
     */
    Polygon(const size_t vertex_count) : point_count_(vertex_count), point_array_(new Point[point_count_]) {}

    /**
     * @brief Конструктор с массивом вершин
     * @param vertex_count Количество вершин
     * @param vertex_array Массив вершин для копирования
     */
    Polygon(const size_t vertex_count, const Point* const vertex_array) : point_count_(vertex_count), point_array_(new Point[point_count_]) {
        std::copy_n(vertex_array, point_count_, point_array_);
    }

    /**
     * @brief Деструктор
     * 
     * Освобождает память, выделенную под массив вершин.
     */
    ~Polygon() { delete[] point_array_; }

    /**
     * @brief Конструктор копирования
     * @param other Другой многоугольник для копирования
     */
    Polygon(const Polygon& other): point_count_(other.point_count_), point_array_(new Point[point_count_]) {
        std::copy_n(other.point_array_, point_count_, point_array_);
    }

    /**
     * @brief Оператор присваивания (копирование)
     * @param other Другой многоугольник
     * @return Ссылка на текущий объект
     */
    Polygon& operator=(const Polygon& other) {
        if (this != &other) {
            Polygon save_place(other);
            delete[] point_array_;
            point_array_ = save_place.point_array_;
            save_place.point_array_ = nullptr;
            point_count_ = save_place.point_count_;
        }

        return *this;
    }
    
    /**
     * @brief Конструктор перемещения
     * @param other Другой многоугольник для перемещения
     */
    Polygon(Polygon&& other) noexcept : point_count_(other.point_count_), point_array_(other.point_array_) {
        other.point_count_ = 0;
        other.point_array_ = nullptr;
    }

    /**
     * @brief Оператор присваивания (перемещение)
     * @param other Другой многоугольник
     * @return Ссылка на текущий объект
     */
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

    /**
     * @brief Вычислить центр масс многоугольника
     * @return Точка - центр масс (среднее арифметическое всех вершин)
     */
    Point centerOfMass() const {
        float sumX = 0;
        float sumY = 0;
        std::for_each(point_array_, point_array_ + point_count_, [&](Point &point) {
            sumX += point.getX();
            sumY += point.getY();
        });
        
        return Point(sumX / point_count_, sumY / point_count_);
    }

    /**
     * @brief Добавить вершину к многоугольнику
     * @param point Новая вершина для добавления
     * @return Ссылка на текущий объект
     */
    Polygon& operator+=(const Point& point) {
        Point* new_point_array = new Point[point_count_ + 1];
        std::copy_n(point_array_, point_count_, new_point_array);
        new_point_array[point_count_] = point;
        delete[] point_array_;
        point_array_ = new_point_array;
        point_count_++;

        return *this;
    }

    /**
     * @brief Получить доступ к вершине по индексу (неконстантная версия)
     * @param index Индекс вершины
     * @return Ссылка на вершину
     */
    Point& operator[](size_t index) {
        if (index > point_count_ - 1) {
            throw std::out_of_range("index");
        }
        return point_array_[index];
    }
    
    /**
     * @brief Получить доступ к вершине по индексу (константная версия)
     * @param index Индекс вершины
     * @return Константная ссылка на вершину
     */
    const Point& operator[](size_t index) const {
        if (index > point_count_ - 1) {
            throw std::out_of_range("index");
        }
        return point_array_[index];
    }

    /**
     * @brief Повернуть многоугольник вокруг точки
     * @param center Центр поворота
     * @param angle Угол поворота в градусах (должен быть кратен 90°)
     * @throws std::invalid_argument если угол не кратен 90°
     */
    void rotate(const Point& center, size_t angle) {
        angle = angle % 360;
 
        if (angle % 90 != 0) {
            throw std::invalid_argument("the angle is not a multiple of 90 degrees");
        }

        size_t steps = angle / 90;
        for (size_t s = 0; s < steps; ++s) {
            for (size_t i = 0; i < point_count_; ++i) {
                Point relative = point_array_[i] - center;
                Point rotated(relative.getY(), -relative.getX());
                point_array_[i] = rotated + center;
            }   
        }

        return;
    }

    /**
     * @brief Переместить многоугольник на заданный вектор
     * @param vector Вектор перемещения
     */
    void move(const Point& vector) noexcept {
        for (size_t i = 0; i < point_count_; i++) {
            point_array_[i] = point_array_[i] + vector;
        }

        return;
    }

    /**
     * @brief Получить количество вершин многоугольника
     * @return Количество вершин
     */
    size_t getCount() const {
        return point_count_;
    }

    /**
     * @brief Оператор вывода многоугольника в поток
     * @param os Выходной поток
     * @param poly Многоугольник для вывода
     * @return Ссылка на поток
     * 
     * Формат вывода: количество_вершин x1 y1 x2 y2 ...
     */
    friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) noexcept {
        os << poly.point_count_ << " ";
        for (size_t i = 0; i < poly.point_count_; ++i) {
            os << poly.point_array_[i] << " ";
        }

        return os;
    }

    /**
     * @brief Оператор ввода многоугольника из потока
     * @param is Входной поток
     * @param poly Многоугольник для чтения
     * @return Ссылка на поток
     * 
     * Формат ввода: количество_вершин x1 y1 x2 y2 ...
     * Устанавливает failbit в случае ошибки чтения.
     */
    friend std::istream& operator>>(std::istream& is, Polygon& poly) {
        try{
            size_t numVertices;
            is >> numVertices;
            Polygon polygon(numVertices);
            for (size_t i = 0; i < numVertices; ++i) {
                is >> polygon.point_array_[i];
            }
            poly = std::move(polygon);
        } catch(...) {
            is.setstate(std::ios_base::failbit);        
        }

        return is;
    }
};

#endif