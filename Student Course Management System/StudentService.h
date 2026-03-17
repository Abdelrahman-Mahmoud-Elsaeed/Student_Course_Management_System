#pragma once
#include "StudentRepository.h"
#include "CourseService.h"
#include "Student.h"
#include <vector>
#include <optional>
#include <string>

class StudentService {
private:
    StudentRepository studentRepo;
    CourseService courseService;

public:
    StudentService(const StudentRepository& sRepo, const CourseService& cService);

    bool addStudent(const std::string& name, int age, int id, const std::string& gender,
        const std::string& phone, const std::string& email, int level,
        const std::string& major, double gpa);

    bool removeStudent(int id);
    std::optional<Student> searchStudent(int id) const;
    std::vector<Student> getAllStudents() const;
    bool enrollStudentInCourse(int studentId, const std::string& courseCode);
    std::vector<Student> getStudentsSortedByGPA() const;
};