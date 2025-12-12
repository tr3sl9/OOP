#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <string>
#include <vector>
#include <memory>

// Forward declaration
class University;
class ControllerProvider;

/**
 * @brief Интерфейс для обработки ввода
 */
class InputProvider {
public:
    virtual ~InputProvider() = default;
    
    /**
     * @brief Обработать ввод
     * @param input Входная строка
     */
    virtual bool processInput(const std::string& input) = 0;
};

/**
 * @brief Контроллер ввода
 */
class InputController : public InputProvider {
private:
    University* university_;
    ControllerProvider* controller_; ///< Высокоуровневый контроллер для бизнес-операций
    
    /**
     * @brief Обработать команду
     * @param command Команда
     * @param args Аргументы команды
     */
    bool processCommand(const std::string& command, const std::vector<std::string>& args) noexcept;
    
    /**
     * @brief Разбить строку на токены
     * @param input Входная строка
     * @return Вектор токенов
     */
    std::vector<std::string> tokenize(const std::string& input) const;

public:
    /**
     * @brief Конструктор
     * @param university Указатель на университет (репозиторий групп)
     * @param controller Указатель на высокоуровневый контроллер (бизнес-логика)
     */
    InputController(University* university, ControllerProvider* controller);
    
    /**
     * @brief Деструктор
     */
    ~InputController() override = default;
    
    /**
     * @brief Обработать ввод
     * @param input Входная строка
     */
    bool processInput(const std::string& input) override;
};

#endif

