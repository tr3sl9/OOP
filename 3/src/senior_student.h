#ifndef SENIOR_STUDENT_H
#define SENIOR_STUDENT_H

#include "seniorInterface.h"
#include "student.h"

/**
 * @brief Класс старшекурсника
 * 
 * Представляет студента старших курсов.
 * Описатель старшекурсника содержит:
 * - фамилию и инициалы студента
 * - количество оценок и указатель на динамический массив оценок
 * - направление темы УИР (учебно-исследовательской работы)
 * - место выполнения
 * - оценку за УИР
 */
class SeniorStudent : public Student, public ERWProvider  {
private: 
    std::string ERW_;        ///< Направление темы УИР
    std::string placeERW_;   ///< Место выполнения УИР
    int gradeERW_;           ///< Оценка за УИР

public: 
    /**
     * @brief Конструктор
     * @param fullname Фамилия и инициалы студента
     */
    explicit SeniorStudent(const std::string& fullname);

    /**
     * @brief Получить тип студента
     * @return SENIOR
     */
    CategoryStudent getStudentType() const override;

    /**
     * @brief Установить название УИР
     * @param ERW Направление темы УИР
     */
    void setERWName(const std::string& ERW) override;
    
    /**
     * @brief Получить название УИР
     * @return Направление темы УИР
     */
    std::string getERWName() const override;
    
    /**
     * @brief Установить место выполнения УИР
     * @param placeERW Место выполнения
     */
    void setPlace(const std::string& placeERW) override;
    
    /**
     * @brief Получить место выполнения УИР
     * @return Место выполнения УИР
     */
    std::string getPlaceERW() const override;
    
    /**
     * @brief Установить оценку за УИР
     * @param grade Оценка руководителя
     */
    void setERWGrade(int grade) noexcept;
    
    /**
     * @brief Получить оценку за УИР (из интерфейса ERWProvider)
     * @return Оценка за УИР
     */
    int getERWGrade() const noexcept;
    
    /**
     * @brief Получить оценку (из интерфейса IGradeProvider)
     * @return Оценка за УИР
     */
    int getGrade() const override;
}; 

#endif