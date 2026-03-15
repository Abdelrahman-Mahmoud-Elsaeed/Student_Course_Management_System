#include "Course.h"

Course::Course() : courseCode(""), courseName("") {}

Course::Course(const std::string& code, const std::string& name)
    : courseCode(code), courseName(name) {
}

std::string Course::getCourseCode() const { return courseCode; }
std::string Course::getCourseName() const { return courseName; }

bool Course::operator<(const Course& other) const {
    return this->courseCode < other.courseCode;
}

bool Course::operator==(const Course& other) const {
    return this->courseCode == other.courseCode;
}