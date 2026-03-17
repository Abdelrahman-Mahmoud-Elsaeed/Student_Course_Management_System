#include "StudentRepository.h"


StudentRepository::StudentRepository()
    : fileManager() {}

std::optional<Student> StudentRepository::getStudent(size_t index) const {
    auto lineOpt = fileManager.readLine(filePath, index);

    if (lineOpt.has_value()) {
        try {
            const std::string& line = lineOpt.value();
            Student s = Student::fromString(line);
            return s;
        }
        catch (...) {
            return std::nullopt;
        }
    }
    return std::nullopt;
}

std::optional<std::vector<Student>> StudentRepository::getAllStudents() const {
    auto linesOpt = fileManager.readAllLines(filePath);

    if (!linesOpt.has_value()) return std::nullopt;

    try {
        std::vector<Student> students;
        for (const auto& line : linesOpt.value()) {
            students.push_back(Student::fromString(line));
        }
        return students;
    }
    catch (...) {
        return std::nullopt;
    }
}

void StudentRepository::addStudent(const Student& student) {
    std::string line = student.toString();
    fileManager.appendLine(filePath, line);
}

void StudentRepository::updateStudent(size_t index, const Student& student) {
    std::string newLine = student.toString();
    fileManager.writeLine(filePath, index, newLine);
};

void StudentRepository::deleteStudent(size_t index) {
    auto linesOpt = fileManager.readAllLines(filePath);
    if (!linesOpt.has_value()) return;
    auto lines = linesOpt.value();
    if (index >= lines.size()) return;
    lines.erase(lines.begin() + index);
    fileManager.writeAllLines(filePath, lines);
}

void StudentRepository::clearAll() {
   fileManager.clearFile(filePath);
};