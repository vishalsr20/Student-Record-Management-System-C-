#include <iostream>
#include <limits>
#include "Database.h"

int readInt(const std::string &prompt) {
    int x;
    while (true) {
        std::cout << prompt;
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid number. Try again.\n";
        }
    }
}

int main() {
    Database db;
    db.loadFromFile();

    while (true) {
        std::cout << "\n--- Student Record Management System ---\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Display All Students\n";
        std::cout << "3. Search Student\n";
        std::cout << "4. Update Student\n";
        std::cout << "5. Delete Student\n";
        std::cout << "6. Exit\n";
        int choice = readInt("Enter choice: ");

        if (choice == 1) {
            int roll = readInt("Enter roll: ");
            if (db.existsRoll(roll)) {
                std::cout << "Roll already exists. Aborting add.\n";
                continue;
            }
            std::string name, course;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            if (name.empty()) { std::cout << "Name cannot be empty.\n"; continue; }
            std::cout << "Enter course: ";
            std::getline(std::cin, course);
            if (course.empty()) { std::cout << "Course cannot be empty.\n"; continue; }

            db.addStudent(Student(roll, name, course));
        } else if (choice == 2) {
            db.displayAll();
        } else if (choice == 3) {
            int roll = readInt("Enter roll to search: ");
            db.searchStudent(roll);
        } else if (choice == 4) {
            int roll = readInt("Enter roll to update: ");
            db.updateStudent(roll);
        } else if (choice == 5) {
            int roll = readInt("Enter roll to delete: ");
            db.deleteStudent(roll);
        } else if (choice == 6) {
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
