#ifndef GROUP_H
#define GROUP_H

#include "student.h"
#include "studentInterface.h"
#include "groupInterface.h"
#include "../hash_table.h"

#include <memory>
#include <string>
#include <vector>

// Forward declaration
class StudentTable;

/**
 * @brief Класс группы студентов
 * 
 * Полная информация о группе содержится в таблице группы,
 * каждый элемент которой состоит из:
 * - индекса группы
 * - максимального количества дисциплин (оценок)
 * - типа учащихся
 * - таблицы учащихся
 */
class Group : public GroupProvider {
private:
    std::string ID_;                    ///< Индекс группы
    int maxCountDisciplines_;           ///< Максимальное количество дисциплин
    CategoryStudent type_;              ///< Тип учащихся
    std::unique_ptr<StudentTable> studentTable_; ///< Таблица учащихся

public:
    /**
     * @brief Конструктор
     * @param ID Индекс группы
     * @param maxCountDisciplines Максимальное количество дисциплин
     * @param type Тип учащихся
     */
    Group(const std::string& ID, int maxCountDisciplines, CategoryStudent type);
    
    /**
     * @brief Деструктор
     */
    ~Group();

    // GroupProvider interface
    void setID(const std::string& ID) noexcept override;
    std::string getID() const noexcept override;
    void setMaxCountDisciplines(int maxCountDisciplines) noexcept override;
    int getMaxCountDisciplines() const noexcept override;
    void setGroupType(CategoryStudent type) noexcept override;
    CategoryStudent getGroupType() const noexcept override;
    void addStudent(std::shared_ptr<Student> student) override;
    void removeStudent(const std::string& fullname) override;
    void showGroup() const override ;
    StudentTable* getTable() const override;
    size_t getStudentCount() const override;
    size_t getCount() const override;
};

#endif