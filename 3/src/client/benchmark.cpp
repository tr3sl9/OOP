/**
 * @file benchmark.cpp
 * @brief Программа для сравнения производительности однопоточной и многопоточной обработки
 * 
 * Создает университет с заданным количеством групп и студентов,
 * затем измеряет время выполнения операций поиска отстающих студентов
 * и вычисления среднего балла в однопоточном и многопоточном режимах.
 */

#include "../repository/university.h"
#include "../repository/group.h"
#include "../model/student.h"
#include "../model/juniorStudent.h"
#include "../model/seniorStudent.h"
#include "../controller/highLevelController.h"
#include "../view/tableView.h"
#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <fstream>

/**
 * @brief Заполнить университет тестовыми данными
 * @param university Университет для заполнения
 * @param groupCount Количество групп
 * @param studentsPerGroup Количество студентов в каждой группе
 * @param gradesPerStudent Количество оценок у каждого студента
 */
void fillTestData(University* university, size_t groupCount, size_t studentsPerGroup, size_t gradesPerStudent) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> gradeDist(2, 5);
    
    std::cout << "Создание тестовых данных..." << std::endl;
    std::cout << "Групп: " << groupCount << std::endl;
    std::cout << "Студентов в группе: " << studentsPerGroup << std::endl;
    std::cout << "Оценок на студента: " << gradesPerStudent << std::endl;
    
    for (size_t g = 0; g < groupCount; ++g) {
        std::string groupID = "G" + std::to_string(g + 1);
        CategoryStudent type = (g % 2 == 0) ? CategoryStudent::JUNIOR : CategoryStudent::SENIOR;
        
        university->addGroup(groupID, static_cast<int>(gradesPerStudent), type);
        auto group = university->findGroup(groupID);
        
        if (!group) {
            continue;
        }
        
        for (size_t s = 0; s < studentsPerGroup; ++s) {
            std::string fullname = "Student_" + std::to_string(g) + "_" + std::to_string(s);
            std::shared_ptr<Student> student;
            
            if (type == CategoryStudent::JUNIOR) {
                student = std::make_shared<JuniorStudent>(fullname);
            } else {
                student = std::make_shared<SeniorStudent>(fullname);
            }
            
            for (size_t gr = 0; gr < gradesPerStudent; ++gr) {
                student->addGrade(gradeDist(gen));
            }
            
            group->addStudent(student);
        }
    }
    
    std::cout << "Тестовые данные созданы." << std::endl;
    std::cout << "Всего студентов: " << university->getTotalStudentCount() << std::endl;
    std::cout << std::endl;
}

/**
 * @brief Измерить время выполнения функции
 * @param func Функция для выполнения
 * @param name Имя операции
 * @return Время выполнения в миллисекундах
 */
template<typename Func>
double measureTime(Func func, const std::string& name) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> duration = end - start;
    double ms = duration.count();
    
    std::cout << name << ": " << std::fixed << std::setprecision(3) << ms << " мс" << std::endl;
    
    return ms;
}

/**
 * @brief Провести бенчмарк с заданными параметрами
 * @param groupCount Количество групп
 * @param studentsPerGroup Количество студентов в группе
 * @param gradesPerStudent Количество оценок у студента
 */
void runBenchmark(size_t groupCount, size_t studentsPerGroup, size_t gradesPerStudent) {
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "Бенчмарк: " << groupCount << " групп, " 
              << studentsPerGroup << " студентов, " 
              << gradesPerStudent << " оценок" << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    University university(101);
    TableDialogView view;
    HighLevelController controller(&university, &view);
    
    fillTestData(&university, groupCount, studentsPerGroup, gradesPerStudent);
    
    std::cout << "\n--- Поиск отстающих студентов ---" << std::endl;
    
    double singleThreadTime = measureTime([&controller]() {
        controller.laggingStudents("");
    }, "Однопоточный режим");
    
    double multiThreadTime = measureTime([&controller]() {
        controller.laggingStudentsMultithreaded("");
    }, "Многопоточный режим");
    
    double speedup1 = singleThreadTime / multiThreadTime;
    std::cout << "Ускорение: " << std::fixed << std::setprecision(2) 
              << speedup1 << "x" << std::endl;
}

/**
 * @brief Сохранить результаты бенчмарка в CSV файл для построения графиков
 */
void saveBenchmarkResults() {
    std::ofstream csv("benchmark_results.csv");
    csv << "GroupCount,StudentsPerGroup,TotalStudents,LaggingSingleThread,LaggingMultiThread,LaggingSpeedup\n";
    
    std::vector<std::pair<size_t, size_t>> configs = {
        {10, 10000}, 
        {10, 20000},
        {10, 30000},
        {10, 40000},
        {10, 50000},
        {10, 60000},
        {10, 75000},
        {10, 90000},
        {10, 100000},
        {10, 120000}
    };
    
    for (const auto& [groupCount, studentsPerGroup] : configs) {
        std::cout << "\n\nТестирование конфигурации: " << groupCount 
                  << " групп, " << studentsPerGroup << " студентов..." << std::endl;
        
        University university(101);
        TableDialogView view;
        HighLevelController controller(&university, &view);
        
        fillTestData(&university, groupCount, studentsPerGroup, 10);
        
        size_t totalStudents = groupCount * studentsPerGroup;
        
        double laggingSingle = 0.0;
        double laggingMulti = 0.0;
        
        auto start = std::chrono::high_resolution_clock::now();
        controller.laggingStudents("");
        auto end = std::chrono::high_resolution_clock::now();
        laggingSingle = std::chrono::duration<double, std::milli>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        controller.laggingStudentsMultithreaded("");
        end = std::chrono::high_resolution_clock::now();
        laggingMulti = std::chrono::duration<double, std::milli>(end - start).count();
        
        double laggingSpeedup = laggingSingle / laggingMulti;
        
        csv << groupCount << "," 
            << studentsPerGroup << ","
            << totalStudents << ","
            << laggingSingle << ","
            << laggingMulti << ","
            << laggingSpeedup << "\n";
        
        std::cout << "  Результат: " << laggingSingle << " мс (однопоточно) -> " << laggingMulti 
                  << " мс (многопоточно), ускорение: " << std::fixed << std::setprecision(2) 
                  << laggingSpeedup << "x" << std::endl;
    }
    
    csv.close();
    std::cout << "\n\nРезультаты сохранены в benchmark_results.csv" << std::endl;
}

/**
 * @brief Главная функция
 */
int main() {
    std::cout << "=== Программа для тестирования производительности ===" << std::endl;
    std::cout << "=== Однопоточный vs Многопоточный режим ===" << std::endl;
    std::cout << std::endl;
    
    runBenchmark(10, 30000, 10);
    runBenchmark(10, 60000, 10);
    runBenchmark(10, 100000, 15);
    

    std::cout << "\n\n=== Генерация данных для графиков ===" << std::endl;
    saveBenchmarkResults();
    
    std::cout << "\n=== Тестирование завершено ===" << std::endl;
    
    return 0;
}

