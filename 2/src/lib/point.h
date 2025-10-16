/**
 * @file point.h
 * @brief Заголовочный файл класса Point для работы с точками на плоскости
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

/**
 * @class Point
 * @brief Класс для представления точки на двумерной плоскости
 * 
 * Класс Point представляет точку с координатами (x, y) и предоставляет
 * методы для работы с точками: вычисление расстояний, арифметические
 * операции, поворот и ввод/вывод.
 */
class Point {
private: 
    float x; ///< Координата X точки
    float y; ///< Координата Y точки

public:
    /**
     * @brief Конструктор по умолчанию
     * 
     * Создает точку с координатами (0, 0).
     */
    Point();
    
    /**
     * @brief Конструктор с параметрами
     * @param x Координата X
     * @param y Координата Y
     */
    Point(float x, float y);
    
    /**
     * @brief Конструктор с массивом координат
     * @param coords Массив из двух элементов [x, y]
     */
    Point(const float coords[2]);
    
    /**
     * @brief Получить координату X
     * @return Координата X точки
     */
    float getX() const;

    /**
     * @brief Получить координату Y
     * @return Координата Y точки
     */
    float getY() const;

    /**
     * @brief Установить координату X
     * @param x Новое значение координаты X
     */
    void setX(float x);
    
    /**
     * @brief Установить координату Y
     * @param y Новое значение координаты Y
     */
    void setY(float y);
    
    /**
     * @brief Вычислить расстояние до другой точки
     * @param other Другая точка
     * @return Расстояние между точками
     */
    float distanceTo(const Point& other) const;
    
    /**
     * @brief Повернуть точку на 90° по часовой стрелке относительно начала координат
     * 
     * Преобразование: (x, y) -> (y, -x)
     */
    void rotate90Clockwise();

    /**
     * @brief Оператор сложения точек
     * @param other Другая точка
     * @return Новая точка с суммой координат
     */
    Point operator+(const Point& other) const;
    
    /**
     * @brief Оператор вычитания точек
     * @param other Другая точка
     * @return Новая точка с разностью координат
     */
    Point operator-(const Point& other) const;
    
    /**
     * @brief Оператор деления координат на число
     * @param divisor Делитель
     * @return Новая точка с координатами, поделенными на divisor
     */
    Point operator/(float divisor) const;
    
    /**
     * @brief Оператор ввода из потока
     * @param is Входной поток
     * @param point Точка для чтения
     * @return Ссылка на поток
     */
    friend std::istream& operator>>(std::istream& is, Point& point);
    
    /**
     * @brief Оператор вывода в поток
     * @param os Выходной поток
     * @param point Точка для вывода
     * @return Ссылка на поток
     */
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};

#endif