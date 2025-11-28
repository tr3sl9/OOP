#include "senior_student.h"

SeniorStudent::SeniorStudent(const std::string& fullname) 
    : Student(fullname), ERW_(""), placeERW_(""), gradeERW_(0) {
}

CategoryStudent SeniorStudent::getStudentType() const {
    return CategoryStudent::SENIOR;
}

void SeniorStudent::setERWName(const std::string& ERW) noexcept {
    ERW_ = ERW;
}

std::string SeniorStudent::getERWName() const {
    return ERW_;
}

void SeniorStudent::setPlace(const std::string& placeERW) noexcept {
    placeERW_ = placeERW;
}

std::string SeniorStudent::getPlaceERW() const {
    return placeERW_;
}

void SeniorStudent::setERWGrade(int grade) noexcept {
    gradeERW_ = grade;
}

int SeniorStudent::getERWGrade() const noexcept {
    return gradeERW_;
}

int SeniorStudent::getGrade() const {
    return gradeERW_;
}

