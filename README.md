# Student Course Management System (SCMS)

![App Screenshot](Student%20Course%20Management%20System/images/Screenshot%202026-03-28%20183849.png)

## Description
The Student Course Management System (SCMS) is a robust, console-based C++ application designed to manage student records and course enrollments. Built using advanced Object-Oriented Programming (OOP) principles, the Standard Template Library (STL), and a decoupled layered architecture, this system provides a highly responsive and visually appealing Command Line Interface (CLI) for educational administrators. 

## Features
* **Full CRUD Operations:** Add, remove, search, and display students and courses.
* **Smart Enrollments:** Enroll students in courses, automatically preventing duplicate enrollments using `std::set`.
* **Advanced Sorting:** Rank students by GPA in descending order using STL algorithms.
* **Persistent Storage:** Data is saved to and loaded from local text files (`students.txt`, `courses.txt`) utilizing a custom Repository pattern.
* **Bulletproof Input Validation:** The UI gracefully handles invalid data types, ensuring the application never crashes from bad user input.
* **Premium CLI:** Features ANSI color coding, dynamic tabular formatting, and simulated network delays for a professional user experience.

## Architecture & System Design

### System Architecture Flowchart
This project utilizes a decoupled N-Tier architecture (Data Access, Business Logic, and Presentation layers) to ensure the Single Responsibility Principle.
![System Architecture Flowchart](Student%20Course%20Management%20System/images/Untitled%20diagram-2026-03-28-163806.png)

### UML Class Diagram
The core data models utilize inheritance, encapsulation, and composition to represent the university's entities effectively.
![UML Class Diagram](Student%20Course%20Management%20System/images/Untitled%20diagram-2026-03-28-163722.png)

## Requirements
* **Compiler:** Any C++ compiler supporting the **C++17 standard** (e.g., GCC, Clang, MSVC).
* **Environment:** Windows, macOS, or Linux terminal supporting ANSI escape codes.
* **Build System (Optional):** CMake (if utilizing a `CMakeLists.txt` file).


## Usage
Upon running the application, you will be greeted by the main menu. Enter a number between 1 and 8 to navigate the system. The system will guide you through prompts for data entry (e.g., ID, Name, GPA) and will alert you if input constraints (like a GPA outside of 0.0 - 4.0) are violated.