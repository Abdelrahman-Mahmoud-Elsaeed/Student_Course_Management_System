#include "StudentService.h"
#include <iostream>
#include <algorithm>

StudentService::StudentService(const StudentRepository& sRepo, const CourseService& cService)
    : studentRepo(sRepo), courseService(cService) {
}

bool StudentService::addStudent(const std::string& name, int age, int id, const std::string& gender,
    const std::string& phone, const std::string& email, int level,
    const std::string& major, double gpa) {
    if (gpa < 0.0 || gpa > 4.0) {
        std::cout << "Error: GPA must be between 0.0 and 4.0\n";
        return false;
    }

    auto students = studentRepo.getAllStudents().value_or(std::vector<Student>());
    auto it = std::find_if(students.begin(), students.end(),
        [id](const Student& s) { return s.getId() == id; });

    if (it != students.end()) {
        std::cout << "Error: Student ID must be unique.\n";
        return false;
    }

    studentRepo.addStudent(Student(name, age, id, gender, phone, email, level, major, gpa, {}));
    return true;
}

bool StudentService::removeStudent(int id) {
    auto students = studentRepo.getAllStudents().value_or(std::vector<Student>());
    auto it = std::find_if(students.begin(), students.end(),
        [id](const Student& s) { return s.getId() == id; });

    if (it != students.end()) {
        size_t index = std::distance(students.begin(), it);
        studentRepo.deleteStudent(index);
        return true;
    }
    return false;
}

std::optional<Student> StudentService::searchStudent(int id) const {
    auto students = studentRepo.getAllStudents().value_or(std::vector<Student>());
    auto it = std::find_if(students.begin(), students.end(),
        [id](const Student& s) { return s.getId() == id; });

    if (it != students.end()) return *it;
    return std::nullopt;
}

std::vector<Student> StudentService::getAllStudents() const {
    return studentRepo.getAllStudents().value_or(std::vector<Student>());
}

bool StudentService::enrollStudentInCourse(int studentId, const std::string& courseCode) {
    auto students = studentRepo.getAllStudents().value_or(std::vector<Student>());

    auto it = std::find_if(students.begin(), students.end(),
        [studentId](const Student& s) { return s.getId() == studentId; });

    if (it == students.end()) {
        std::cout << "Error: Student not found.\n";
        return false;
    }

    if (!courseService.getCourseByCode(courseCode).has_value()) {
        std::cout << "Error: Course does not exist in the system.\n";
        return false;
    }

    Student updatedStudent = *it;
    updatedStudent.enrollCourse(courseCode);

    size_t index = std::distance(students.begin(), it);
    studentRepo.updateStudent(index, updatedStudent);
    return true;
}

std::vector<Student> StudentService::getStudentsSortedByGPA() const {
    auto students = studentRepo.getAllStudents().value_or(std::vector<Student>());
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getGpa() > b.getGpa();
        });
    return students;
}