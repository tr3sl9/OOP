#include "senior_student.h"

SeniorStudent::SeniorStudent(const std::string& fullname) 
    : Student(fullname), ERW_(""), placeERW_(""), gradeERW_(0) {
}

CategoryStudent SeniorStudent::getStudentType() const noexcept {
    return CategoryStudent::SENIOR;
}

void SeniorStudent::setERWName(const std::string& ERW) {
    ERW_ = ERW;
}

std::string SeniorStudent::getERWName() const noexcept {
    return ERW_;
}

void SeniorStudent::setPlace(const std::string& placeERW) {
    placeERW_ = placeERW;
}

std::string SeniorStudent::getPlaceERW() const noexcept {
    return placeERW_;
}

void SeniorStudent::setERWGrade(int grade) noexcept {
    gradeERW_ = grade;
}

int SeniorStudent::getERWGrade() const noexcept {
    return gradeERW_;
}

int SeniorStudent::getGrade() const noexcept {
    return gradeERW_;
}

