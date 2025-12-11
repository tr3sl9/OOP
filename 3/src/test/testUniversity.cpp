#include <catch2/catch_all.hpp>
#include "../repository/university.h"
#include "../repository/group.h"
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../model/studentInterface.h"
#include <memory>

TEST_CASE("University: создание университета", "[university]") {
    University university;
    
    REQUIRE(university.getGroupCount() == 0);
}

TEST_CASE("University: добавление групп", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    university.addGroup("ГР-02", 6, CategoryStudent::SENIOR);
    
    REQUIRE(university.getGroupCount() == 2);
}

TEST_CASE("University: поиск группы", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    
    auto group = university.findGroup("ГР-01");
    REQUIRE(group != nullptr);
    REQUIRE(group->getID() == "ГР-01");
    
    auto notFound = university.findGroup("ГР-99");
    REQUIRE(notFound == nullptr);
}

TEST_CASE("University: удаление группы", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    REQUIRE(university.getGroupCount() == 1);
    
    university.removeGroup("ГР-01");
    REQUIRE(university.getGroupCount() == 0);
    
    auto group = university.findGroup("ГР-01");
    REQUIRE(group == nullptr);
}

TEST_CASE("University: получение всех групп", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    university.addGroup("ГР-02", 6, CategoryStudent::SENIOR);
    university.addGroup("ГР-03", 5, CategoryStudent::JUNIOR);
    
    auto groups = university.getAllGroups();
    REQUIRE(groups.size() == 3);
}

TEST_CASE("University: общее количество студентов", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    university.addGroup("ГР-02", 6, CategoryStudent::SENIOR);
    
    auto group1 = university.findGroup("ГР-01");
    auto group2 = university.findGroup("ГР-02");
    
    group1->addStudent(std::make_shared<JuniorStudent>("Студент1 С.С."));
    group1->addStudent(std::make_shared<JuniorStudent>("Студент2 С.С."));
    group2->addStudent(std::make_shared<SeniorStudent>("Студент3 С.С."));
    
    REQUIRE(university.getTotalStudentCount() == 3);
}

TEST_CASE("University: обновление ID группы", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    
    bool result = university.updateGroup("ГР-01", "ГР-02");
    REQUIRE(result == true);
    
    auto oldGroup = university.findGroup("ГР-01");
    REQUIRE(oldGroup == nullptr);
    
    auto newGroup = university.findGroup("ГР-02");
    REQUIRE(newGroup != nullptr);
    REQUIRE(newGroup->getID() == "ГР-02");
}

TEST_CASE("University: обновление максимального количества дисциплин", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    
    bool result = university.updateGroup("ГР-01", 7);
    REQUIRE(result == true);
    
    auto group = university.findGroup("ГР-01");
    REQUIRE(group != nullptr);
    REQUIRE(group->getMaxCountDisciplines() == 7);
}

TEST_CASE("University: обновление типа группы", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    
    bool result = university.updateGroup("ГР-01", CategoryStudent::SENIOR);
    REQUIRE(result == true);
    
    auto group = university.findGroup("ГР-01");
    REQUIRE(group != nullptr);
    REQUIRE(group->getGroupType() == CategoryStudent::SENIOR);
}

TEST_CASE("University: обновление несуществующей группы", "[university]") {
    University university;
    
    bool result1 = university.updateGroup("ГР-99", "ГР-100");
    REQUIRE(result1 == false);
    
    bool result2 = university.updateGroup("ГР-99", 10);
    REQUIRE(result2 == false);
    
    bool result3 = university.updateGroup("ГР-99", CategoryStudent::SENIOR);
    REQUIRE(result3 == false);
}

TEST_CASE("University: обновление ID на существующий", "[university]") {
    University university;
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    university.addGroup("ГР-02", 6, CategoryStudent::SENIOR);
    
    bool result = university.updateGroup("ГР-01", "ГР-02");
    REQUIRE(result == false);
    
    auto group1 = university.findGroup("ГР-01");
    REQUIRE(group1 != nullptr);
}

