#include "Course.h"
#include <sstream>

Course::Course() : courseCode(""), courseName("") {}
Course::Course(const std::string& code, const std::string& name)
    : courseCode(code), courseName(name) {
}

std::string Course::getCourseCode() const { return courseCode; }
std::string Course::getCourseName() const { return courseName; }

bool Course::operator<(const Course& other) const {
    return courseCode < other.courseCode;
}

bool Course::operator==(const Course& other) const {
    return courseCode == other.courseCode;
}

std::string Course::toString() const {
    return courseCode + "|" + courseName;
}

Course Course::fromString(const std::string& line) {
    std::istringstream iss(line);
    std::string code, name;

    std::getline(iss, code, '|');
    std::getline(iss, name, '|');

    return Course(code, name);
}