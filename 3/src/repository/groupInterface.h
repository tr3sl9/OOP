#ifndef GROUP_INTERFACE_H
#define GROUP_INTERFACE_H

#include "../model/studentInterface.h"
#include <string>
#include <memory>

// Forward declaration
class Student;
class StudentTable;

/**
 * @brief Интерфейс для работы с группой
 */
class GroupProvider {
public:
    virtual ~GroupProvider() = default;
    
    /**
     * @brief Установить максимальное количество дисциплин
     * @param maxCountDisciplines Максимальное количество дисциплин
     */
    virtual void setMaxCountDisciplines(int maxCountDisciplines) noexcept = 0;
    
    /**
     * @brief Получить максимальное количество дисциплин
     * @return Максимальное количество дисциплин
     */
    virtual int getMaxCountDisciplines() const noexcept = 0;
    
    /**
     * @brief Установить тип группы
     * @param type Тип учащихся
     */
    virtual void setGroupType(CategoryStudent type) noexcept = 0;
    
    /**
     * @brief Получить тип группы
     * @return Тип учащихся
     */
    virtual CategoryStudent getGroupType() const noexcept = 0;
    
    /**
     * @brief Установить индекс группы
     * @param ID Индекс группы
     */
    virtual void setID(const std::string& ID) = 0;
    
    /**
     * @brief Получить индекс группы
     * @return Индекс группы
     */
    virtual std::string getID() const noexcept = 0;


    /**
    * @brief Добавить ученика в группу
    * @param sudent указатель на студента
    */
    virtual void addStudent(std::shared_ptr<Student> student) = 0;

    /**
     * @brief Удалить студента из группы
     * @param fullname ФИО студента
     */
    virtual void removeStudent(const std::string& fullname) = 0;

    /**
     * @brief Показать информацию о группе
     */
    virtual void showGroup() const = 0;

    /**
     * @brief Получить таблицу студентов
     * @return Указатель на таблицу студентов
     */
    virtual StudentTable* getTable() const = 0;

    /**
     * @brief Получить количество студентов в группе
     * @return Количество студентов
     */
    virtual size_t getStudentCount() const = 0;

    /**
     * @brief Получить количество студентов (для совместимости)
     * @return Количество студентов
     */
    virtual size_t getCount() const = 0;

};

/**
 * @brief Интерфейс для работы с таблицей групп
 */
class TableProvider {
public:
    virtual ~TableProvider() = default;
    
    /**
     * @brief Добавить группу
     * @param ID Индекс группы
     * @param maxCountDisciplines Максимальное количество дисциплин
     * @param type Тип учащихся
     */
    virtual void addGroup(const std::string& ID, int maxCountDisciplines, CategoryStudent type) = 0;
    
    /**
     * @brief Удалить группу
     * @param ID Индекс группы
     */
    virtual void removeGroup(const std::string& ID) = 0;
    
    /**
     * @brief Показать группу
     * @param ID Индекс группы
     */
    virtual void showGroup(const std::string& ID) const = 0;
    
    /**
     * @brief Получить таблицу групп
     * @return Указатель на таблицу групп
     */
    virtual void* getTable() const = 0;
    
    /**
     * @brief Получить ID группы
     * @return Индекс группы
     */
    virtual std::string getID() const = 0;
    
    /**
     * @brief Получить количество групп
     * @return Количество групп
     */
    virtual size_t getCount() const = 0;
};

#endif

