#ifndef SENIOR_STRDENT_H
#define SENIOR_STRDENT_H

#include "seniorInterface.h"
#include "student.h"

class SeniorStudent : public Student, public ERWProvider {
    private: 
        std::string ERW_;
        std::string placeERW_;
        int grade_;
    public: 
        explicit SeniorStudent(const std::string fullname) : Student(fullname) {};

        CategoryStudent getStudentType() const override { return SENIOR; }

        void setERWName(const std::string& ERW) noexcept override { ERW_ = ERW; }
        std::string getERWName() const override { return ERW_; }
        void setPlace(const std::string& placeERW) noexcept override {placeERW_ = placeERW; }
        std::string getPlaceERW() const override { return placeERW_; }
        void setGrade(int grade) { grade_ = grade; }
        int getGrade() const override { return grade_; }    
}; 

#endif