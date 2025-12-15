#include <catch2/catch_all.hpp>
#include "../controller/inputController.h"
#include "../controller/highLevelController.h"
#include "../repository/university.h"
#include "../view/tableView.h"

TEST_CASE("InputController: создание контроллера", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController, &view);
    
    REQUIRE_NOTHROW(controller.processInput("help"));
}

TEST_CASE("InputController: обработка команды help", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController, &view);
    
    REQUIRE_NOTHROW(controller.processInput("help"));
}

TEST_CASE("InputController: обработка команды add_group", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController, &view);
    
    controller.processInput("add_group С25-501 5 JUNIOR");
    
    auto group = university.findGroup("С25-501");
    REQUIRE(group != nullptr);
    REQUIRE(group->getGroupType() == CategoryStudent::JUNIOR);
}

TEST_CASE("InputController: обработка команды add_student", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController, &view);
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    controller.processInput("add_student С24-501 Иванов");
    
    auto group = university.findGroup("С24-501");
    REQUIRE(group->getStudentCount() == 1);
}

TEST_CASE("InputController: обработка команды show_group", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController, &view);
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    
    REQUIRE_NOTHROW(controller.processInput("show_group С24-501"));
}

TEST_CASE("InputController: обработка команды show_all", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController, &view);
    
    university.addGroup("С24-501", 5, CategoryStudent::JUNIOR);
    university.addGroup("С25-502", 6, CategoryStudent::SENIOR);
    
    REQUIRE_NOTHROW(controller.processInput("show_all"));
}

TEST_CASE("InputController: обработка неизвестной команды", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController, &view);
    
    REQUIRE_NOTHROW(controller.processInput("unknown_command"));
}

TEST_CASE("InputController: обработка пустой строки", "[inputcontroller]") {
    University university;
    TableDialogView view;
    HighLevelController highController(&university, &view);
    InputController controller(&university, &highController, &view);
    
    std::string emptyStr;
    REQUIRE_NOTHROW(controller.processInput(emptyStr));
}

