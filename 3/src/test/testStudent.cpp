#include <catch2/catch_all.hpp>
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../model/studentInterface.h"

TEST_CASE("Student: создание и базовые операции", "[student]") {
    Student student("Иванов И.И.");
    
    REQUIRE(student.getFullName() == "Иванов И.И.");
    REQUIRE(student.getStudentType() == CategoryStudent::STUDENT);
    REQUIRE(student.getGrades().empty());
}

TEST_CASE("Student: добавление оценок", "[student]") {
    Student student("Петров П.П.");
    
    student.addGrade(5);
    student.addGrade(4);
    student.addGrade(3);
    
    auto grades = student.getGrades();
    REQUIRE(grades.size() == 3);
    REQUIRE(grades[0] == 5);
    REQUIRE(grades[1] == 4);
    REQUIRE(grades[2] == 3);
}

TEST_CASE("Student: вычисление среднего балла", "[student]") {
    Student student("Сидоров С.С.");
    
    student.addGrade(5);
    student.addGrade(4);
    student.addGrade(3);
    
    double avg = student.average();
    REQUIRE(avg == Catch::Approx(4.0).margin(0.01));
}

TEST_CASE("Student: средний балл пустого списка", "[student]") {
    Student student("Тестов Т.Т.");
    
    double avg = student.average();
    REQUIRE(avg == 0.0);
}

TEST_CASE("JuniorStudent: создание и тип", "[junior]") {
    JuniorStudent junior("Младший М.М.");
    
    REQUIRE(junior.getFullName() == "Младший М.М.");
    REQUIRE(junior.getStudentType() == CategoryStudent::JUNIOR);
}

TEST_CASE("SeniorStudent: создание и базовые операции", "[senior]") {
    SeniorStudent senior("Старший С.С.");
    
    REQUIRE(senior.getFullName() == "Старший С.С.");
    REQUIRE(senior.getStudentType() == CategoryStudent::SENIOR);
    REQUIRE(senior.getERWName().empty());
    REQUIRE(senior.getPlaceERW().empty());
    REQUIRE(senior.getERWGrade() == 0);
}

TEST_CASE("SeniorStudent: работа с УИР", "[senior]") {
    SeniorStudent senior("УИР У.У.");
    
    senior.setERWName("ИИ дебилы");
    senior.setPlace("Кафедра 22");
    senior.setERWGrade(5);
    
    REQUIRE(senior.getERWName() == "ИИ дебилы");
    REQUIRE(senior.getPlaceERW() == "Кафедра 22");
    REQUIRE(senior.getERWGrade() == 5);
    REQUIRE(senior.getGrade() == 5);
}

TEST_CASE("Student: интерфейс IGradeProvider", "[student]") {
    Student student("Интерфейс И.И.");
    
    student.addGrade(5);
    student.addGrade(4);
    
    std::vector<int> grades = student.getGrades();
    REQUIRE(grades[0] == 5);
}

