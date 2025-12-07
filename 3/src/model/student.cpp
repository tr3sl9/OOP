#include "student.h"
#include <algorithm>
#include <numeric>

Student::Student() : fullname_(""), grades_() {
}

Student::Student(const std::string& fullname) : fullname_(fullname), grades_() {
}

std::string Student::getFullName() const noexcept {
    return fullname_;
}

void Student::addGrade(int g) {
    grades_.push_back(g);
}

std::vector<int> Student::getGrades() const {
    return grades_;
}

CategoryStudent Student::getStudentType() const noexcept {
    return CategoryStudent::STUDENT;
}

void Student::setStudentType(CategoryStudent type) noexcept {
    (void)type;
}

double Student::average() const {
    if (grades_.empty()) {
        return 0.0;
    }
    return std::accumulate(grades_.begin(), grades_.end(), 0.0) / static_cast<double>(grades_.size());
}

