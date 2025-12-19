#include <catch2/catch_all.hpp>
#include "../repository/university.h"
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
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    university.addGroup("С25-501", 6, CategoryStudent::SENIOR);
    
    REQUIRE(university.getGroupCount() == 2);
}

TEST_CASE("University: поиск группы", "[university]") {
    University university;
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    
    auto group = university.findGroup("С24-501");
    REQUIRE(group != nullptr);
    REQUIRE(group->getID() == "С24-501");
    
    auto notFound = university.findGroup("С99-501");
    REQUIRE(notFound == nullptr);
}

TEST_CASE("University: удаление группы", "[university]") {
    University university;
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    REQUIRE(university.getGroupCount() == 1);
    
    university.removeGroup("С24-501");
    REQUIRE(university.getGroupCount() == 0);
    
    auto group = university.findGroup("С24-501");
    REQUIRE(group == nullptr);
}

TEST_CASE("University: получение всех групп", "[university]") {
    University university;
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    university.addGroup("С25-501", 6, CategoryStudent::SENIOR);
    university.addGroup("С26-501", 5, CategoryStudent::JUNIOR);
    
    auto groups = university.getAllGroups();
    REQUIRE(groups.size() == 3);
}

TEST_CASE("University: общее количество студентов", "[university]") {
    University university;
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    university.addGroup("С25-501", 6, CategoryStudent::SENIOR);
    
    auto group1 = university.findGroup("С24-501");
    auto group2 = university.findGroup("С25-501");
    
    group1->addStudent(std::make_shared<JuniorStudent>("Студент1 С.С."));
    group1->addStudent(std::make_shared<JuniorStudent>("Студент2 С.С."));
    group2->addStudent(std::make_shared<SeniorStudent>("Студент3 С.С."));
    
    REQUIRE(university.getTotalStudentCount() == 3);
}

TEST_CASE("University: обновление ID группы", "[university]") {
    University university;
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    
    bool result = university.updateGroup("С24-501", "С25-501");
    REQUIRE(result == true);
    
    auto oldGroup = university.findGroup("С24-501");
    REQUIRE(oldGroup == nullptr);
    
    auto newGroup = university.findGroup("С25-501");
    REQUIRE(newGroup != nullptr);
    REQUIRE(newGroup->getID() == "С25-501");
}

TEST_CASE("University: обновление максимального количества дисциплин", "[university]") {
    University university;
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    
    bool result = university.updateGroup("С24-501", 7);
    REQUIRE(result == true);
    
    auto group = university.findGroup("С24-501");
    REQUIRE(group != nullptr);
    REQUIRE(group->getMaxCountDisciplines() == 7);
}

TEST_CASE("University: обновление типа группы", "[university]") {
    University university;
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    
    bool result = university.updateGroup("С24-501", CategoryStudent::SENIOR);
    REQUIRE(result == true);
    
    auto group = university.findGroup("С24-501");
    REQUIRE(group != nullptr);
    REQUIRE(group->getGroupType() == CategoryStudent::SENIOR);
}

TEST_CASE("University: обновление несуществующей группы", "[university]") {
    University university;
    
    bool result1 = university.updateGroup("С24-501", "Б24-503");
    REQUIRE(result1 == false);
    
    bool result2 = university.updateGroup("С24-501", 10);
    REQUIRE(result2 == false);
    
    bool result3 = university.updateGroup("С24-501", CategoryStudent::SENIOR);
    REQUIRE(result3 == false);
}

TEST_CASE("University: обновление ID на существующий", "[university]") {
    University university;
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    university.addGroup("С25-501", 6, CategoryStudent::SENIOR);
    
    bool result = university.updateGroup("С24-501", "С25-501");
    REQUIRE(result == false);
    
    auto group1 = university.findGroup("С24-501");
    REQUIRE(group1 != nullptr);
}

