#ifndef STUDENT_H
#define STUDENT_H

#include <numeric>
#include <string>
#include <vector>
#include <memory>

#include "studentInterface.h"

/**
 * @brief Базовый класс студента
 * 
 * Представляет базовую информацию о студенте: фамилию и инициалы,
 * а также список оценок.
 */
class Student : public IStudentProvider {
protected:
    std::string fullname_;
    std::vector<int> grades_;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Student();
    
    /**
     * @brief Конструктор с параметром
     * @param fullname Фамилия и инициалы студента
     */
    explicit Student(const std::string& fullname);
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Student() = default;

    /**
     * @brief Получить полное имя студента
     * @return Фамилия и инициалы
     */
    std::string getFullName() const noexcept override;
    
    /**
     * @brief Добавить оценку
     * @param g Оценка
     */
    void addGrade(int g) override;
    
    /**
     * @brief Получить список оценок
     * @return Вектор оценок
     */
    std::vector<int> getGrades() const override;
    
    /**
     * @brief Получить тип студента
     * @return Категория студента
     */
    CategoryStudent getStudentType() const noexcept override;
    
    /**
     * @brief Установить тип студента
     * @param type Категория студента
     */
    void setStudentType(CategoryStudent type) noexcept override;
    
    /**
     * @brief Вычислить средний балл
     * @return Средний балл студента
     */
    double average() const;
};

#endif