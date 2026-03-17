#include "Student.h"
#include <iostream>
#include <sstream>

Student::Student(const std::string& name, int age, int id, const std::string& gender,
    const std::string& phone,
    const std::string& email,
    int level,
    const std::string& major,
    double gpa,
    const std::set<std::string>& courses)
    : User(name, age, id, gender, phone, email),
    _level(level),
    _major(major),
    _gpa(gpa),
    _courses(courses)
{
}

void Student::enrollCourse(const std::string& course) {
    _courses.insert(course);
}

void Student::dropCourse(const std::string& course) {
    _courses.erase(course);
}

void Student::displayCourses() const {
    for (const auto& course : _courses) {
        std::cout << course << " ";
    }
    std::cout << "\n";
}

void Student::display() const {
    User::display();
    std::cout
        << "Year: " << _level << "\n"
        << "Major: " << _major << "\n"
        << "GPA: " << _gpa << "\nEnrolled Courses: ";
    displayCourses();
}

int Student::getLevel() const { return _level; }
std::string Student::getMajor() const { return _major; }
double Student::getGpa() const { return _gpa; }

std::set<std::string> Student::getCourses() const {
    return _courses;
}

std::string Student::toString() const {
    std::ostringstream line;
    line << getId() << "|"
        << getName() << "|"
        << getAge() << "|"
        << getGender() << "|"
        << getEmail() << "|"
        << getPhone() << "|"
        << _level << "|"
        << _major << "|"
        << _gpa << "|";

    auto it = _courses.begin();
    while (it != _courses.end()) {
        line << *it;
        ++it;
        if (it != _courses.end()) {
            line << ",";
        }
    }

    return line.str();
}

Student Student::fromString(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }

    int id = std::stoi(tokens[0]);
    std::string name = tokens[1];
    int age = std::stoi(tokens[2]);
    std::string gender = tokens[3];
    std::string email = tokens[4];
    std::string phone = tokens[5];
    int level = std::stoi(tokens[6]);
    std::string major = tokens[7];
    double gpa = std::stod(tokens[8]);

    std::set<std::string> courses;
    if (tokens.size() > 9) {
        std::istringstream ciss(tokens[9]);
        std::string course;
        while (std::getline(ciss, course, ',')) {
            courses.insert(course);
        }
    }

    return Student(name, age, id, gender, phone, email, level, major, gpa, courses);
}