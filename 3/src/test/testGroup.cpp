#include <catch2/catch_all.hpp>
#include "../repository/group.h"
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../model/studentInterface.h"
#include "../repository/studentTable.h"
#include <memory>

TEST_CASE("Group: создание группы", "[group]") {
    Group group("С24-501", 5, CategoryStudent::JUNIOR);
    
    REQUIRE(group.getID() == "С24-501");
    REQUIRE(group.getMaxCountDisciplines() == 5);
    REQUIRE(group.getGroupType() == CategoryStudent::JUNIOR);
    REQUIRE(group.getStudentCount() == 0);
}

TEST_CASE("Group: добавление студентов", "[group]") {
    Group group("Б24-503", 6, CategoryStudent::SENIOR);
    
    auto student1 = std::make_shared<SeniorStudent>("Студент1 С.С.");
    auto student2 = std::make_shared<SeniorStudent>("Студент2 С.С.");
    
    group.addStudent(student1);
    group.addStudent(student2);
    
    REQUIRE(group.getStudentCount() == 2);
}

TEST_CASE("Group: удаление студентов", "[group]") {
    Group group("С25-501", 5, CategoryStudent::JUNIOR);
    
    auto student = std::make_shared<JuniorStudent>("Удаляемый У.У.");
    group.addStudent(student);
    
    REQUIRE(group.getStudentCount() == 1);
    
    group.removeStudent("Удаляемый У.У.");
    
    REQUIRE(group.getStudentCount() == 0);
}

TEST_CASE("Group: изменение параметров", "[group]") {
    Group group("С26-501", 5, CategoryStudent::JUNIOR);
    
    group.setID("Б26-503");
    group.setMaxCountDisciplines(6);
    group.setGroupType(CategoryStudent::SENIOR);
    
    REQUIRE(group.getID() == "Б26-503");
    REQUIRE(group.getMaxCountDisciplines() == 6);
    REQUIRE(group.getGroupType() == CategoryStudent::SENIOR);
}

TEST_CASE("Group: получение таблицы студентов", "[group]") {
    Group group("С27-501", 5, CategoryStudent::JUNIOR);
    
    auto table = group.getTable();
    REQUIRE(table != nullptr);
    REQUIRE(table->empty());
    
    auto student = std::make_shared<JuniorStudent>("Тест Т.Т.");
    group.addStudent(student);
    
    REQUIRE_FALSE(table->empty());
    REQUIRE(table->size() == 1);
}

