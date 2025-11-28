#ifndef SENIOR_INTERFACE_H
#define SENIOR_INTERFACE_H

#include <string>

/**
 * @brief Интерфейс для работы с УИР (учебно-исследовательской работой)
 */
class ERWProvider {
public:
    virtual ~ERWProvider() = default;
    
    /**
     * @brief Получить название УИР
     * @return Направление темы УИР
     */
    virtual std::string getERWName() const = 0;
    
    /**
     * @brief Установить название УИР
     * @param ERW Направление темы УИР
     */
    virtual void setERWName(const std::string& ERW) noexcept = 0;
    
    /**
     * @brief Установить место выполнения УИР
     * @param placeERW Место выполнения
     */
    virtual void setPlace(const std::string& placeERW) noexcept = 0;
    
    /**
     * @brief Получить место выполнения УИР
     * @return Место выполнения УИР
     */
    virtual std::string getPlaceERW() const = 0;

    /**
     * @brief Получить оценку
     * @return Оценка
     */
    virtual int getGrade() const = 0;
};

#endif