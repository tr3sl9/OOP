#include "dialog.h"
#include "../lib/point.h"
#include "../lib/polygon.h"
#include <iostream>
#include <limits>

void Dialog::run() {
    int choice;
    
    do {
        std::cout << "\n=== ТЕСТИРОВАНИЕ КЛАССА POINT ===\n";
        std::cout << "[1] Тест конструкторов\n";
        std::cout << "[2] Тест геттеров/сеттеров\n";
        std::cout << "[3] Тест расстояния между точками\n";
        std::cout << "[4] Тест арифметических операций\n";
        std::cout << "[5] Тест поворота точки\n";
        std::cout << "[0] Выход\n";
        std::cout << "Выберите опцию: ";
        
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        switch (choice) {
            case 1: testConstructors(); break;
            case 2: testGettersSetters(); break;
            case 3: testDistance(); break;
            case 4: testArithmetic(); break;
            case 5: testRotation(); break;
            case 0: std::cout << "Завершение работы...\n"; break;
            default: std::cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return;
}

Point Dialog::createPoint() {
    Point p;
    std::cout << "Введите координаты точки (x y): ";
    std::cin >> p;
    return p;
}

void Dialog::testConstructors() {
    std::cout << "\n--- Тест конструкторов ---\n";
    
    Point p1;
    std::cout << "Конструктор по умолчанию: " << p1 << std::endl;
    
    Point p2(3.5f, 7.2f);
    std::cout << "Конструктор с параметрами (3.5, 7.2): " << p2 << std::endl;
    
    float coords[2] = {1.0f, 2.0f};
    Point p3(coords);
    std::cout << "Конструктор с массивом [1.0, 2.0]: " << p3 << std::endl;
    
    Point p4 = createPoint();
    std::cout << "Пользовательская точка: " << p4 << std::endl;

    return;
}

void Dialog::testGettersSetters() {
    std::cout << "\n--- Тест геттеров/сеттеров ---\n";
    
    Point p = createPoint();
    printPointInfo(p, "Исходная точка");
    
    float newX, newY;
    std::cout << "Введите новое значение X: ";
    std::cin >> newX;
    p.setX(newX);
    
    std::cout << "Введите новое значение Y: ";
    std::cin >> newY;
    p.setY(newY);
    
    printPointInfo(p, "Точка после изменения");

    return;
}

void Dialog::testDistance() {
    std::cout << "\n--- Тест расстояния между точками ---\n";
    
    std::cout << "Первая точка:\n";
    Point p1 = createPoint();
    
    std::cout << "Вторая точка:\n";
    Point p2 = createPoint();
    
    float distance = p1.distanceTo(p2);
    std::cout << "Расстояние между " << p1 << " и " << p2 << " = " << distance << std::endl;

    return;
}

void Dialog::testArithmetic() {
    std::cout << "\n--- Тест арифметических операций ---\n";
    
    std::cout << "Первая точка:\n";
    Point p1 = createPoint();
    
    std::cout << "Вторая точка:\n";
    Point p2 = createPoint();
    
    Point sum = p1 + p2;
    std::cout << p1 << " + " << p2 << " = " << sum << std::endl;
    
    Point diff = p1 - p2;
    std::cout << p1 << " - " << p2 << " = " << diff << std::endl;
    
    float divisor;
    std::cout << "Введите делитель: ";
    std::cin >> divisor;
    
    if (divisor != 0) {
        Point div = p1 / divisor;
        std::cout << p1 << " / " << divisor << " = " << div << std::endl;
    } else {
        std::cout << "Ошибка: деление на ноль!\n";
    }

    return;
}

void Dialog::testRotation() {
    std::cout << "\n--- Тест поворота точки ---\n";
    
    Point p = createPoint();
    printPointInfo(p, "Исходная точка");
    
    Point rotated = p;
    rotated.rotate90Clockwise();
    std::cout << "Точка после поворота на 90° по часовой: " << rotated << std::endl;

    return;
}

void Dialog::printPointInfo(const Point& point, const std::string& name) {
    std::cout << name << ":\n";
    std::cout << "  Координаты: (" << point.getX() << ", " << point.getY() << ")\n";
    std::cout << "  Строковое представление: " << point << std::endl;

    return;
}

void Dialog::run_polygon() {
    int choice;
    
    do {
        std::cout << "\n=== ТЕСТИРОВАНИЕ КЛАССА POLYGON ===\n";
        std::cout << "[1] Тест конструкторов\n";
        std::cout << "[2] Тест операторов\n";
        std::cout << "[3] Тест центра масс\n";
        std::cout << "[4] Тест перемещения\n";
        std::cout << "[5] Тест поворота\n";
        std::cout << "[6] Тест потоков ввода/вывода\n";
        std::cout << "[0] Выход\n";
        std::cout << "Выберите опцию: ";
        
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        switch (choice) {
            case 1: testPolygonConstructors(); break;
            case 2: testPolygonOperators(); break;
            case 3: testPolygonCenterOfMass(); break;
            case 4: testPolygonMove(); break;
            case 5: testPolygonRotate(); break;
            case 6: testPolygonStreams(); break;
            case 0: std::cout << "Завершение работы...\n"; break;
            default: std::cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return;
}

Polygon Dialog::createPolygon() {
    std::cout << "Введите количество вершин: ";
    size_t count;
    std::cin >> count;
    
    if (count == 0) {
        return Polygon();
    } else if (count == 1) {
        std::cout << "Введите координаты единственной точки (x y): ";
        Point p;
        std::cin >> p;
        return Polygon(p);
    } else {
        Point* points = new Point[count];
        std::cout << "Введите координаты точек (x y для каждой):\n";
        for (size_t i = 0; i < count; ++i) {
            std::cout << "Точка " << (i + 1) << ": ";
            std::cin >> points[i];
        }
        Polygon result(count, points);
        delete[] points;
        return result;
    }
}

void Dialog::testPolygonConstructors() {
    std::cout << "\n--- Тест конструкторов Polygon ---\n";
    
    Polygon p1;
    std::cout << "Конструктор по умолчанию: " << p1 << std::endl;
    
    Point vertex(1.0f, 2.0f);
    Polygon p2(vertex);
    std::cout << "Конструктор с одной точкой (1.0, 2.0): " << p2 << std::endl;
    
    Polygon p3(3);
    std::cout << "Конструктор с 3 вершинами: " << p3 << std::endl;
    
    Point points[3] = {Point(0.0f, 0.0f), Point(2.0f, 0.0f), Point(2.0f, 2.0f)};
    Polygon p4(3, points);
    std::cout << "Конструктор с массивом точек (треугольник): " << p4 << std::endl;
    
    std::cout << "\nСоздайте свой многоугольник:\n";
    Polygon p5 = createPolygon();
    std::cout << "Ваш многоугольник: " << p5 << std::endl;

    return;
}

void Dialog::testPolygonOperators() {
    std::cout << "\n--- Тест операторов Polygon ---\n";
    
    std::cout << "Создайте базовый многоугольник:\n";
    Polygon poly = createPolygon();
    printPolygonInfo(poly, "Исходный многоугольник");
    
    std::cout << "\nДобавим новую вершину:\n";
    Point newVertex = createPoint();
    poly += newVertex;
    std::cout << "Многоугольник после добавления вершины " << newVertex << ":\n";
    printPolygonInfo(poly, "Обновленный многоугольник");
    
    if (poly.getCount() > 0) {
        std::cout << "\nТест доступа к вершинам:\n";
        std::cout << "Первая вершина [0]: " << poly[0] << std::endl;
        if (poly.getCount() > 1) {
            std::cout << "Последняя вершина [" << (poly.getCount() - 1) << "]: " 
                      << poly[poly.getCount() - 1] << std::endl;
        }
        
        std::cout << "\nИзменим первую вершину:\n";
        Point newFirstVertex = createPoint();
        poly[0] = newFirstVertex;
        std::cout << "Первая вершина после изменения: " << poly[0] << std::endl;
    }
    
    std::cout << "\nТест копирования:\n";
    Polygon copy = poly;
    std::cout << "Копия: " << copy << std::endl;
    
    if (copy.getCount() > 0) {
        copy[0] = Point(999.0f, 999.0f);
        std::cout << "Копия после изменения первой вершины: " << copy << std::endl;
        std::cout << "Оригинал (должен остаться неизменным): " << poly << std::endl;
    }

    return;
}

void Dialog::testPolygonCenterOfMass() {
    std::cout << "\n--- Тест центра масс Polygon ---\n";
    
    std::cout << "Создайте многоугольник для расчета центра масс:\n";
    Polygon poly = createPolygon();
    printPolygonInfo(poly, "Многоугольник");
    
    if (poly.getCount() > 0) {
        Point center = poly.centerOfMass();
        std::cout << "\nЦентр масс многоугольника: " << center << std::endl;
        
        std::cout << "\nВершины многоугольника:\n";
        for (size_t i = 0; i < poly.getCount(); ++i) {
            std::cout << "  Вершина " << (i + 1) << ": " << poly[i] << std::endl;
        }
        
        if (poly.getCount() > 1) {
            float sumX = 0, sumY = 0;
            for (size_t i = 0; i < poly.getCount(); ++i) {
                sumX += poly[i].getX();
                sumY += poly[i].getY();
            }
            Point manualCenter(sumX / poly.getCount(), sumY / poly.getCount());
            std::cout << "Центр масс (вычисленный вручную): " << manualCenter << std::endl;
        }
    } else {
        std::cout << "Многоугольник пустой, центр масс не определен.\n";
    }

    return;
}

void Dialog::testPolygonMove() {
    std::cout << "\n--- Тест перемещения Polygon ---\n";
    
    std::cout << "Создайте многоугольник для перемещения:\n";
    Polygon poly = createPolygon();
    printPolygonInfo(poly, "Исходный многоугольник");
    
    if (poly.getCount() > 0) {
        std::cout << "\nВведите вектор перемещения (dx dy): ";
        Point moveVector = createPoint();
        
        std::cout << "Перемещаем многоугольник на вектор " << moveVector << std::endl;
        poly.move(moveVector);
        printPolygonInfo(poly, "Многоугольник после перемещения");
        
        std::cout << "\nДетали перемещения:\n";
        std::cout << "Вектор перемещения: " << moveVector << std::endl;
    } else {
        std::cout << "Многоугольник пустой, перемещение невозможно.\n";
    }

    return;
}

void Dialog::testPolygonRotate() {
    std::cout << "\n--- Тест поворота Polygon ---\n";
    
    std::cout << "Создайте многоугольник для поворота:\n";
    Polygon poly = createPolygon();
    printPolygonInfo(poly, "Исходный многоугольник");
    
    if (poly.getCount() > 0) {
        std::cout << "\nВведите центр поворота (x y): ";
        Point center = createPoint();
        
        std::cout << "Введите угол поворота (кратный 90°): ";
        size_t angle;
        std::cin >> angle;
        
        try {
            std::cout << "Поворачиваем многоугольник на " << angle << "° вокруг точки " << center << std::endl;
            poly.rotate(center, angle);
            printPolygonInfo(poly, "Многоугольник после поворота");
            
            std::cout << "\nПоворот на 90° еще раз:\n";
            poly.rotate(center, 90);
            printPolygonInfo(poly, "После дополнительного поворота на 90°");
            
        } catch (const std::invalid_argument& e) {
            std::cout << "Ошибка поворота: " << e.what() << std::endl;
            std::cout << "Угол должен быть кратен 90°.\n";
        }
    } else {
        std::cout << "Многоугольник пустой, поворот невозможен.\n";
    }

    return;
}

void Dialog::testPolygonStreams() {
    std::cout << "\n--- Тест потоков ввода/вывода Polygon ---\n";
    
    std::cout << "Создайте многоугольник для тестирования потоков:\n";
    Polygon poly = createPolygon();
    std::cout << "Вывод многоугольника в поток: " << poly << std::endl;
    
    std::cout << "\nТест ввода многоугольника из потока.\n";
    std::cout << "Формат: количество_вершин x1 y1 x2 y2 ...\n";
    std::cout << "Пример: 3 0 0 1 0 1 1 (треугольник)\n";
    std::cout << "Введите многоугольник: ";
    
    Polygon inputPoly;
    std::cin >> inputPoly;
    
    if (!std::cin.fail()) {
        std::cout << "Успешно считан многоугольник: " << inputPoly << std::endl;
        printPolygonInfo(inputPoly, "Многоугольник из потока");
    } else {
        std::cout << "Ошибка при чтении многоугольника из потока!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return;
}

void Dialog::printPolygonInfo(const Polygon& polygon, const std::string& name) {
    std::cout << name << ":\n";
    std::cout << "  Количество вершин: " << polygon.getCount() << std::endl;
    
    if (polygon.getCount() > 0) {
        std::cout << "  Вершины:\n";
        for (size_t i = 0; i < polygon.getCount(); ++i) {
            std::cout << "    [" << i << "] " << polygon[i] << std::endl;
        }
        
        Point center = polygon.centerOfMass();
        std::cout << "  Центр масс: " << center << std::endl;
    } else {
        std::cout << "  Многоугольник пустой\n";
    }
    
    std::cout << "  Строковое представление: " << polygon << std::endl;

    return;
}