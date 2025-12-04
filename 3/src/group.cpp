#include "group.h"
#include "student_table.h"
#include <iostream>
#include <memory>

Group::Group(const std::string& ID, int maxCountDisciplines, CategoryStudent type)
    : ID_(ID), maxCountDisciplines_(maxCountDisciplines), type_(type),
      studentTable_(std::make_unique<StudentTable>(101)) {
}

Group::~Group() = default;

void Group::setID(const std::string& ID) noexcept {
    ID_ = ID;
}

std::string Group::getID() const noexcept {
    return ID_;
}

void Group::setMaxCountDisciplines(int maxCountDisciplines) noexcept {
    maxCountDisciplines_ = maxCountDisciplines;
}

int Group::getMaxCountDisciplines() const noexcept {
    return maxCountDisciplines_;
}

void Group::setGroupType(CategoryStudent type) noexcept {
    type_ = type;
}

CategoryStudent Group::getGroupType() const noexcept {
    return type_;
}

void Group::addStudent(std::shared_ptr<Student> student) {
    if (!student) {
        return;
    }
    studentTable_->addStudent(student);
}

void Group::removeStudent(const std::string& fullname) {
    studentTable_->removeStudent(fullname);
}

void Group::showGroup() const {
    std::cout << "Группа: " << ID_ << std::endl;
    std::cout << "Тип: ";
    switch (type_) {
        case CategoryStudent::JUNIOR:
            std::cout << "Младшекурсники";
            break;
        case CategoryStudent::SENIOR:
            std::cout << "Старшекурсники";
            break;
        default:
            std::cout << "Студенты";
            break;
    }
    std::cout << std::endl;
    std::cout << "Максимум дисциплин: " << maxCountDisciplines_ << std::endl;
    std::cout << "Студенты:" << std::endl;
    
    auto students = studentTable_->getAllStudents();
    for (const auto& student : students) {
        if (student) {
            std::cout << "  - " << student->getFullName() << std::endl;
        }
    }
}

StudentTable* Group::getTable() const {
    return studentTable_.get();
}

size_t Group::getStudentCount() const {
    return studentTable_->size();
}

size_t Group::getCount() const {
    return studentTable_->size();
}

