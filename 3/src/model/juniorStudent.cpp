#include "juniorStudent.h"

JuniorStudent::JuniorStudent(const std::string& fullname) : Student(fullname) {
}

CategoryStudent JuniorStudent::getStudentType() const noexcept {
    return CategoryStudent::JUNIOR;
}

