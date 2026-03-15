#pragma once

#include <string>
#include <vector>
#include <optional>
#include "Student.h"
#include "FileManager.h"



class StudentsRepo {
private:
    std::string filePath;
    FileManager fileManager;

public:
    StudentsRepo(const std::string& path);

    std::optional<Student> getStudent(size_t index) const;
    std::vector<Student> getAllStudents() const;

    void addStudent(const Student& student);
    void updateStudent(size_t index, const Student& student);
    void deleteStudent(size_t index);

    void clearAll();
};