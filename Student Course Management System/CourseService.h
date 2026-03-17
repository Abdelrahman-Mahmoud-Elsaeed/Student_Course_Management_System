#pragma once
#include "CourseRepository.h"
#include "Course.h"
#include <vector>
#include <optional>
#include <string>

class CourseService {
private:
    CourseRepository courseRepo;

public:
    CourseService(const CourseRepository& repo);

    bool addCourse(const std::string& code, const std::string& name);
    std::optional<Course> getCourseByCode(const std::string& code) const;
    std::vector<Course> getAllCourses() const;
};