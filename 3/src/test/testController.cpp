#include <catch2/catch_all.hpp>
#include "../repository/university.h"
#include "../view/tableView.h"
#include "../controller/highLevelController.h"
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../model/studentInterface.h"
#include "../repository/studentTable.h"
#include <memory>

TEST_CASE("HighLevelController: зачисление студента", "[controller]") {
    University university;
    TableDialogView view;
    HighLevelController controller(&university, &view);
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    
    controller.applyStudentAdmission("С24-501", "Симоненко М.В.", 5);
    
    auto group = university.findGroup("С24-501");
    REQUIRE(group != nullptr);
    REQUIRE(group->getStudentCount() == 1);
    
    auto table = group->getTable();
    auto student = table->findStudent("Симоненко М.В.");
    REQUIRE(student != nullptr);
    REQUIRE(student->getFullName() == "Симоненко М.В.");
}

TEST_CASE("HighLevelController: средний балл группы", "[controller]") {
    University university;
    TableDialogView view;
    HighLevelController controller(&university, &view);
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    
    controller.applyStudentAdmission("С24-501", "Студент1 С.С.", 5);
    controller.applyStudentAdmission("С24-501", "Студент2 С.С.", 5);
    
    auto group = university.findGroup("С24-501");
    auto table = group->getTable();
    
    auto student1 = table->findStudent("Студент1 С.С.");
    auto student2 = table->findStudent("Студент2 С.С.");
    
    student1->addGrade(5);
    student1->addGrade(4);
    student2->addGrade(3);
    student2->addGrade(4);
    
    double avg = controller.averageGroupGrade("С24-501");
    REQUIRE(avg == Catch::Approx(4.0).margin(0.01));
}

TEST_CASE("HighLevelController: поиск отстающих студентов", "[controller]") {
    University university;
    TableDialogView view;
    HighLevelController controller(&university, &view);
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    
    controller.applyStudentAdmission("С24-501", "Отстающий1 О.О.", 5);
    controller.applyStudentAdmission("С24-501", "Отстающий2 О.О.", 5);
    controller.applyStudentAdmission("С24-501", "Успевающий У.У.", 5);
    
    auto group = university.findGroup("С24-501");
    auto table = group->getTable();
    
    auto lagging1 = table->findStudent("Отстающий1 О.О.");
    auto lagging2 = table->findStudent("Отстающий2 О.О.");
    auto good = table->findStudent("Успевающий У.У.");
    
    lagging1->addGrade(2);
    lagging1->addGrade(2);
    lagging1->addGrade(2);
    
    lagging2->addGrade(2);
    lagging2->addGrade(2);
    lagging2->addGrade(2);
    lagging2->addGrade(2);
    
    good->addGrade(5);
    good->addGrade(4);
    good->addGrade(2);
    
    auto lagging = controller.laggingStudents("ГР-01");
    REQUIRE(lagging.size() == 2);
}

TEST_CASE("HighLevelController: ведомость семестрового контроля", "[controller]") {
    University university;
    TableDialogView view;
    HighLevelController controller(&university, &view);
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    controller.applyStudentAdmission("С24-501", "Студент С.С.", 5);
    
    auto group = university.findGroup("С24-501");
    auto table = group->getTable();
    auto student = table->findStudent("Студент С.С.");
    student->addGrade(5);
    student->addGrade(4);
    
    REQUIRE_NOTHROW(controller.semesterControl("С24-501"));
}

