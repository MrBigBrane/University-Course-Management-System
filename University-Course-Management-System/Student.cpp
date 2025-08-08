#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <cstdlib>
#include "Student.h"
#include "Course.h"

using namespace std;

// Constructor for parsing txt files
Student::Student(string studentID, string studentName) {
   id = studentID;
   name = studentName;
}

Student::Student() {
   id = "";
   name = "";
}

// Sets the student id
void Student::SetStudentID() {
   cout << "Generating a randomly generated student id..." << endl;
   for (int i = 0; i < 10; ++i) {
      id += to_string(rand() % 10);
   }
   cout << "ID Generated: " << id << endl;
}

// Sets the student's name
void Student::SetName() {
   cout << "Please type the full name of this student: ";
   getline(cin, name);
   cout << "Successfully set name of this student" << endl;
}

// Adds the course specific to courseCode
void Student::AddCourse(string courseCode, bool silent) {
   auto courseAdd = enrollments.insert(courseCode);
   if(courseAdd.second) {
      if(!silent) { // Silent variable is added for cases like parsing files or adding a course to the student object and the student to the course object to prevent long streams of output messages
         cout << "Successfully enrolled " << name << " in course " << courseCode << endl;
      }
   }
   else {
      cout << "Error: This student is already enrolled in " << courseCode << endl;
   }
}

// Removes course specific to courseCode
void Student::DropCourse(string courseCode, bool silent) {
   auto courseExists = enrollments.find(courseCode);
   if(courseExists != enrollments.end()) {
      enrollments.erase(courseCode);
      if(!silent) {
      cout << "Successfully unenrolled " << name << " from " << courseCode << endl;
      }
   }
   else {
      cout << name << "is not currently enrolled in this course." << endl;
   }
}

// Checks if the student is taking the course specific by courseCode
bool Student::HasCourse(string courseCode) {
   auto courseExists = enrollments.find(courseCode);
   if(courseExists != enrollments.end()) {
      return true;
   }
   else {
      return false;
   }
}

void Student::PrintStudentInfo(map<string, Course> courseRegistry) {
   cout << "Student ID: " << id << endl;
   cout << "Name: " << name << endl;
   cout << "Registered Courses: " << endl;
   for(auto courseCode : enrollments) {
      courseRegistry.at(courseCode).PrintCourseSummary();
   }
}

void Student::PrintStudentSummary() {
   cout << "Student ID: " << id;
   cout << ", Name: " << name << endl;
}


