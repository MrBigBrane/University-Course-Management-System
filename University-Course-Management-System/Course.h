#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <queue>
#include <map>

using namespace std;

class Student;

class Course {
   public:
      // Constructor
      Course();
      Course(string courseCode, string courseInstructor, string courseTitle);

      // Member functions
      void SetCourseTitle();
      void SetCourseCode();
      void SetCourseInstructor();
      void AddStudent(string studentID, bool silent = false);
      void DropStudent(string studentID, bool silent = false);
      bool HasStudent(string studentID);
      void PrintCourseInfo(map<string, Student> studentRegistry);
      void PrintCourseSummary();

      // Overriding Functions
      bool operator<(const Course& other) const {
         return code < other.code;
      }

      // Member variables
      string title;
      string code;
      string instructor;
      int maxSize;
      set<string> studentList;
      queue<string> waitlist;
};

#endif