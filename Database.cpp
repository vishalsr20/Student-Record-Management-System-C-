#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

// File format: roll|name|course
void Database::loadFromFile() {
    students.clear();
    std::ifstream file("students.txt");
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string token;
        int roll = 0;
        std::string name, course;

        if (std::getline(ss, token, '|')) {
            try {
                roll = std::stoi(token);
            } catch (...) { continue; }
            if (std::getline(ss, name, '|')) {
                if (std::getline(ss, course)) {
                    students.push_back(Student(roll, name, course));
                }
            }
        }
    }
    file.close();
}

void Database::saveToFile() const {
    std::ofstream file("students.txt");
    for (const auto &s : students) {
        file << s.roll << '|' << s.name << '|' << s.course << '\n';
    }
    file.close();
}

bool Database::existsRoll(int roll) const {
    for (const auto &s : students) if (s.roll == roll) return true;
    return false;
}

bool Database::addStudent(const Student &s) {
    if (existsRoll(s.roll)) {
        std::cout << "A student with roll " << s.roll << " already exists.\n";
        return false;
    }
    students.push_back(s);
    saveToFile();
    std::cout << "Student added successfully.\n";
    return true;
}

void Database::displayAll() const {
    if (students.empty()) {
        std::cout << "No records found.\n";
        return;
    }
    for (const auto &s : students) s.display();
}

bool Database::searchStudent(int roll) const {
    for (const auto &s : students) {
        if (s.roll == roll) {
            s.display();
            return true;
        }
    }
    std::cout << "Student not found.\n";
    return false;
}

bool Database::deleteStudent(int roll) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].roll == roll) {
            students.erase(students.begin() + i);
            saveToFile();
            std::cout << "Record deleted.\n";
            return true;
        }
    }
    std::cout << "Student not found.\n";
    return false;
}

bool Database::updateStudent(int roll) {
    for (auto &s : students) {
        if (s.roll == roll) {
            std::cout << "Enter new name: ";
            std::string name;
            std::getline(std::cin, name);
            if (name.empty()) {
                std::cout << "Name cannot be empty. Update cancelled.\n";
                return false;
            }
            std::cout << "Enter new course: ";
            std::string course;
            std::getline(std::cin, course);
            if (course.empty()) {
                std::cout << "Course cannot be empty. Update cancelled.\n";
                return false;
            }
            s.name = name;
            s.course = course;
            saveToFile();
            std::cout << "Record updated.\n";
            return true;
        }
    }
    std::cout << "Student not found.\n";
    return false;
}
