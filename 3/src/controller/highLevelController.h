#ifndef HIGH_LEVEL_CONTROLLER_H
#define HIGH_LEVEL_CONTROLLER_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>

// Forward declaration
class University;
class Group;
class Student;
class ITableView;

/**
 * @brief Интерфейс высокоуровневого контроллера
 */
class ControllerProvider {
public:
    virtual ~ControllerProvider() = default;
    
    /// Оформить поступление студента в институт
    virtual void applyStudentAdmission(const std::string& groupID, const std::string& fullname, int gradeCount) = 0;
    /// Оформить перевод студента на новый семестр
    virtual void transitionStudentCourse(const std::string& groupID, const std::string& fullname, int newGradeCount) = 0;
    /// Оформить ведомость семестрового контроля
    virtual void semesterControl(const std::string& groupID) = 0;
    /// Определить средний балл для указанной учебной группы
    virtual double averageGroupGrade(const std::string& groupID) = 0;
    /// Получить всех отстающих студентов (3+ двойки)
    virtual std::vector<std::shared_ptr<Student>> laggingStudents(const std::string& groupID = "") = 0;
};

/**
 * @brief Высокоуровневый контроллер
 */
class HighLevelController : public ControllerProvider {
private:
    University* university_{nullptr};
    ITableView* view_{nullptr};
    
    /// Подсчитать количество двоек у студента
    int countFailures(const Student* student) const;

public:
    HighLevelController(University* university, ITableView* view);
    ~HighLevelController() override = default;

    void applyStudentAdmission(const std::string& groupID, const std::string& fullname, int gradeCount) override;
    void transitionStudentCourse(const std::string& groupID,const std::string& fullname, int newGradeCount) override;
    void semesterControl(const std::string& groupID) override;
    double averageGroupGrade(const std::string& groupID) override;
    std::vector<std::shared_ptr<Student>> laggingStudents(const std::string& groupID = "") override;
};

#endif

