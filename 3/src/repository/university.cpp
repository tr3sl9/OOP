#include "university.h"
#include "group.h"
#include "groupInterface.h"
#include <iostream>

std::string University::extractKey(const std::shared_ptr<Group>& group) {
    if (!group) {
        return "";
    }
    return group->getID();
}

std::function<std::string(const std::shared_ptr<Group>&)> University::createGroupKeyExtractor() {
    return extractKey;
}

University::University(size_t bucket_count) : hashTable_(bucket_count) {
}

void University::addGroup(const std::string& ID, int maxCountDisciplines, CategoryStudent type) {
    auto group = std::make_shared<Group>(ID, maxCountDisciplines, type);
    if (!hashTable_.insert(group, ID, createGroupKeyExtractor())) {
        std::cout << "Группа с ID " << ID << " уже существует." << std::endl;
    }
}

void University::removeGroup(const std::string& ID) {
    hashTable_.erase(ID, createGroupKeyExtractor());
}

size_t University::getTotalStudentCount() const {
    size_t total = 0;
    for (auto it = begin(); it != end(); ++it) {
        if (*it) {
            total += (*it)->getStudentCount();
        }
    }
    return total;
}

bool University::updateGroup(const std::string& oldID, const std::string& newID) {
    auto group = findGroup(oldID);

    if (!group) {
        std::cout << "Группа с ID " << oldID << " не найдена." << std::endl;
        return false;
    }
    
    if (findGroup(newID)) {
        std::cout << "Группа с ID " << newID << " уже существует." << std::endl;
        return false;
    }
    
    hashTable_.erase(oldID, createGroupKeyExtractor());
    
    group->setID(newID);
    
    if (!hashTable_.insert(group, newID, createGroupKeyExtractor())) {
        std::cout << "Ошибка при обновлении ID группы." << std::endl;
        return false;
    }
    
    std::cout << "ID группы изменен с " << oldID << " на " << newID << std::endl;
    return true;
}

bool University::updateGroup(const std::string& ID, int maxCountDisciplines) {
    auto group = findGroup(ID);

    if (!group) {
        std::cout << "Группа с ID " << ID << " не найдена." << std::endl;
        return false;
    }
    
    group->setMaxCountDisciplines(maxCountDisciplines);
    std::cout << "Максимальное количество дисциплин для группы " << ID 
              << " изменено на " << maxCountDisciplines << std::endl;
    return true;
}

bool University::updateGroup(const std::string& ID, CategoryStudent type) {
    auto group = findGroup(ID);

    if (!group) {
        std::cout << "Группа с ID " << ID << " не найдена." << std::endl;
        return false;
    }
    
    group->setGroupType(type);
    std::cout << "Тип группы " << ID << " изменен." << std::endl;
    return true;
}

void University::showGroup(const std::string& ID) const {
    auto group = findGroup(ID);
    if (group) {
        group->showGroup();
    } else {
        std::cout << "Группа с ID " << ID << " не найдена." << std::endl;
    }
}

void* University::getTable() const {
    return const_cast<HashTable<std::shared_ptr<Group>, std::string>*>(&hashTable_);
}

std::string University::getID() const {
    return "";
}

size_t University::getCount() const {
    return hashTable_.size();
}

std::shared_ptr<Group> University::findGroup(const std::string& ID) const {
    auto* result = const_cast<HashTable<std::shared_ptr<Group>, std::string>*>(&hashTable_)
        ->find(ID, createGroupKeyExtractor());
    return result ? *result : nullptr;
}

size_t University::getGroupCount() const noexcept {
    return hashTable_.size();
}

std::vector<std::shared_ptr<Group>> University::getAllGroups() const {
    std::vector<std::shared_ptr<Group>> groups;
    for (auto it = const_cast<University*>(this)->begin(); it != const_cast<University*>(this)->end(); ++it) {
        groups.push_back(*it);
    }
    return groups;
}

HashTable<std::shared_ptr<Group>, std::string>::iterator University::begin() {
    return hashTable_.begin();
}

HashTable<std::shared_ptr<Group>, std::string>::iterator University::end() {
    return hashTable_.end();
}

HashTable<std::shared_ptr<Group>, std::string>::const_iterator University::begin() const {
    return hashTable_.cbegin();
}

HashTable<std::shared_ptr<Group>, std::string>::const_iterator University::end() const {
    return hashTable_.cend();
}

