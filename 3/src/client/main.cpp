#include "../repository/university.h"
#include "../repository/group.h"
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../view/tableView.h"
#include "../controller/highLevelController.h"
#include "../controller/inputController.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <limits>

/**
 * @brief Главная функция приложения
 * 
 * Реализует диалоговый интерфейс для работы с системой учета успеваемости студентов.
 */
int main() {
    try {
        std::unique_ptr<University> university = std::make_unique<University>();
        std::unique_ptr<TableDialogView> view = std::make_unique<TableDialogView>();
        std::unique_ptr<HighLevelController> highController = 
            std::make_unique<HighLevelController>(university.get(), view.get());
        std::unique_ptr<InputController> inputController = 
            std::make_unique<InputController>(university.get(), highController.get());
        
        std::cout << "=== Система учета успеваемости студентов ===" << std::endl;
        std::cout << "Введите 'help' для списка команд или 'exit' для выхода" << std::endl;
        std::cout << std::endl;
        
        std::string line;
        bool running = true;
        
        while (running) {
            if (!std::cin.good()) {
                if (std::cin.eof()) {
                    std::cout << std::endl << "Обнаружен EOF. Завершение работы..." << std::endl;
                    break;
                }
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Ошибка ввода. Попробуйте снова." << std::endl;
                    continue;
                }
            }
            
            std::cout << "> ";
            std::cout.flush();
            
            if (!std::getline(std::cin, line)) {
                if (std::cin.eof()) {
                    std::cout << std::endl << "Обнаружен EOF. Завершение работы..." << std::endl;
                    break;
                }
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Ошибка чтения ввода. Попробуйте снова." << std::endl;
                    continue;
                }
            }
            
            if (line.empty()) {
                continue;
            }
            
            try {
                inputController->processInput(line);
            } catch (const std::exception& e) {
                view->printError("Ошибка при обработке команды: " + std::string(e.what()));
            } catch (...) {
                view->printError("Неизвестная ошибка при обработке команды");
            }
            
            std::cout << std::endl;
        }
        
        try {
            size_t groupCount = university->getGroupCount();
            size_t totalStudents = university->getTotalStudentCount();
            view->printState(groupCount, totalStudents);
        } catch (...) {
            
        }
        
        std::cout << "Выход из программы." << std::endl;
        return 0;
        
    } catch (const std::bad_alloc& e) {
        std::cerr << "Критическая ошибка: не удалось выделить память. " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная критическая ошибка" << std::endl;
        return 1;
    }
}
