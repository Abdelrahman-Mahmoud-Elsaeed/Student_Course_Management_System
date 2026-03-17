#pragma once
#include "StudentService.h"
#include "CourseService.h"
#include <string>

class ConsoleUI {
private:
    StudentService& studentService;
    CourseService& courseService;

    // --- UI Enhancements ---
    void clearScreen() const;
    void sleepFor(int milliseconds) const;
    void printHeader(const std::string& title) const;
    void printSuccess(const std::string& message) const;
    void printError(const std::string& message) const;
    void printWarning(const std::string& message) const;
    void waitForUser() const;

    // --- Bulletproof Input Handlers ---
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    std::string getStringInput(const std::string& prompt) const;

    // --- Action Handlers ---
    void handleAddStudent();
    void handleRemoveStudent();
    void handleSearchStudent();
    void handleDisplayAllStudents();
    void handleEnrollStudent();
    void handleShowStudentCourses();
    void handleSortStudents();

public:
    ConsoleUI(StudentService& sService, CourseService& cService);
    void start();
};