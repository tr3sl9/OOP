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

University::University(size_t bucket_count) : hashTable_(bucket_count) {
}

void University::addGroup(const std::string& ID, int maxCountDisciplines, CategoryStudent type) {
    auto group = std::make_shared<Group>(ID, maxCountDisciplines, type);
    hashTable_.insert(group, ID);
}

void University::removeGroup(const std::string& ID) {
    auto keyExtractor = [](const std::shared_ptr<Group>& g) -> std::string {
        return g ? g->getID() : "";
    };
    hashTable_.erase(ID, keyExtractor);
}

void University::updateGroup(const std::string& ID) {
    auto group = findGroup(ID);
    if (group) {
        //обновить группу 
    }
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
    // Для университета ID не применим, возвращаем пустую строку
    return "";
}

size_t University::getCount() const {
    return hashTable_.size();
}

std::shared_ptr<Group> University::findGroup(const std::string& ID) const {
    auto keyExtractor = [](const std::shared_ptr<Group>& g) -> std::string {
        return g ? g->getID() : "";
    };
    auto* result = const_cast<HashTable<std::shared_ptr<Group>, std::string>*>(&hashTable_)
        ->find(ID, keyExtractor);
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
