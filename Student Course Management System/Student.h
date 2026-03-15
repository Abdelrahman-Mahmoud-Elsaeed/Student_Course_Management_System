#pragma once
#include "User.h"
#include <vector>

class Student : User
{
private:
	int _level;
	std::string _major;
	double _gpa;
	std::vector<std::string> _courses;
public:
    Student();
    Student(const std::string& name, int age, int id, const std::string& gender,
        const std::string& phone,
        const std::string& email,
        int level,
        const std::string& major,
        double gpa,
        const std::vector<std::string>& courses);
    ~Student();

    void enrollCourse(const std::string& course);
    void dropCourse(const std::string& course);
    void displayCourses() const;
    void display() const override;

};
