#ifndef STUDENT_H
#define STUDENT_H

#include <numeric>
#include <string>
#include <vector>

#include "studentInterface.h"

class Student :  public IGradeProvider, public IStudentProvider {
    protected:
        std::string fullname_;
        std::vector<int> grades_;
    public:
        Student(); 
        explicit Student(std::string fullname) : fullname_(std::move(fullname)) {}
        virtual ~Student() = default;

        std::string getFullName() const noexcept override { return fullname_; }
        void addGrade(int g) noexcept override { grades_.push_back(g); }
        std::vector<int> getGrades() const override { return grades_; }
        CategoryStudent getStudentType() const override { return STUDENT; }
        double average() const { 
            if (grades_.empty()) {
                return 0;
            }

            return std::accumulate(grades_.begin(), grades_.end(), 0) / static_cast<double>(grades_.size());
        }
        
};

#endif