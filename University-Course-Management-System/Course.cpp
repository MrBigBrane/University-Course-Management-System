#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <cstdlib>
#include "Student.h"
#include "Course.h"

using namespace std;

// Constructor used for parsing .txt files
Course::Course(string courseCode, string courseInstructor, string courseTitle) {
   code = courseCode;
   instructor = courseInstructor;
   title = courseTitle;
   maxSize = 8;
}

Course::Course() {
   code = "";
   instructor = "";
   title = "";
   maxSize = 0;
}

// Sets the course code
void Course::SetCourseCode() {
   cout << "Generating a randomly generated course code..." << endl;
   for (int i = 0; i < 5; ++i) {
      code += to_string(rand() % 10);
   }
   cout << "Code Generated: " << code << endl;
}

// Sets the course title
void Course::SetCourseTitle() {
   cout << "Please type the title of this course: ";
   getline(cin, title);
   cout << "Successfully set title of this course" << endl;
}

// Sets the course instructor
void Course::SetCourseInstructor() {
   cout << "Please type the full name of this course's instructor: ";
   getline(cin, instructor);
   cout << "Successfully set name of this course's instructor" << endl;
}

// Adds a student to the course based on student id
void Course::AddStudent(string studentID, bool silent) {
   if(studentList.find(studentID) != studentList.end()) {
      cout << studentID << " Error: This student is already enrolled in " << title << endl;
   }
   else if(studentList.size() <= 8) { // Check if course capacity has been reached
      auto studentAdd = studentList.insert(studentID);
      if(studentAdd.second) {
         if(!silent) {
            cout << "Successfully enrolled student in " << title << endl;
         }
      }
      else {
         cout << studentID << " Error: Could not add student to " << title << endl;
      }
   }
   else { // If course capacity is reached then the student is added to the waitlist
      waitlist.push(studentID);
   }
}

// Drop student based on studentID
void Course::DropStudent(string studentID, bool silent) {
   auto studentExists = studentList.find(studentID);
   queue<string> copyWaitlist;
   int size = waitlist.size();
   bool found = false;
   for(int i = 0; i < size; ++i) { // Check to see if the student is on the waitlist
      if(waitlist.front() == studentID) {
         found = true;
      }
      else {
         copyWaitlist.push(waitlist.front());
         waitlist.pop();
      }
   }
   waitlist = copyWaitlist; // waitlist queue is updated to not contain studentID if it was there previously

   if(found) { // If on the waitlist, nothing else needs to be done
      if(!silent) {
         cout << "Successfully removed " << studentID << " from the waitlist." << endl;
      }
   }
   else if(studentExists != studentList.end()) { // If not on waitlist, check to see if the student is enrolled in the course
      studentList.erase(studentID);
      if(!silent) {
      cout << "Successfully dropped " << studentID << " from " << title << endl;
      }

      if(waitlist.size() > 0) { // If the waitlist exists, the first student on the waitlist can replace the student who dropped the course
         studentList.insert(waitlist.front());
         waitlist.pop();
      }
   }
   else { // This student is not affiliated with the course
      cout << studentID << "is not currently enrolled in this course." << endl;
   }
}

bool Course::HasStudent(string studentID) { // Check if this course has a student taking it specific by studentID
   auto studentExists = studentList.find(studentID);
   if(studentExists != studentList.end()) {
      return true;
   }
   else {
      return false;
   }
}

void Course::PrintCourseInfo(map<string, Student> studentRegistry) {
   queue<string> copyWaitlist = waitlist;
   
   cout << "Course Title: " << title << endl;
   cout << "Course Instructor: " << instructor << endl;
   cout << "Course Code: " << code << endl;
   cout << "Students Registered:" << endl;
   for(auto studentID : studentList) {
      studentRegistry.at(studentID).PrintStudentSummary();
   }
   cout << "Waitlist: " << endl;
   for(int i = 0; i < waitlist.size(); ++i) {
      studentRegistry.at(copyWaitlist.front()).PrintStudentSummary();
      copyWaitlist.pop();
   }
}

void Course::PrintCourseSummary() {
   cout << "Course Title: " << title;
   cout << ", Course Instructor: " << instructor;
   cout << ", Course Code: " << code << endl;
}