#pragma once

#include <string>
#include <vector>
#include <optional>
#include "Student.h"
#include "FileManager.h"



class StudentRepository {
private:
    std::string filePath = "./data/students.txt";
    FileManager fileManager;

public:
    StudentRepository();

    std::optional<Student> getStudent(size_t index) const;
    std::optional< std::vector<Student> > getAllStudents() const;

    void addStudent(const Student& student);
    void updateStudent(size_t index, const Student& student);
    void deleteStudent(size_t index);

    void clearAll();
};