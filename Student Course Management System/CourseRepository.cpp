#include "CourseRepository.h"

CourseRepository::CourseRepository()
    : fileManager() {
}

std::optional<Course> CourseRepository::getCourse(size_t index) const {
    auto lineOpt = fileManager.readLine(filePath, index);
    if (lineOpt.has_value()) {
        try {
            const std::string& line = lineOpt.value();
            Course c = Course::fromString(line);
            return c;
        }
        catch (...) {
            return std::nullopt;
        }
    }
    return std::nullopt;
}

std::optional<std::vector<Course>> CourseRepository::getAllCourses() const {
    auto linesOpt = fileManager.readAllLines(filePath);
    if (!linesOpt.has_value()) return std::nullopt;

    try {
        std::vector<Course> courses;
        for (const auto& line : linesOpt.value()) {
            courses.push_back(Course::fromString(line));
        }
        return courses;
    }
    catch (...) {
        return std::nullopt;
    }
}

void CourseRepository::addCourse(const Course& course) {
    std::string line = course.toString();
    fileManager.appendLine(filePath, line);
}

void CourseRepository::updateCourse(size_t index, const Course& course) {
    std::string newLine = course.toString();
    fileManager.writeLine(filePath, index, newLine);
}

void CourseRepository::deleteCourse(size_t index) {
    auto linesOpt = fileManager.readAllLines(filePath);
    if (!linesOpt.has_value()) return;

    auto lines = linesOpt.value();
    if (index >= lines.size()) return;

    lines.erase(lines.begin() + index);
    fileManager.writeAllLines(filePath, lines);
}

void CourseRepository::clearAll() {
    fileManager.clearFile(filePath);
}