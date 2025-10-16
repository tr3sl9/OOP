/**
 * @file dialog.h
 * @brief Заголовочный файл класса Dialog для интерактивного тестирования
 */

#ifndef DIALOG_H
#define DIALOG_H

#include "point.h"
#include "../lib/polygon.h"

/**
 * @class Dialog
 * @brief Класс для интерактивного тестирования классов Point и Polygon
 * 
 * Класс Dialog предоставляет статические методы для создания
 * интерактивных меню тестирования функциональности классов
 * геометрических объектов.
 */
class Dialog {
public:
    /**
     * @brief Запустить интерактивное тестирование класса Point
     * 
     * Создает меню с опциями для тестирования различных
     * аспектов класса Point.
     */
    static void run();
    
    /**
     * @brief Запустить интерактивное тестирование класса Polygon
     * 
     * Создает меню с опциями для тестирования различных
     * аспектов класса Polygon.
     */
    static void run_polygon();
    
private:
    /**
     * @brief Создать точку через пользовательский ввод
     * @return Созданная точка
     */
    static Point createPoint();
    
    /**
     * @brief Тестирование конструкторов класса Point
     */
    static void testConstructors();
    
    /**
     * @brief Тестирование геттеров и сеттеров класса Point
     */
    static void testGettersSetters();
    
    /**
     * @brief Тестирование вычисления расстояния между точками
     */
    static void testDistance();
    
    /**
     * @brief Тестирование арифметических операций с точками
     */
    static void testArithmetic();
    
    /**
     * @brief Тестирование поворота точки
     */
    static void testRotation();
    
    /**
     * @brief Вывод информации о точке
     * @param point Точка для вывода
     * @param name Название для отображения
     */
    static void printPointInfo(const Point& point, const std::string& name);
    
    /**
     * @brief Создать многоугольник через пользовательский ввод
     * @return Созданный многоугольник
     */
    static Polygon createPolygon();
    
    /**
     * @brief Тестирование конструкторов класса Polygon
     */
    static void testPolygonConstructors();
    
    /**
     * @brief Тестирование операторов класса Polygon
     */
    static void testPolygonOperators();
    
    /**
     * @brief Тестирование вычисления центра масс многоугольника
     */
    static void testPolygonCenterOfMass();
    
    /**
     * @brief Тестирование перемещения многоугольника
     */
    static void testPolygonMove();
    
    /**
     * @brief Тестирование поворота многоугольника
     */
    static void testPolygonRotate();
    
    /**
     * @brief Тестирование потоков ввода/вывода для многоугольника
     */
    static void testPolygonStreams();
    
    /**
     * @brief Вывод информации о многоугольнике
     * @param polygon Многоугольник для вывода
     * @param name Название для отображения
     */
    static void printPolygonInfo(const Polygon& polygon, const std::string& name);
};

#endif