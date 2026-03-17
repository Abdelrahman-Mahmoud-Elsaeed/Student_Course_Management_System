#include "CourseService.h"

CourseService::CourseService(const CourseRepository& repo) : courseRepo(repo) {}

bool CourseService::addCourse(const std::string& code, const std::string& name) {
    auto courses = courseRepo.getAllCourses().value_or(std::vector<Course>());
    for (const auto& c : courses) {
        if (c.getCourseCode() == code) {
            return false; // Course already exists
        }
    }
    courseRepo.addCourse(Course(code, name));
    return true;
}

std::optional<Course> CourseService::getCourseByCode(const std::string& code) const {
    auto courses = courseRepo.getAllCourses().value_or(std::vector<Course>());
    for (const auto& c : courses) {
        if (c.getCourseCode() == code) {
            return c;
        }
    }
    return std::nullopt;
}

std::vector<Course> CourseService::getAllCourses() const {
    return courseRepo.getAllCourses().value_or(std::vector<Course>());
}