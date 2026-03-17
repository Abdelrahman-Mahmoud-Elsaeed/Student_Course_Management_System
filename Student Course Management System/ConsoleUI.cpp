#include "ConsoleUI.h"
#include "Student.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
#include <cstdlib>

// --- ANSI Color Codes for Premium Look ---
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";

ConsoleUI::ConsoleUI(StudentService& sService, CourseService& cService)
    : studentService(sService), courseService(cService) {
}

// ==========================================
//           UI UX ENHANCEMENTS
// ==========================================

void ConsoleUI::clearScreen() const {
#if defined(_WIN32)
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ConsoleUI::sleepFor(int milliseconds) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void ConsoleUI::printHeader(const std::string& title) const {
    clearScreen();
    std::cout << CYAN << BOLD << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════════╗\n";
    std::cout << "  ║ " << std::setw(52) << std::left << title << " ║\n";
    std::cout << "  ╚══════════════════════════════════════════════════════╝\n" << RESET << "\n";
}

void ConsoleUI::printSuccess(const std::string& message) const {
    std::cout << GREEN << "  [✔] SUCCESS: " << message << RESET << "\n";
}

void ConsoleUI::printError(const std::string& message) const {
    std::cout << RED << "  [✖] ERROR: " << message << RESET << "\n";
}

void ConsoleUI::printWarning(const std::string& message) const {
    std::cout << YELLOW << "  [!] WARNING: " << message << RESET << "\n";
}

void ConsoleUI::waitForUser() const {
    std::cout << "\n  " << MAGENTA << "Press [Enter] to return to the main menu..." << RESET;
    std::string dummy;
    std::getline(std::cin, dummy);
}

// ==========================================
//          INPUT VALIDATION
// ==========================================

int ConsoleUI::getIntInput(const std::string& prompt) const {
    int value;
    while (true) {
        std::cout << "  " << prompt << BOLD;
        if (std::cin >> value) {
            std::cout << RESET;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << RESET;
        printError("Invalid input. Please enter a whole number.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double ConsoleUI::getDoubleInput(const std::string& prompt) const {
    double value;
    while (true) {
        std::cout << "  " << prompt << BOLD;
        if (std::cin >> value) {
            std::cout << RESET;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << RESET;
        printError("Invalid input. Please enter a decimal number.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string ConsoleUI::getStringInput(const std::string& prompt) const {
    std::string value;
    std::cout << "  " << prompt << BOLD;
    std::getline(std::cin, value);
    std::cout << RESET;
    return value;
}

// ==========================================
//              MAIN MENU
// ==========================================

void ConsoleUI::start() {
    bool running = true;
    while (running) {
        clearScreen();
        std::cout << CYAN << BOLD << "\n";
        std::cout << "  ███████╗ ██████╗███╗   ███╗ ██████╗\n";
        std::cout << "  ██╔════╝██╔════╝████╗ ████║██╔════╝\n";
        std::cout << "  ███████╗██║     ██╔████╔██║███████╗\n";
        std::cout << "  ╚════██║██║     ██║╚██╔╝██║╚════██║\n";
        std::cout << "  ███████║╚██████╗██║ ╚═╝ ██║███████║\n";
        std::cout << "  ╚══════╝ ╚═════╝╚═╝     ╚═╝╚══════╝\n";
        std::cout << "  STUDENT COURSE MANAGEMENT SYSTEM\n" << RESET;
        std::cout << "  ──────────────────────────────────────────\n";
        std::cout << "  " << BOLD << "1." << RESET << " Add Student\n";
        std::cout << "  " << BOLD << "2." << RESET << " Remove Student\n";
        std::cout << "  " << BOLD << "3." << RESET << " Search Student\n";
        std::cout << "  " << BOLD << "4." << RESET << " Display All Students\n";
        std::cout << "  " << BOLD << "5." << RESET << " Enroll Student in Course\n";
        std::cout << "  " << BOLD << "6." << RESET << " Show Student Courses\n";
        std::cout << "  " << BOLD << "7." << RESET << " Sort Students by GPA\n";
        std::cout << "  " << BOLD << "8." << RESET << " Exit\n";
        std::cout << "  ──────────────────────────────────────────\n\n";

        int choice = getIntInput("Select an option (1-8): ");

        switch (choice) {
        case 1: handleAddStudent(); break;
        case 2: handleRemoveStudent(); break;
        case 3: handleSearchStudent(); break;
        case 4: handleDisplayAllStudents(); break;
        case 5: handleEnrollStudent(); break;
        case 6: handleShowStudentCourses(); break;
        case 7: handleSortStudents(); break;
        case 8:
            clearScreen();
            std::cout << "\n  " << GREEN << BOLD << "Saving Data...\n" << RESET;
            sleepFor(600);
            std::cout << "  " << CYAN << "System Offline. Goodbye!\n\n" << RESET;
            running = false;
            break;
        default:
            printError("Invalid choice. Please select a number between 1 and 8.");
            sleepFor(1500);
        }
    }
}

// ==========================================
//           ACTION HANDLERS
// ==========================================

void ConsoleUI::handleAddStudent() {
    printHeader("ADD NEW DETAILED STUDENT");

    int id = getIntInput("Enter Student ID: ");
    if (studentService.searchStudent(id).has_value()) {
        printError("A student with ID " + std::to_string(id) + " already exists.");
        waitForUser();
        return;
    }

    std::string name = getStringInput("Enter Full Name: ");
    int age = getIntInput("Enter Age: ");
    std::string gender = getStringInput("Enter Gender (Male/Female): ");
    std::string phone = getStringInput("Enter Phone Number: ");
    std::string email = getStringInput("Enter Email Address: ");
    int level = getIntInput("Enter Academic Level/Year (e.g., 1, 2, 3): ");
    std::string major = getStringInput("Enter Major: ");

    double gpa;
    while (true) {
        gpa = getDoubleInput("Enter GPA (0.0 - 4.0): ");
        if (gpa >= 0.0 && gpa <= 4.0) break;
        printError("GPA must be strictly between 0.0 and 4.0.");
    }

    std::cout << "\n  " << YELLOW << "Registering complete student profile in database..." << RESET << "\n";
    sleepFor(500);

    if (studentService.addStudent(name, age, id, gender, phone, email, level, major, gpa)) {
        printSuccess("Student '" + name + "' registered successfully.");
    }
    else {
        printError("Failed to register student.");
    }
    waitForUser();
}

void ConsoleUI::handleRemoveStudent() {
    printHeader("REMOVE STUDENT");
    int id = getIntInput("Enter Student ID to remove: ");

    std::cout << "\n  " << YELLOW << "Searching database..." << RESET << "\n";
    sleepFor(400);

    if (studentService.removeStudent(id)) {
        printSuccess("Student with ID " + std::to_string(id) + " was removed permanently.");
    }
    else {
        printError("Student with ID " + std::to_string(id) + " not found.");
    }
    waitForUser();
}

void ConsoleUI::handleSearchStudent() {
    printHeader("SEARCH STUDENT");
    int id = getIntInput("Enter Student ID to search: ");

    std::cout << "\n  " << YELLOW << "Querying database..." << RESET << "\n";
    sleepFor(400);

    auto studentOpt = studentService.searchStudent(id);
    if (studentOpt.has_value()) {
        printSuccess("Student Record Found:");
        std::cout << "\n  " << BOLD << "ID:      " << RESET << studentOpt.value().getId();
        std::cout << "\n  " << BOLD << "Name:    " << RESET << studentOpt.value().getName();
        std::cout << "\n  " << BOLD << "GPA:     " << RESET << std::fixed << std::setprecision(2) << studentOpt.value().getGpa();
        std::cout << "\n  " << BOLD << "Courses: " << RESET << studentOpt.value().getCourses().size() << " enrolled\n";
    }
    else {
        printError("Student with ID " + std::to_string(id) + " not found.");
    }
    waitForUser();
}

void ConsoleUI::handleDisplayAllStudents() {
    printHeader("SYSTEM ROSTER - ALL REGISTERED STUDENTS");
    auto students = studentService.getAllStudents();

    if (students.empty()) {
        printWarning("No students are currently registered in the system.");
    }
    else {
        std::cout << "  " << BOLD << std::left
            << std::setw(10) << "ID"
            << std::setw(30) << "Name"
            << std::setw(10) << "GPA"
            << "Courses" << RESET << "\n";
        std::cout << "  ──────────────────────────────────────────────────────────────\n";

        for (const auto& s : students) {
            std::cout << "  " << std::left
                << std::setw(10) << s.getId()
                << std::setw(30) << s.getName()
                << std::setw(10) << std::fixed << std::setprecision(2) << s.getGpa()
                << s.getCourses().size() << " enrolled\n";
        }
        std::cout << "  ──────────────────────────────────────────────────────────────\n";
        std::cout << "  " << BOLD << "Total Records: " << students.size() << RESET << "\n";
    }
    waitForUser();
}

void ConsoleUI::handleEnrollStudent() {
    printHeader("ENROLL IN COURSE");
    int id = getIntInput("Enter Student ID: ");

    if (!studentService.searchStudent(id).has_value()) {
        printError("Student with ID " + std::to_string(id) + " does not exist.");
        waitForUser();
        return;
    }

    std::string courseCode = getStringInput("Enter Course Code (e.g., CS101): ");

    std::cout << "\n  " << YELLOW << "Validating enrollment..." << RESET << "\n";
    sleepFor(500);

    // Auto-create course for ease of assignment testing
    if (!courseService.getCourseByCode(courseCode).has_value()) {
        printWarning("Course " + courseCode + " not in catalog. Auto-creating...");
        courseService.addCourse(courseCode, "New Course");
    }

    if (studentService.enrollStudentInCourse(id, courseCode)) {
        printSuccess("Student " + std::to_string(id) + " successfully enrolled in " + courseCode + ".");
    }
    waitForUser();
}

void ConsoleUI::handleShowStudentCourses() {
    printHeader("STUDENT COURSE SCHEDULE");
    int id = getIntInput("Enter Student ID: ");

    auto studentOpt = studentService.searchStudent(id);
    if (studentOpt.has_value()) {
        auto courses = studentOpt.value().getCourses();
        std::cout << "\n  " << BOLD << "Schedule for: " << RESET << studentOpt.value().getName() << " (ID: " << id << ")\n";
        std::cout << "  ──────────────────────────────────────────\n";

        if (courses.empty()) {
            printWarning("Student is not enrolled in any courses.");
        }
        else {
            for (const auto& c : courses) {
                std::cout << "  " << CYAN << "► " << RESET << c << "\n";
            }
        }
        std::cout << "  ──────────────────────────────────────────\n";
    }
    else {
        printError("Student with ID " + std::to_string(id) + " not found.");
    }
    waitForUser();
}

void ConsoleUI::handleSortStudents() {
    printHeader("STUDENTS RANKED BY GPA (DESCENDING)");
    std::cout << "  " << YELLOW << "Sorting records via STL Algorithm..." << RESET << "\n\n";
    sleepFor(400);

    auto students = studentService.getStudentsSortedByGPA();

    if (students.empty()) {
        printWarning("No students available to sort.");
    }
    else {
        std::cout << "  " << BOLD << std::left
            << std::setw(10) << "Rank"
            << std::setw(10) << "ID"
            << std::setw(30) << "Name"
            << "GPA" << RESET << "\n";
        std::cout << "  ──────────────────────────────────────────────────────────────\n";

        int rank = 1;
        for (const auto& s : students) {
            // Give top student a green rank
            if (rank == 1) std::cout << GREEN;

            std::cout << "  " << std::left
                << "#" << std::setw(9) << rank++
                << std::setw(10) << s.getId()
                << std::setw(30) << s.getName()
                << std::fixed << std::setprecision(2) << s.getGpa() << "\n";

            if (rank == 2) std::cout << RESET; // Reset color after rank 1
        }
        std::cout << "  ──────────────────────────────────────────────────────────────\n";
    }
    waitForUser();
}