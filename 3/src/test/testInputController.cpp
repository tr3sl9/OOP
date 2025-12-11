#include <catch2/catch_all.hpp>
#include "../controller/inputController.h"
#include "../controller/highLevelController.h"
#include "../repository/university.h"
#include "../view/tableView.h"
#include <sstream>

TEST_CASE("InputController: создание контроллера", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController);
    
    REQUIRE_NOTHROW(controller.processInput("help"));
}

TEST_CASE("InputController: обработка команды help", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController);
    
    REQUIRE_NOTHROW(controller.processInput("help"));
}

TEST_CASE("InputController: обработка команды add_group", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController);
    
    controller.processInput("add_group ГР-01 5 JUNIOR");
    
    auto group = university.findGroup("ГР-01");
    REQUIRE(group != nullptr);
    REQUIRE(group->getGroupType() == CategoryStudent::JUNIOR);
}

TEST_CASE("InputController: обработка команды add_student", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController);
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    controller.processInput("add_student ГР-01 Иванов И.И. 5");
    
    auto group = university.findGroup("ГР-01");
    REQUIRE(group->getStudentCount() == 1);
}

TEST_CASE("InputController: обработка команды show_group", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController);
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    
    REQUIRE_NOTHROW(controller.processInput("show_group ГР-01"));
}

TEST_CASE("InputController: обработка команды show_all", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController);
    
    university.addGroup("ГР-01", 5, CategoryStudent::JUNIOR);
    university.addGroup("ГР-02", 6, CategoryStudent::SENIOR);
    
    REQUIRE_NOTHROW(controller.processInput("show_all"));
}

TEST_CASE("InputController: обработка неизвестной команды", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController);
    
    REQUIRE_NOTHROW(controller.processInput("unknown_command"));
}

TEST_CASE("InputController: обработка пустой строки", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController);
    
    REQUIRE_NOTHROW(controller.processInput(""));
}

