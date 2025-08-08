#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>

using namespace std;

class Course;

class Student {
   public:
      // Constructor
      Student(string studentID, string studentName);
      Student();

      // Member functions
      void SetStudentID();
      void SetName();
      void AddCourse(string courseCode, bool silent = false);
      void DropCourse(string courseCode, bool silent = false);
      bool HasCourse(string courseCourse);
      void PrintStudentInfo(map<string, Course> courseRegistry);
      void PrintStudentSummary();

      // Overriding Functions
      bool operator<(const Student& other) const {
         return id < other.id;
      }

      // Member variables
      string id;
      string name;
      set<string> enrollments;
};

#endif