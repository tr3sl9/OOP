#include <catch2/catch_all.hpp>
#include <iostream>
#include <sstream>
#include "../view/tableView.h"
#include "../repository/group.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../repository/university.h"

TEST_CASE("TableView: создание view", "[view]") {
    TableDialogView view;
    REQUIRE_NOTHROW(view.printState(0, 0));
}

TEST_CASE("TableView: вывод состояния системы", "[view]") {
    TableDialogView view;
    std::ostringstream oss;
    
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    
    view.printState(5, 20);
    
    std::cout.rdbuf(oldCout);
    
    std::string output = oss.str();
    REQUIRE(output.find("Количество групп: 5") != std::string::npos);
    REQUIRE(output.find("Общее количество студентов: 20") != std::string::npos);
}

TEST_CASE("TableView: вывод информации о группе", "[view]") {
    TableDialogView view;
    Group group("С24-501", 5, CategoryStudent::JUNIOR);
    
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    
    view.printGroup(&group);
    
    std::cout.rdbuf(oldCout);
    
    std::string output = oss.str();
    REQUIRE(output.find("С24-501") != std::string::npos);
    REQUIRE(output.find("5") != std::string::npos);
}

TEST_CASE("TableView: вывод информации о студенте", "[view]") {
    TableDialogView view;
    JuniorStudent student("Иванов И.И.");
    student.addGrade(5);
    student.addGrade(4);
    
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    
    view.printStudent(&student);
    
    std::cout.rdbuf(oldCout);
    
    std::string output = oss.str();
    REQUIRE(output.find("Иванов И.И.") != std::string::npos);
    REQUIRE(output.find("5") != std::string::npos);
    REQUIRE(output.find("4") != std::string::npos);
}

TEST_CASE("TableView: вывод информации о старшекурснике", "[view]") {
    TableDialogView view;
    SeniorStudent student("Петров П.П.");
    student.setERWName("ИИ дебилы");
    student.setPlace("Кафедра 22");
    student.setERWGrade(5);
    
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    
    view.printStudent(&student);
    
    std::cout.rdbuf(oldCout);
    
    std::string output = oss.str();
    REQUIRE(output.find("Петров П.П.") != std::string::npos);
    REQUIRE(output.find("ИИ дебилы") != std::string::npos);
    REQUIRE(output.find("Кафедра 22") != std::string::npos);
}

TEST_CASE("TableView: вывод сообщения", "[view]") {
    TableDialogView view;
    
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    
    view.printMessage("Тестовое сообщение");
    
    std::cout.rdbuf(oldCout);
    
    std::string output = oss.str();
    REQUIRE(output.find("Тестовое сообщение") != std::string::npos);
}

TEST_CASE("TableView: вывод ошибки", "[view]") {
    TableDialogView view;
    
    std::ostringstream oss;
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::cerr.rdbuf(oss.rdbuf());
    
    view.printError("Тестовая ошибка");
    
    std::cerr.rdbuf(oldCerr);
    
    std::string output = oss.str();
    REQUIRE(output.find("Тестовая ошибка") != std::string::npos);
    REQUIRE(output.find("ОШИБКА") != std::string::npos);
}

TEST_CASE("TableView: вывод nullptr группы", "[view]") {
    TableDialogView view;
    
    std::ostringstream oss;
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::cerr.rdbuf(oss.rdbuf());
    
    view.printGroup(nullptr);
    
    std::cerr.rdbuf(oldCerr);
    
    std::string output = oss.str();
    REQUIRE(output.find("не найдена") != std::string::npos);
}

TEST_CASE("TableView: вывод nullptr студента", "[view]") {
    TableDialogView view;
    
    std::ostringstream oss;
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::cerr.rdbuf(oss.rdbuf());
    
    view.printStudent(nullptr);
    
    std::cerr.rdbuf(oldCerr);
    
    std::string output = oss.str();
    REQUIRE(output.find("не найден") != std::string::npos);
}

