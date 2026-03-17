#include <iostream>
#include <vector>

// Include your headers (adjust paths if they are inside folders like include/models/)
#include "StudentRepository.h"
#include "CourseRepository.h"
#include "Student.h"
#include "Course.h"

using namespace std;

int main() {
    cout << "=== Starting System Tests ===\n\n";

    // 1. Initialize Repositories
    StudentRepository studentRepo;
    CourseRepository courseRepo;

    // Clear previous data to ensure a fresh test run every time
    studentRepo.clearAll();
    courseRepo.clearAll();

    // ==========================================
    // TEST 1: Course Repository
    // ==========================================
    cout << "--- Testing CourseRepository ---\n";
    Course c1("CS101", "Introduction to C++");
    Course c2("MATH201", "Calculus I");

    cout << "Adding courses to file...\n";
    courseRepo.addCourse(c1);
    courseRepo.addCourse(c2);

    cout << "Reading courses from file:\n";
    auto allCoursesOpt = courseRepo.getAllCourses();
    if (allCoursesOpt.has_value()) {
        for (const auto& c : allCoursesOpt.value()) {
            cout << " - [" << c.getCourseCode() << "] " << c.getCourseName() << "\n";
        }
    }

    // ==========================================
    // TEST 2: Student Repository
    // ==========================================
    cout << "\n--- Testing StudentRepository ---\n";

    vector<string> s1_courses = { "CS101" };
    vector<string> s2_courses = { "MATH201" };

    // Student(name, age, id, gender, phone, email, level, major, gpa, courses)
    Student s1("Ahmed Ali", 20, 1001, "Male", "01012345678", "ahmed@edu.com", 2, "Computer Science", 3.8, s1_courses);
    Student s2("Sara Khan", 21, 1002, "Female", "01198765432", "sara@edu.com", 3, "Engineering", 3.5, s2_courses);

    cout << "Adding students to file...\n";
    studentRepo.addStudent(s1);
    studentRepo.addStudent(s2);

    cout << "Reading students from file:\n";
    auto allStudentsOpt = studentRepo.getAllStudents();
    if (allStudentsOpt.has_value()) {
        for (const auto& s : allStudentsOpt.value()) {
            cout << " - " << s.getName() << " (ID: " << s.getId() << ") | Major: " << s.getMajor() << " | GPA: " << s.getGpa() << "\n";
            cout << "   Enrolled in: ";
            for (const auto& courseCode : s.getCourses()) {
                cout << courseCode << " ";
            }
            cout << "\n";
        }
    }

    // ==========================================
    // TEST 3: Update and Delete Operations
    // ==========================================
    cout << "\n--- Testing Update & Delete ---\n";

    cout << "Updating Student at index 0 (Ahmed getting a 4.0 GPA and adding a course)...\n";
    Student s1_updated("Ahmed Ali", 20, 1001, "Male", "01012345678", "ahmed@edu.com", 2, "Computer Science", 4.0, { "CS101", "MATH201" });
    studentRepo.updateStudent(0, s1_updated);

    cout << "Deleting Course at index 1 (MATH201)...\n";
    courseRepo.deleteCourse(1);

    // ==========================================
    // TEST 4: Final Verification
    // ==========================================
    cout << "\n--- Final Data State ---\n";

    cout << "Remaining Courses:\n";
    auto finalCoursesOpt = courseRepo.getAllCourses();
    if (finalCoursesOpt.has_value()) {
        for (const auto& c : finalCoursesOpt.value()) {
            cout << " - " << c.getCourseCode() << "\n";
        }
    }

    cout << "\nFinal Students List:\n";
    auto finalStudentsOpt = studentRepo.getAllStudents();
    if (finalStudentsOpt.has_value()) {
        for (const auto& s : finalStudentsOpt.value()) {
            cout << " - " << s.getName() << " | New GPA: " << s.getGpa() << " | Courses count: " << s.getCourses().size() << "\n";
        }
    }

    cout << "\n=== Tests Completed! ===\n";
    return 0;
}