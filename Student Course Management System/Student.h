#pragma once
#include "User.h"
#include <vector>
#include <sstream>

class Student : public User
{
private:
	int _level;
	std::string _major;
	double _gpa;
	std::vector<std::string> _courses;
public:
    Student(const std::string& name, int age, int id, const std::string& gender,
        const std::string& phone,
        const std::string& email,
        int level,
        const std::string& major,
        double gpa,
        const std::vector<std::string>& courses);

    std::string toString() const;

    void enrollCourse(const std::string& course);
    void dropCourse(const std::string& course);
    static Student fromString(const std::string& line);

    void displayCourses() const;
    void display() const override;
    int getLevel() const;
    std::string getMajor() const;
    double getGpa() const;
    std::vector<std::string> getCourses() const;
};
