#ifndef STUDENT_TABLE_H
#define STUDENT_TABLE_H

#include "../model/student.h"
#include "../template/hashTable.h"

#include <memory>
#include <string>
#include <vector>

/**
 * @brief Класс таблицы студентов
 * 
 * Таблица учащихся, каждый элемент которой — указатель на описатель учащегося.
 * Элементы таблицы упорядочены по фамилиям в алфавитном порядке.
 */
class StudentTable {
private:
    // Используем стандартный std::hash для строковых ключей
    HashTable<std::shared_ptr<Student>, std::string> table_;
    
    /**
     * @brief Извлечь ключ (фамилию) из студента
     */
    static std::string extractKey(const std::shared_ptr<Student>& student);
    
    /**
     * @brief Сортировать студентов по фамилиям
     */
    std::vector<std::shared_ptr<Student>> getSortedStudents() const;

public:
    /**
     * @brief Конструктор
     */
    explicit StudentTable(size_t bucket_count = 101);
    
    /**
     * @brief Деструктор
     */
    ~StudentTable() = default;
    
    /**
     * @brief Добавить студента в таблицу (с сохранением упорядоченности)
     * @param student Указатель на студента
     */
    void addStudent(std::shared_ptr<Student> student);
    
    /**
     * @brief Удалить студента из таблицы
     * @param fullname Фамилия и инициалы студента
     */
    void removeStudent(const std::string& fullname);
    
    /**
     * @brief Найти студента по имени
     * @param fullname Фамилия и инициалы студента
     * @return Указатель на студента или nullptr
     */
    std::shared_ptr<Student> findStudent(const std::string& fullname) const;
    
    /**
     * @brief Получить количество студентов
     * @return Количество студентов в таблице
     */
    size_t size() const noexcept;
    
    /**
     * @brief Проверить, пуста ли таблица
     * @return true, если таблица пуста
     */
    bool empty() const noexcept;
    
    /**
     * @brief Очистить таблицу
     */
    void clear();
    
    /**
     * @brief Получить итератор начала
     * @return Итератор на первый элемент
     */
    HashTable<std::shared_ptr<Student>, std::string>::iterator begin();
    
    /**
     * @brief Получить итератор конца
     * @return Итератор за последним элементом
     */
    HashTable<std::shared_ptr<Student>, std::string>::iterator end();
    
    /**
     * @brief Получить константный итератор начала
     * @return Константный итератор на первый элемент
     */
    HashTable<std::shared_ptr<Student>, std::string>::const_iterator begin() const;
    
    /**
     * @brief Получить константный итератор конца
     * @return Константный итератор за последним элементом
     */
    HashTable<std::shared_ptr<Student>, std::string>::const_iterator end() const;
    
    /**
     * @brief Получить всех студентов в отсортированном порядке
     * @return Вектор указателей на студентов
     */
    std::vector<std::shared_ptr<Student>> getAllStudents() const;
    
    /**
     * @brief Получить всех студентов без сортировки (быстрый метод для итерации)
     * @return Вектор указателей на студентов
     */
    std::vector<std::shared_ptr<Student>> getAllElements() const;
};

#endif

