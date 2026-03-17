#pragma once

#include <string>
#include <vector>
#include <optional>
#include "Course.h"
#include "FileManager.h"



class CourseRepository {
private:
    std::string filePath = "./data/courses.txt";
    FileManager fileManager;

public:
    CourseRepository();

    std::optional<Course> getCourse(size_t index) const;
    std::optional< std::vector<Course> > getAllCourses() const;

    void addCourse(const Course& course);
    void updateCourse(size_t index, const Course& course);
    void deleteCourse(size_t index);

    void clearAll();
};