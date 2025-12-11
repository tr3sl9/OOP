#include "inputController.h"
#include "highLevelController.h"
#include "../repository/university.h"
#include "../repository/group.h"
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../model/studentInterface.h"
#include "../repository/studentTable.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <array>
#include <functional>

namespace {
std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    return s;
}

int parseInt(const std::string& s, int fallback = 0) noexcept {
    try {
        size_t pos = 0;
        int v = std::stoi(s, &pos);
        if (pos != s.size()) {
            return fallback;
        }
        return v;
    } catch (...) {
        return fallback;
    }
}
}

InputController::InputController(University* university, ControllerProvider* controller)
    : university_(university), controller_(controller) {}

std::vector<std::string> InputController::tokenize(const std::string& input) const {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

void InputController::processCommand(const std::string& command, const std::vector<std::string>& args) noexcept {
    const std::string cmd = toLower(command);

    if (!controller_ || !university_) {
        std::cout << "Контроллер не инициализирован\n";
        return;
    }

    University* university = university_;
    ControllerProvider* controller = controller_;

    struct Command {
        const char* name;
        const char* usage;
        std::function<void(const std::vector<std::string>&)> action;
    };

    const std::array<Command, 10> commands = {{
        {"help", "help", [](const std::vector<std::string>&) {
            std::cout << "Команды:\n"
                      << "  help\n"
                      << "  add_group <id> <max_disciplines> <type(JUNIOR|SENIOR|STUDENT)>\n"
                      << "  add_student <group_id> <fullname>\n"
                      << "  del_student <group_id> <fullname>\n"
                      << "  semester <group_id>\n"
                      << "  avg <group_id>\n"
                      << "  lagging [group_id]\n"
                      << "  show_group <group_id>\n"
                      << "  show_all\n"
                      << "  exit\n";
        }},
        
        {"add_group", "add_group <id> <max_disciplines> <type>", [university](const std::vector<std::string>& a) {
            if (a.size() < 3) { 
                std::cout << "Использование: add_group <id> <max_disciplines> <type>\n"; return; 
            }

            const std::string& id = a[0];
            int maxDisc = parseInt(a[1], 0);
            CategoryStudent type = CategoryStudent::STUDENT;
            const std::string typeStr = toLower(a[2]);

            if (typeStr == "junior") {
                type = CategoryStudent::JUNIOR;
            }
            else if (typeStr == "senior") {
                type = CategoryStudent::SENIOR;
            }

            university->addGroup(id, maxDisc, type);
            std::cout << "Группа " << id << " добавлена\n";
        }},

        {"add_student", "add_student <group_id> <fullname>", [controller](const std::vector<std::string>& a) {
            if (a.size() < 2) { 
                std::cout << "Использование: add_student <group_id> <fullname>\n"; return; 
            }

            controller->applyStudentAdmission(a[0], a[1], 0);
        }},

        {"del_student", "del_student <group_id> <fullname>", [university](const std::vector<std::string>& a) {
            if (a.size() < 2) {
                std::cout << "Использование: del_student <group_id> <fullname>\n"; return;
            }

            auto g = university->findGroup(a[0]);
            if (!g) {
                std::cout << "Группа " << a[0] << " не найдена\n"; return;
            }

            auto table = g->getTable();
            if (!table) {
                std::cout << "Таблица студентов для группы " << a[0] << " не найдена\n"; return;
            }

            table->removeStudent(a[1]);
            std::cout << "Студент \"" << a[1] << "\" удалён из группы " << a[0] << "\n";
        }},

        {"semester", "semester <group_id>", [controller](const std::vector<std::string>& a) {
            if (a.empty()) { 
                std::cout << "Использование: semester <group_id>\n"; return; 
            }

            controller->semesterControl(a[0]);
        }},

        {"avg", "avg <group_id>", [controller](const std::vector<std::string>& a) {
            if (a.empty()) { 
                std::cout << "Использование: avg <group_id>\n"; return;
            }

            controller->averageGroupGrade(a[0]);
        }},

        {"lagging", "lagging [group_id]", [controller](const std::vector<std::string>& a) {
            const std::string group = a.empty() ? "" : a[0];
            controller->laggingStudents(group);
        }},

        {"show_group", "show_group <group_id>", [university](const std::vector<std::string>& a) {
            if (a.empty()) { 
                std::cout << "Использование: show_group <group_id>\n"; return;
            }
            
            auto g = university->findGroup(a[0]);
            if (g) {
                std::cout << "Группа: " << g->getID() << ", студентов: " << g->getStudentCount() << "\n";
            } else {
                std::cout << "Группа " << a[0] << " не найдена\n";
            }
        }},

        {"show_all", "show_all", [university](const std::vector<std::string>&) {
            auto groups = university->getAllGroups();
            if (groups.empty()) {
                std::cout << "Нет групп\n"; 
                return;
            }

            for (const auto& g : groups) {
                if (!g) {
                    continue;
                }

                std::cout << "\n=== Группа " << g->getID() << " ===\n";
                std::cout << "Макс. дисциплин: " << g->getMaxCountDisciplines() << "\n";
                std::cout << "Студентов: " << g->getStudentCount() << "\n";
                auto table = g->getTable();

                if (!table) {
                    continue;
                }

                auto students = table->getAllStudents();
                for (const auto& s : students) {
                    if (!s) {
                        continue;
                    }

                    std::cout << " - " << s->getFullName() << "\n";
                }
            }
            std::cout << std::endl;
        }},

        {"exit", "exit", [](const std::vector<std::string>&) {
            std::cout << "Завершение работы.\n";
            std::exit(0);
        }}
    }};

    for (const auto& c : commands) {
        if (cmd == c.name) {
            c.action(args);
            return;
        }
    }

    std::cout << "Неизвестная команда: " << command << ". Введите help\n";
}

void InputController::processInput(const std::string& input) {
    auto tokens = tokenize(input);
    if (tokens.empty()) {
        return;
    }
    
    std::string command = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());
    
    processCommand(command, args);
}

