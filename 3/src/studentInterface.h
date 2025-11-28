#ifndef STUDENT_INTERFACE_H
#define STUDENT_INTERFACE_H

#include <numeric>
#include <string>
#include <vector>

typedef enum CategoryStudent {
    JUNIOR = 1,
    SENIOR = 2,
    STUDENT = 3
} CategoryStudent;

class IGradeProvider {
    public:
        virtual ~IGradeProvider() = default;

        virtual int getGrade() const = 0;
};

class IStudentProvider {
    public: 
        virtual ~IStudentProvider() = default;

        virtual std::string getFullName() const = 0;
        virtual void addGrade(int g) noexcept = 0;
        virtual std::vector<int> getGrades() const = 0;
        virtual CategoryStudent getStudentType() const = 0;
        virtual void setStudentType(CategoryStudent type) noexcept = 0;
};

#endif