#ifndef SENIOR_STRDENT_H
#define SENIOR_STRDENT_H

#include "student.h" 
#include <string>

class SeniorStudent : public Student {
    private: 
        std::string ERW_;
        std::string placeERW_;
        int grade_;
    public: 
        explicit SeniorStudent(const std::string fullname) : Student(fullname) {};

        categoryStudent studentType() const noexcept override { return senior; }

        void setERW(const std::string& ERW) { ERW_ = ERW; }
        std::string getERW() const noexcept { return ERW_; }
        void setPlace(const std::string& placeERW) {placeERW_ = placeERW; }
        std::string getPlaceERW() const noexcept { return placeERW_; }
        void setGrade(int grade) { grade_ = grade; }
        int getGrade() const noexcept { return grade_; }    
}; 

#endif