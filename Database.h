#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Database {
public:
    vector<Student> students;

    void loadFromFile();
    void saveToFile() const;
    bool addStudent(const Student &s);
    void displayAll() const;
    bool searchStudent(int roll) const;
    bool deleteStudent(int roll);
    bool updateStudent(int roll);
    bool existsRoll(int roll) const;
};

#endif 
