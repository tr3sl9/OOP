#ifndef STUDENT_H
#define STUDENT_H

#include <numeric>
#include <string>
#include <vector>

typedef enum categoryStudent {
    junior = 1,
    senior = 2,
    student = 3
} categoryStudent;


class Student {
    protected:
        std::string fullname_;
        std::vector<int> grades_;
    public:
        Student(); 
        explicit Student(std::string fullname) : fullname_(std::move(fullname)) {}
        Student(const Student& other) = default;
        Student(Student&& other) = default;
        Student& operator=(const Student& other) = default;
        Student& operator=(Student&& other) = default;
        virtual ~Student() = default;

        virtual std::string getFullName() const noexcept { return fullname_; }
        virtual void addGrade(int g) { grades_.push_back(g); }
        virtual std::vector<int> getGrades() const noexcept { return grades_; }
        virtual categoryStudent studentType() const noexcept { return student; }
        double average() const { 
            if (grades_.empty()) {
                return 0;
            }

            return std::accumulate(grades_.begin(), grades_.end(), 0) / static_cast<double>(grades_.size());
        }
        
};

#endif