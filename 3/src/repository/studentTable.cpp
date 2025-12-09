#include "studentTable.h"
#include <algorithm>
#include <iostream>

std::string StudentTable::extractKey(const std::shared_ptr<Student>& student) {
    if (!student) {
        return "";
    }
    return student->getFullName();
}

StudentTable::StudentTable(size_t bucket_count) : table_(bucket_count) {}

void StudentTable::addStudent(std::shared_ptr<Student> student) {
    if (!student) {
        return;
    }
    std::string key = student->getFullName();
    auto keyExtractor = [](const std::shared_ptr<Student>& s) -> std::string {
        return s ? s->getFullName() : "";
    };
    if (!table_.insert(student, key, keyExtractor)) {
        std::cout << "Студент \"" << key << "\" уже существует. Добавление пропущено.\n";
    }
}

void StudentTable::removeStudent(const std::string& fullname) {
    auto keyExtractor = [](const std::shared_ptr<Student>& s) -> std::string {
        return s ? s->getFullName() : "";
    };
    table_.erase(fullname, keyExtractor);
}

std::shared_ptr<Student> StudentTable::findStudent(const std::string& fullname) const {
    auto keyExtractor = [](const std::shared_ptr<Student>& s) -> std::string {
        return s ? s->getFullName() : "";
    };
    auto* result = const_cast<HashTable<std::shared_ptr<Student>, std::string>*>(&table_)->find(fullname, keyExtractor);
    return result ? *result : nullptr;
}

size_t StudentTable::size() const noexcept {
    return table_.size();
}

bool StudentTable::empty() const noexcept {
    return table_.empty();
}

void StudentTable::clear() {
    table_.clear();
}

HashTable<std::shared_ptr<Student>, std::string>::iterator StudentTable::begin() {
    return table_.begin();
}

HashTable<std::shared_ptr<Student>, std::string>::iterator StudentTable::end() {
    return table_.end();
}

HashTable<std::shared_ptr<Student>, std::string>::const_iterator StudentTable::begin() const {
    return table_.cbegin();
}

HashTable<std::shared_ptr<Student>, std::string>::const_iterator StudentTable::end() const {
    return table_.cend();
}

std::vector<std::shared_ptr<Student>> StudentTable::getSortedStudents() const {
    std::vector<std::shared_ptr<Student>> students;
    for (auto it = begin(); it != end(); ++it) {
        students.push_back(*it);
    }
    std::sort(students.begin(), students.end(), [](const std::shared_ptr<Student>& a, const std::shared_ptr<Student>& b) {
            if (!a || !b) return false;
            return a->getFullName() < b->getFullName();
        });
    return students;
}

std::vector<std::shared_ptr<Student>> StudentTable::getAllStudents() const {
    return getSortedStudents();
}

