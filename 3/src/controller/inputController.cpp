#include "inputController.h"
#include "highLevelController.h"
#include "../repository/university.h"
#include "../repository/group.h"
#include "../model/studentInterface.h"
#include "../repository/studentTable.h"
#include "../view/tableView.h"
#include <sstream>
#include <algorithm>
#include <cctype>
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

InputController::InputController(University* university, ControllerProvider* controller, ITableView* view)
    : university_(university), controller_(controller), view_(view) {}

std::vector<std::string> InputController::tokenize(const std::string& input) const {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

bool InputController::processCommand(const std::string& command, const std::vector<std::string>& args) noexcept {
    const std::string cmd = toLower(command);

    if (!controller_ || !university_) {
        if (view_) {
            view_->printError("Контроллер не инициализирован");
        }
        return false;
    }

    University* university = university_;
    ControllerProvider* controller = controller_;
    ITableView* view = view_;

    struct Command {
        const char* name;
        const char* usage;
        std::function<void(const std::vector<std::string>&)> action;
    };

    bool shouldExit = false;

    const std::array<Command, 10> commands = {{
        {"help", "help", [view](const std::vector<std::string>&) {
            if (!view) return;
            view->printMessage("Команды:");
            view->printMessage("  help");
            view->printMessage("  add_group <id> <max_disciplines> <type(JUNIOR|SENIOR|STUDENT)>");
            view->printMessage("  add_student <group_id> <fullname>");
            view->printMessage("  del_student <group_id> <fullname>");
            view->printMessage("  semester <group_id>");
            view->printMessage("  avg <group_id>");
            view->printMessage("  lagging [group_id]");
            view->printMessage("  show_group <group_id>");
            view->printMessage("  show_all");
            view->printMessage("  exit");
        }},
        
        {"add_group", "add_group <id> <max_disciplines> <type>", [university, view](const std::vector<std::string>& a) {
            if (a.size() < 3) { 
                if (view) view->printError("Использование: add_group <id> <max_disciplines> <type>");
                return; 
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

            if (university->findGroup(id)) {
                if (view) view->printError("Группа " + id + " уже существует");
                return;
            }

            university->addGroup(id, maxDisc, type);
            if (view) view->printMessage("Группа " + id + " добавлена");
        }},

        {"add_student", "add_student <group_id> <fullname>", [controller, view, university](const std::vector<std::string>& a) {
            if (a.size() < 2) { 
                if (view) view->printError("Использование: add_student <group_id> <fullname>");
                return; 
            }

            if (!university->findGroup(a[0])) {
                if (view) view->printError("Группа " + a[0] + " не найдена");
                return;
            }

            controller->applyStudentAdmission(a[0], a[1], 0);
        }},

        {"del_student", "del_student <group_id> <fullname>", [university, view](const std::vector<std::string>& a) {
            if (a.size() < 2) {
                if (view) view->printError("Использование: del_student <group_id> <fullname>");
                return;
            }

            auto g = university->findGroup(a[0]);
            if (!g) {
                if (view) view->printError("Группа " + a[0] + " не найдена");
                return;
            }

            auto table = g->getTable();
            if (!table) {
                if (view) view->printError("Таблица студентов для группы " + a[0] + " не найдена");
                return;
            }

            table->removeStudent(a[1]);
            if (view) view->printMessage("Студент \"" + a[1] + "\" удалён из группы " + a[0]);
        }},

        {"semester", "semester <group_id>", [controller, view](const std::vector<std::string>& a) {
            if (a.empty()) { 
                if (view) view->printError("Использование: semester <group_id>");
                return; 
            }

            controller->semesterControl(a[0]);
        }},

        {"avg", "avg <group_id>", [controller, view](const std::vector<std::string>& a) {
            if (a.empty()) { 
                if (view) view->printError("Использование: avg <group_id>");
                return;
            }

            controller->averageGroupGrade(a[0]);
        }},

        {"lagging", "lagging [group_id]", [controller](const std::vector<std::string>& a) {
            const std::string group = a.empty() ? "" : a[0];
            controller->laggingStudents(group);
        }},

        {"show_group", "show_group <group_id>", [university, view](const std::vector<std::string>& a) {
            if (a.empty()) { 
                if (view) view->printError("Использование: show_group <group_id>");
                return;
            }
            
            auto g = university->findGroup(a[0]);
            if (g) {
                if (view) {
                    view->printGroup(g.get());
                }
            } else {
                if (view) view->printError("Группа " + a[0] + " не найдена");
            }
        }},

        {"show_all", "show_all", [university, view](const std::vector<std::string>&) {
            auto groups = university->getAllGroups();
            if (groups.empty()) {
                if (view) view->printMessage("Нет групп");
                return;
            }

            for (const auto& g : groups) {
                if (!g || !view) {
                    continue;
                }

                view->printMessage("\n=== Группа " + g->getID() + " ===");
                view->printMessage("Макс. дисциплин: " + std::to_string(g->getMaxCountDisciplines()));
                view->printMessage("Студентов: " + std::to_string(g->getStudentCount()));
                auto table = g->getTable();

                if (!table) {
                    continue;
                }

                auto students = table->getAllStudents();
                for (const auto& s : students) {
                    if (!s) {
                        continue;
                    }

                    view->printMessage(" - " + s->getFullName());
                }
            }
        }},

        {"exit", "exit", [&shouldExit, view](const std::vector<std::string>&) {
            if (view) {
                view->printMessage("Завершение работы.");
            }
            shouldExit = true;
        }}
    }};

    for (const auto& c : commands) {
        if (cmd == c.name) {
            c.action(args);
            return shouldExit;
        }
    }

    if (view) {
        view->printError("Неизвестная команда: " + command + ". Введите help");
    }
    return shouldExit;
}

bool InputController::processInput(const std::string& input) {
    auto tokens = tokenize(input);
    if (tokens.empty()) {
        return false;
    }
    
    std::string command = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());
    
    return processCommand(command, args);
}

