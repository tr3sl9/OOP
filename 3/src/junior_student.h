#ifndef JUNIOR_STUDENT_H
#define JUNIOR_STUDENT_H

#include "student.h"

class JuniorStudent : public Student {
    public: 
        explicit JuniorStudent(const std::string fullname) : Student(fullname) {}

        CategoryStudent getStudentType() const override { return JUNIOR; }
};

#endif