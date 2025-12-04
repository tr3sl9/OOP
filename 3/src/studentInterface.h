#ifndef STUDENT_INTERFACE_H
#define STUDENT_INTERFACE_H

#include <string>
#include <vector>

/**
 * @brief Категория студента
 */
enum class CategoryStudent {
    JUNIOR = 1,  ///< Младшекурсник
    SENIOR = 2,  ///< Старшекурсник
    STUDENT = 3  ///< Обычный студент
};

/**
 * @brief Интерфейс для работы со студентом
 */
class IStudentProvider {
public: 
    virtual ~IStudentProvider() = default;

    /**
     * @brief Получить полное имя студента
     * @return Фамилия и инициалы
     */
    virtual std::string getFullName() const noexcept = 0;
    
    /**
     * @brief Добавить оценку
     * @param g Оценка
     */
    virtual void addGrade(int g) = 0;
    
    /**
     * @brief Получить список оценок
     * @return Вектор оценок
     */
    virtual std::vector<int> getGrades() const = 0;
    
    /**
     * @brief Получить тип студента
     * @return Категория студента
     */
    virtual CategoryStudent getStudentType() const noexcept = 0;
    
    /**
     * @brief Установить тип студента
     * @param type Категория студента
     */
    virtual void setStudentType(CategoryStudent type) noexcept = 0;
};

#endif