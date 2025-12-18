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
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <atomic>

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

std::vector<std::shared_ptr<Student>> HighLevelController::laggingStudentsMultithreaded(const std::string& groupID) {
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
    
    if (groups.empty()) {
        return lagging;
    }
    
    std::mutex resultMutex;
    std::atomic<size_t> nextGroupIndex(0);
    const size_t totalGroups = groups.size();
    
    constexpr size_t MAX_THREADS = 10;
    const size_t numThreads = std::min(MAX_THREADS, totalGroups);
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([&groups, &lagging, &resultMutex, &nextGroupIndex, totalGroups]() {
            while (true) {
                size_t currentIndex = nextGroupIndex.fetch_add(1, std::memory_order_relaxed);
                
                if (currentIndex >= totalGroups) {
                    break;
                }
                
                const auto& group = groups[currentIndex];
                if (!group) {
                    continue;
                }
                
                auto table = group->getTable();
                if (!table) {
                    continue;
                }
                
                std::vector<std::shared_ptr<Student>> localLagging;
                
                auto students = table->getAllStudents();
                for (const auto& student : students) {
                    if (!student) continue;
                    auto grades = student->getGrades();
                    int failures = std::count(grades.begin(), grades.end(), 2);
                    if (failures >= 3) {
                        localLagging.push_back(student);
                    }
                }
                
                if (!localLagging.empty()) {
                    std::lock_guard<std::mutex> lock(resultMutex);
                    lagging.insert(lagging.end(), localLagging.begin(), localLagging.end());
                }
            }
        });
    }
    
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    
    if (view_) {
        view_->printMessage("Найдено отстающих студентов (многопоточно): " + std::to_string(lagging.size()));
        for (const auto& student : lagging) {
            if (student) {
                view_->printStudent(student.get());
            }
        }
    }
    
    return lagging;
}

std::vector<std::pair<std::string, double>> HighLevelController::averageAllGroupsMultithreaded() {
    std::vector<std::pair<std::string, double>> results;
    
    if (!university_) {
        return results;
    }
    
    auto groups = university_->getAllGroups();
    if (groups.empty()) {
        return results;
    }
    
    std::mutex resultMutex;
    std::atomic<size_t> nextGroupIndex(0);
    const size_t totalGroups = groups.size();
    
    constexpr size_t MAX_THREADS = 10;
    const size_t numThreads = std::min(MAX_THREADS, totalGroups);
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([&groups, &results, &resultMutex, &nextGroupIndex, totalGroups]() {
            while (true) {
                size_t currentIndex = nextGroupIndex.fetch_add(1, std::memory_order_relaxed);
                
                if (currentIndex >= totalGroups) {
                    break;
                }
                
                const auto& group = groups[currentIndex];
                if (!group) {
                    continue;
                }
                
                auto table = group->getTable();
                if (!table || table->empty()) {
                    continue;
                }
                
                auto students = table->getAllStudents();
                if (students.empty()) {
                    continue;
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
                
                if (count > 0) {
                    double average = total / count;
                    std::lock_guard<std::mutex> lock(resultMutex);
                    results.emplace_back(group->getID(), average);
                }
            }
        });
    }
    
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    
    if (view_) {
        view_->printMessage("\n=== Средний балл по всем группам (многопоточно) ===");
        for (const auto& [groupID, avg] : results) {
            view_->printMessage("Группа " + groupID + ": " + std::to_string(avg));
        }
    }
    
    return results;
}

