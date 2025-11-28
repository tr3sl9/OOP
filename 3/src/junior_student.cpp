#include "junior_student.h"

JuniorStudent::JuniorStudent(const std::string& fullname) : Student(fullname) {
}

CategoryStudent JuniorStudent::getStudentType() const {
    return CategoryStudent::JUNIOR;
}

