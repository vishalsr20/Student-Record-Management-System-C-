#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include<string>
using namespace std;

class Student {
    public:
    int roll;
    string name;
    string course;

    Student() : roll(0) , name(""), course(""){}

    Student(int r, const string &n , const string &c) :  roll(r), name(n), course(c){}

    void display() const {
        cout<<"Roll: "<<roll
            <<" | Name: "<<name 
            <<" | Course: "<<course<<'\n';
    };

};
#endif
