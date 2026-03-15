#pragma once
#include <string>

class Course {
private:
    std::string courseCode;
    std::string courseName;

public:
    Course();
    Course(const std::string& code, const std::string& name);

    std::string getCourseCode() const;
    std::string getCourseName() const;

    bool operator<(const Course& other) const;

    bool operator==(const Course& other) const;
};