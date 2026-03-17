#include "ConsoleUI.h"
#include "StudentService.h"
#include "CourseService.h"
#include "StudentRepository.h"
#include "CourseRepository.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // 2. Tell the Windows Console to use UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    StudentRepository studentRepo;
    CourseRepository courseRepo;

    CourseService courseService(courseRepo);
    StudentService studentService(studentRepo, courseService);

    ConsoleUI ui(studentService, courseService);
    ui.start();

    return 0;
}