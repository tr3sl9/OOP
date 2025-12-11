#include <catch2/catch_all.hpp>
#include "../repository/studentTable.h"
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include <memory>

TEST_CASE("StudentTable: создание таблицы", "[studenttable]") {
    StudentTable table;
    
    REQUIRE(table.empty());
    REQUIRE(table.size() == 0);
}

TEST_CASE("StudentTable: добавление студентов", "[studenttable]") {
    StudentTable table;
    
    auto student1 = std::make_shared<JuniorStudent>("Иванов И.И.");
    auto student2 = std::make_shared<SeniorStudent>("Петров П.П.");
    
    table.addStudent(student1);
    table.addStudent(student2);
    
    REQUIRE(table.size() == 2);
    REQUIRE_FALSE(table.empty());
}

TEST_CASE("StudentTable: поиск студента", "[studenttable]") {
    StudentTable table;
    
    auto student = std::make_shared<JuniorStudent>("Сидоров С.С.");
    table.addStudent(student);
    
    auto found = table.findStudent("Сидоров С.С.");
    REQUIRE(found != nullptr);
    REQUIRE(found->getFullName() == "Сидоров С.С.");
    
    auto notFound = table.findStudent("Несуществующий Н.Н.");
    REQUIRE(notFound == nullptr);
}

TEST_CASE("StudentTable: удаление студента", "[studenttable]") {
    StudentTable table;
    
    auto student = std::make_shared<JuniorStudent>("Удаляемый У.У.");
    table.addStudent(student);
    
    REQUIRE(table.size() == 1);
    
    table.removeStudent("Удаляемый У.У.");
    
    REQUIRE(table.size() == 0);
    REQUIRE(table.empty());
}

TEST_CASE("StudentTable: очистка таблицы", "[studenttable]") {
    StudentTable table;
    
    table.addStudent(std::make_shared<JuniorStudent>("Студент1 С.С."));
    table.addStudent(std::make_shared<JuniorStudent>("Студент2 С.С."));
    table.addStudent(std::make_shared<JuniorStudent>("Студент3 С.С."));
    
    REQUIRE(table.size() == 3);
    
    table.clear();
    
    REQUIRE(table.size() == 0);
    REQUIRE(table.empty());
}

TEST_CASE("StudentTable: получение всех студентов", "[studenttable]") {
    StudentTable table;
    
    table.addStudent(std::make_shared<JuniorStudent>("Антонов А.А."));
    table.addStudent(std::make_shared<JuniorStudent>("Борисов Б.Б."));
    table.addStudent(std::make_shared<JuniorStudent>("Васильев В.В."));
    
    auto students = table.getAllStudents();
    REQUIRE(students.size() == 3);
    
    REQUIRE(students[0]->getFullName() == "Антонов А.А.");
    REQUIRE(students[1]->getFullName() == "Борисов Б.Б.");
    REQUIRE(students[2]->getFullName() == "Васильев В.В.");
}

TEST_CASE("StudentTable: итераторы", "[studenttable]") {
    StudentTable table;
    
    table.addStudent(std::make_shared<JuniorStudent>("Итератор1 И.И."));
    table.addStudent(std::make_shared<JuniorStudent>("Итератор2 И.И."));
    
    size_t count = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        REQUIRE(*it != nullptr);
        count++;
    }
    
    REQUIRE(count == 2);
}

TEST_CASE("StudentTable: константные итераторы", "[studenttable]") {
    StudentTable table;
    
    table.addStudent(std::make_shared<JuniorStudent>("Констант К.К."));
    
    const StudentTable& constTable = table;
    size_t count = 0;
    for (auto it = constTable.begin(); it != constTable.end(); ++it) {
        REQUIRE(*it != nullptr);
        count++;
    }
    
    REQUIRE(count == 1);
}

TEST_CASE("StudentTable: дубликаты студентов", "[studenttable]") {
    StudentTable table;
    
    auto student = std::make_shared<JuniorStudent>("Дубликат Д.Д.");
    table.addStudent(student);
    
    REQUIRE(table.size() == 1);
    
    auto duplicate = std::make_shared<JuniorStudent>("Дубликат Д.Д.");
    table.addStudent(duplicate);
    
    REQUIRE(table.size() == 1);
}

TEST_CASE("StudentTable: добавление nullptr", "[studenttable]") {
    StudentTable table;
    
    table.addStudent(nullptr);
    
    REQUIRE(table.size() == 0);
    REQUIRE(table.empty());
}

