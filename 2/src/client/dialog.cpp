#include "dialog.h"
#include "../lib/point.h"
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