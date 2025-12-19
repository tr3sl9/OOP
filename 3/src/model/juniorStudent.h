#ifndef JUNIOR_STUDENT_H
#define JUNIOR_STUDENT_H

#include "student.h"

/**
 * @brief Класс младшекурсника
 * 
 * Представляет студента младших курсов.
 * Описатель младшекурсника содержит:
 * - фамилию и инициалы студента
 * - количество оценок
 * - указатель на динамический массив оценок
 */
class JuniorStudent : public Student {
public: 
    /**
     * @brief Конструктор
     * @param fullname Фамилия и инициалы студента
     */
    explicit JuniorStudent(const std::string& fullname);
    
    /**
     * @brief Получить тип студента
     * @return JUNIOR
     */
    CategoryStudent getStudentType() const noexcept override;
};

#endif

