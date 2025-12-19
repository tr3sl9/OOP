#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "group.h"
#include "groupInterface.h"
#include "../template/hashTable.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

// Forward declaration
class Group;

/**
 * @brief Класс университета
 * 
 * Управляет таблицей групп студентов.
 * Реализует интерфейс TableProvider для работы с группами.
 */
class University : public TableProvider {
private:
    // Используем стандартный std::hash для строковых ключей
    HashTable<std::shared_ptr<Group>, std::string> hashTable_;
    
    /**
     * @brief Извлечь ключ (ID группы) из группы
     */
    static std::string extractKey(const std::shared_ptr<Group>& group);
    
    /**
     * @brief Создать функцию-экстрактор ключа для работы с хеш-таблицей
     * @return Функция, которая извлекает ключ (ID) из группы
     */
    static std::function<std::string(const std::shared_ptr<Group>&)> createGroupKeyExtractor();

public:
    /**
     * @brief Конструктор
     */
    explicit University(size_t bucket_count = 101);
    
    /**
     * @brief Деструктор
     */
    ~University() = default;
    
    /**
     * @brief Найти группу по ID
     * @param ID Индекс группы
     * @return Указатель на группу или nullptr
     */
    std::shared_ptr<Group> findGroup(const std::string& ID) const;
    
    /**
     * @brief Получить количество групп
     * @return Количество групп
     */
    size_t getGroupCount() const noexcept;
    
    /**
     * @brief Получить все группы
     * @return Вектор указателей на группы
     */
    std::vector<std::shared_ptr<Group>> getAllGroups() const;
    
    /**
     * @brief Получить итератор начала
     * @return Итератор на первый элемент
     */
    HashTable<std::shared_ptr<Group>, std::string>::iterator begin();
    
    /**
     * @brief Получить итератор конца
     * @return Итератор за последним элементом
     */
    HashTable<std::shared_ptr<Group>, std::string>::iterator end();

    /**
     * @brief Получить константный итератор начала
     * @return Константный итератор на первый элемент
     */
    HashTable<std::shared_ptr<Group>, std::string>::const_iterator begin() const;
    
    /**
     * @brief Получить константный итератор конца
     * @return Константный итератор за последним элементом
     */
    HashTable<std::shared_ptr<Group>, std::string>::const_iterator end() const;
    
    /**
     * @brief Получить общее количество студентов во всех группах
     * @return Общее количество студентов
     */
    size_t getTotalStudentCount() const;
    
    // TableProvider interface
    void addGroup(const std::string& ID, int maxCountDisciplines, CategoryStudent type) override;
    void removeGroup(const std::string& ID) override;
    void showGroup(const std::string& ID) const override;
    void* getTable() const override;
    std::string getID() const override;
    size_t getCount() const override;
    
    // Перегруженные версии updateGroup для изменения различных параметров
    /**
     * @brief Обновить ID группы
     * @param oldID Старый ID группы
     * @param newID Новый ID группы
     * @return true если обновление успешно, false если группа не найдена или новый ID уже существует
     */
    bool updateGroup(const std::string& oldID, const std::string& newID);
    
    /**
     * @brief Обновить максимальное количество дисциплин группы
     * @param ID ID группы
     * @param maxCountDisciplines Новое максимальное количество дисциплин
     * @return true если обновление успешно, false если группа не найдена
     */
    bool updateGroup(const std::string& ID, int maxCountDisciplines);
    
    /**
     * @brief Обновить тип группы
     * @param ID ID группы
     * @param type Новый тип группы
     * @return true если обновление успешно, false если группа не найдена
     */
    bool updateGroup(const std::string& ID, CategoryStudent type);
};

#endif

