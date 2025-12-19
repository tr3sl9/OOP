#include "tableView.h"
#include "../model/student.h"
#include "../repository/group.h"
#include "../model/seniorStudent.h"
#include "../model/studentInterface.h"
#include <iostream>
#include <iomanip>

TableDialogView::TableDialogView() {}

void TableDialogView::printState(size_t groupCount, size_t totalStudentCount) const {
    std::cout << "\n=== Состояние системы ===" << std::endl;
    std::cout << "Количество групп: " << groupCount << std::endl;
    std::cout << "Общее количество студентов: " << totalStudentCount << std::endl;
    std::cout << "==========================\n" << std::endl;
}

void TableDialogView::printGroup(const Group* group) const {
    if (!group) {
        printError("Группа не найдена");
        return;
    }
    
    std::cout << "\n=== Информация о группе ===" << std::endl;
    std::cout << "ID группы: " << group->getID() << std::endl;
    std::cout << "Максимум дисциплин: " << group->getMaxCountDisciplines() << std::endl;
    std::cout << "Тип группы: ";
    switch (group->getGroupType()) {
        case CategoryStudent::JUNIOR:
            std::cout << "Младшекурсники";
            break;
        case CategoryStudent::SENIOR:
            std::cout << "Старшекурсники";
            break;
        default:
            std::cout << "Студенты";
            break;
    }
    std::cout << std::endl;
    std::cout << "Количество студентов: " << group->getStudentCount() << std::endl;
}

void TableDialogView::printStudent(const Student* student) const {
    if (!student) {
        printError("Студент не найден");
        return;
    }
    
    std::cout << "\n=== Информация о студенте ===" << std::endl;
    std::cout << "ФИО: " << student->getFullName() << std::endl;
    std::cout << "Тип: ";
    switch (student->getStudentType()) {
        case CategoryStudent::JUNIOR:
            std::cout << "Младшекурсник";
            break;
        case CategoryStudent::SENIOR:
            std::cout << "Старшекурсник";
            {
                const auto* senior = dynamic_cast<const SeniorStudent*>(student);
                if (senior) {
                    std::cout << std::endl;
                    std::cout << "УИР: " << senior->getERWName() << std::endl;
                    std::cout << "Место выполнения УИР: " << senior->getPlaceERW() << std::endl;
                    std::cout << "Оценка за УИР: " << senior->getERWGrade() << std::endl;
                }
            }
            break;
        default:
            std::cout << "Студент";
            break;
    }
    std::cout << std::endl;
    
    auto grades = student->getGrades();
    if (!grades.empty()) {
        std::cout << "Оценки: ";
        for (size_t i = 0; i < grades.size(); ++i) {
            std::cout << grades[i];
            if (i < grades.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        std::cout << "Средний балл: " << std::fixed << std::setprecision(2) 
                  << student->average() << std::endl;
    } else {
        std::cout << "Оценок нет" << std::endl;
    }
}

void TableDialogView::printMessage(const std::string& message) const {
    std::cout << message << std::endl;
}

void TableDialogView::printError(const std::string& error) const {
    std::cerr << "ОШИБКА: " << error << std::endl;
}

