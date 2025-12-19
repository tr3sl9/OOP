#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <string>

// Forward declaration
class Student;
class Group;

/**
 * @brief Интерфейс для отображения таблиц
 */
class ITableView {
public:
    virtual ~ITableView() = default;
    
    /**
     * @brief Вывести состояние системы
     * @param groupCount Количество групп
     * @param totalStudentCount Общее количество студентов во всех группах
     */
    virtual void printState(size_t groupCount, size_t totalStudentCount) const = 0;

    /// Вывести информацию о группе
    virtual void printGroup(const Group* group) const = 0;
    /// Вывести информацию о студенте
    virtual void printStudent(const Student* student) const = 0;
    /// Вывести сообщение
    virtual void printMessage(const std::string& message) const = 0;
    /// Вывести ошибку
    virtual void printError(const std::string& error) const = 0;
};

/**
 * @brief Реализация диалогового представления таблицы
 */
class TableDialogView : public ITableView {
public:
    /**
     * @brief Конструктор
     */
    TableDialogView();
    
    /**
     * @brief Деструктор
     */
    ~TableDialogView() override = default;
    
    /**
     * @brief Вывести состояние системы
     * @param groupCount Количество групп
     * @param totalStudentCount Общее количество студентов во всех группах
     */
    void printState(size_t groupCount, size_t totalStudentCount) const override;
    
    /**
     * @brief Вывести информацию о группе
     * @param group Указатель на группу
     */
    void printGroup(const Group* group) const override;
    
    /**
     * @brief Вывести информацию о студенте
     * @param student Указатель на студента
     */
    void printStudent(const Student* student) const override;
    
    /**
     * @brief Вывести сообщение
     * @param message Сообщение
     */
    void printMessage(const std::string& message) const override;
    
    /**
     * @brief Вывести ошибку
     * @param error Сообщение об ошибке
     */
    void printError(const std::string& error) const override;
};

#endif

