#include "highLevelController.h"
#include "../repository/university.h"
#include "../repository/group.h"
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../view/tableView.h"
#include "../repository/studentTable.h"
#include <algorithm>
#include <vector>

HighLevelController::HighLevelController(University* university, ITableView* view)
    : university_(university), view_(view) {}

int HighLevelController::countFailures(const Student* student) const {
    if (!student) {
        return 0;
    }

    auto grades = student->getGrades();

    return std::count(grades.begin(), grades.end(), 2);
}

void HighLevelController::applyStudentAdmission(const std::string& groupID, const std::string& fullname, int gradeCount) {
    (void)gradeCount;
    if (!university_) {
        return;
    }

    auto group = university_->findGroup(groupID);
    if (!group) {
        if (view_) {
            view_->printError("Группа " + groupID + " не найдена");
        }
        return;
    }
    
    std::shared_ptr<Student> student;
    if (group->getGroupType() == CategoryStudent::JUNIOR) {
        student = std::make_shared<JuniorStudent>(fullname);
    } else if (group->getGroupType() == CategoryStudent::SENIOR) {
        student = std::make_shared<SeniorStudent>(fullname);
    } else {
        student = std::make_shared<Student>(fullname);
    }
    
    group->addStudent(student);
    
    if (view_) {
        view_->printMessage("Студент " + fullname + " зачислен в группу " + groupID);
    }
}

void HighLevelController::transitionStudentCourse(const std::string& groupID, const std::string& fullname, int newGradeCount) {
    (void)newGradeCount;
    if (!university_) {
        return;
    }

    auto group = university_->findGroup(groupID);
    if (!group) {
        if (view_) {
            view_->printError("Группа " + groupID + " не найдена");
        }
        return;
    }
    
    auto table = group->getTable();
    if (!table) {
        if (view_) {
            view_->printError("Таблица студентов группы " + groupID + " не найдена");
        }
        return;
    }
    
    auto student = table->findStudent(fullname);
    if (!student) {
        if (view_) {
            view_->printError("Студент " + fullname + " не найден в группе " + groupID);
        }
        return;
    }
    
    if (view_) {
        view_->printMessage("Студент " + fullname + " переведен на новый семестр в группе " + groupID);
    }
}

void HighLevelController::semesterControl(const std::string& groupID) {
    if (!university_) {
        return;
    }

    auto group = university_->findGroup(groupID);

    if (!group) {
        if (view_) {
            view_->printError("Группа " + groupID + " не найдена");
        }
        return;
    }
    
    if (view_) {
        view_->printMessage("\n=== Ведомость семестрового контроля ===");
        view_->printMessage("Группа: " + groupID);
        view_->printMessage("Дата: " + std::string(__DATE__) + " " + std::string(__TIME__));
        view_->printMessage("\nСписок студентов:");
    }
    
    auto table = group->getTable();

    if (table) {
        auto students = table->getAllStudents();
        for (const auto& student : students) {
            if (student && view_) {
                view_->printStudent(student.get());
            }
        }
    }
}

double HighLevelController::averageGroupGrade(const std::string& groupID) {
    if (!university_) {
        return 0.0;
    }

    auto group = university_->findGroup(groupID);

    if (!group) {
        if (view_) {
            view_->printError("Группа " + groupID + " не найдена");
        }
        return 0.0;
    }
    
    auto table = group->getTable();
    if (!table || table->empty()) {
        return 0.0;
    }
    
    auto students = table->getAllStudents();
    if (students.empty()) {
        return 0.0;
    }
    
    double total = 0.0;
    int count = 0;
    for (const auto& student : students) {
        if (student) {
            auto grades = student->getGrades();
            if (!grades.empty()) {
                double avg = student->average();
                total += avg;
                count++;
            }
        }
    }
    
    double result = (count > 0) ? (total / count) : 0.0;
    
    if (view_) {
        view_->printMessage("Средний балл группы " + groupID + ": " + std::to_string(result));
    }
    
    return result;
}

std::vector<std::shared_ptr<Student>> HighLevelController::laggingStudents(const std::string& groupID) {
    std::vector<std::shared_ptr<Student>> lagging;
    
    if (!university_) {
        return lagging;
    }
    
    std::vector<std::shared_ptr<Group>> groups;
    if (groupID.empty()) {
        groups = university_->getAllGroups();
    } else {
        auto group = university_->findGroup(groupID);
        if (group) {
            groups.push_back(group);
        }
    }
    
    for (const auto& group : groups) {
        if (!group) {
            continue;
        }

        auto table = group->getTable();
        if (!table) {
            continue;
        }
        
        auto students = table->getAllStudents();
        for (const auto& student : students) {
            if (!student) continue;
            auto grades = student->getGrades();
            int failures = std::count(grades.begin(), grades.end(), 2);
            if (failures >= 3) {
                lagging.push_back(student);
            }
        }
    }
    
    if (view_) {
        view_->printMessage("Найдено отстающих студентов: " + std::to_string(lagging.size()));
        for (const auto& student : lagging) {
            if (student) {
                view_->printStudent(student.get());
            }
        }
    }
    
    return lagging;
}

