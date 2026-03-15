#include "Student.h"
#include <iostream>

Student::Student() {}

Student::Student(const std::string& name, int age, int id, const std::string& gender,
    const std::string& phone,
    const std::string& email,
    int level,
    const std::string& major,
    double gpa,
    const std::vector<std::string>& courses)
    : User(name, age, id, gender, phone, email),
    _level(level),
    _major(major),
    _gpa(gpa),
    _courses(courses)
{
}

void Student::enrollCourse(const std::string& course) {
    _courses.push_back(course);
};

void Student::dropCourse(const std::string& course) {
    for (auto it = _courses.begin(); it != _courses.end(); ++it) {
        if (*it == course) {
            _courses.erase(it);
            break;
        }
    }
}

void Student::displayCourses() const {
    for (size_t i = 0; i < _courses.size(); i++)
    {
        std::cout << _courses[i] << " ";
    }
    std::cout << "\n";
};

void Student::display() const  {
    User::display();
    std::cout
        << "Year: " << _level << "\n"
        << "Major: " << _major << "\n"
        << "GPA: " << _gpa << "\n";
    displayCourses();
};