#include <iostream>
#include "Student.h"
#include "Course.h"
#include <fstream>
#include <map>
#include <deque>

using namespace std;

// Prompt function commonly used in main for asking user for a specific student's id
void StudentIDInput(string& id, map<string, Student> studentRegistry) {
  bool needInput = true;
  Student specificStudent;

  cout << "Please enter the ID of the student: ";
  while(needInput) {
    // Use a try/catch block to ensure that if the student does not exist in the registry, the program does not crash
    try {
      cin >> id;
      specificStudent = studentRegistry.at(id);
      needInput = false;

    } catch (out_of_range& e) {
      cout << "This student does not exist. Please try again: ";
    }
  }
}

// Prompt function commonly used in main for asking user for a specific course code
void CourseCodeInput(string& code, map<string, Course> courseRegistry) {
  bool needInput = true;
  Course specificCourse;

  cout << "Please enter the course code: ";

  while(needInput) {
    try {
      cin >> code;
      specificCourse = courseRegistry.at(code);
      needInput = false;

    } catch (out_of_range& e) {
      cout << "This course does not exist. Please try again: ";
    }
  }
}

int main() { 
  string userAction; // user's input
  string id; // student id
  string code; // course code
  map<string, Student> studentRegistry;
  map<string, Course> courseRegistry;

  deque<string> log;
  
  // Parsing variable
  ifstream inFS;
  
  // Course .txt
  string courseTitle;
  string courseInstructor;
  string courseCode;

  // Loading preset courses in courses.txt
  inFS.open("courses.txt");
  if (!inFS.is_open()) {
    cout << "Could not open file courses.txt." << endl;
    return 1;
  }

  // loop will store tab separated values in each variable until end of file
  // tab separated values allows grouping of variables that may contain spaces
  while (getline(inFS, courseCode, '\t')) {
    getline(inFS, courseTitle, '\t');
    getline(inFS, courseInstructor, '\n');
    Course newCourse(courseCode, courseInstructor, courseTitle);
    courseRegistry.emplace(courseCode, newCourse); // Add course to registry
    log.push_back("Course created");
  }
  if (!inFS.eof()) {
    cout << "Input failure before reaching end of file." << endl;
  }

  // Done with file, so close it
  inFS.close();
  
  cout << "Successfully loaded " << courseRegistry.size() << " courses." << endl;

  // Begin parsing of student.txt file
  string studentID;
  string studentName;
  string course1;
  string course2;
  string course3;
  string course4;

  inFS.open("students.txt");
  if (!inFS.is_open()) {
    cout << "Could not open file students.txt." << endl;
    return 1;
  }

  while (getline(inFS, studentID, '\t')) {
    getline(inFS, studentName, '\t');
    inFS >> course1;
    inFS >> course2;
    inFS >> course3;
    inFS >> course4;
    inFS.ignore();
    
    Student newStudent(studentID, studentName);
    log.push_back("Student created");
    
    newStudent.AddCourse(course1, true);
    courseRegistry.at(course1).AddStudent(studentID, true);
    log.push_back("Student registered for course");
 
    newStudent.AddCourse(course2, true);
    courseRegistry.at(course2).AddStudent(studentID, true);
    log.push_back("Student registered for course");
  
    newStudent.AddCourse(course3, true);
    courseRegistry.at(course3).AddStudent(studentID, true);
    log.push_back("Student registered for course");
  
    newStudent.AddCourse(course4, true);
    courseRegistry.at(course4).AddStudent(studentID, true);
    log.push_back("Student registered for course");
    

    studentRegistry.emplace(studentID, newStudent);
  }
  if (!inFS.eof()) {
    cout << "Input failure before reaching end of file." << endl;
  }

  // Done with file, so close it
  inFS.close();
  
  cout << "Successfully loaded " << studentRegistry.size() << " students." << endl;
  cout << "Starting program..." << endl;
  
  // Ask what the user would like to do (two possible options: view things or modify things)
  cout << "What would you like to do? (\"view\" or \"modify\"): ";
  cin >> userAction;

  while (userAction != "-1") {
    // View Branch:
    if(userAction == "view") {
  
      // List of things that can be viewed: specific student, specific course, student registry, course registry
      cout << "Type what you would like to view (\"student\", \"course\", \"log\", or \"back\"): ";
      cin >> userAction;
  
      
        // Student Branch: specific student or student registry
        if(userAction == "student") {
            cout << "Type which type of student view you would like (\"specific\", \"overall\", or \"back\"): ";
            cin >> userAction;
  
            // Specific Student: print studentinfo including id, name, and all course registrations
            if(userAction == "specific") {
              StudentIDInput(id, studentRegistry);
              studentRegistry.at(id).PrintStudentInfo(courseRegistry);
              
            }
  
            // Student Registry: print a list of all students which includes ID and name
            else if(userAction == "overall") {
                for(auto element : studentRegistry) {
                    element.second.PrintStudentSummary();
                }
            }
        }
  
        // Course Branch: specific course or course registry
        else if(userAction == "course") {
          cout << "Type which type of course view you would like (\"specific\", \"overall\", or \"back\"): ";
          cin >> userAction;
          
          // Specific Course: print courseinfo including course name, code, instructor, and all students enrolled in the course
          if(userAction == "specific") {
            CourseCodeInput(code, courseRegistry);
            courseRegistry.at(code).PrintCourseInfo(studentRegistry);
  
          }
  
          // Course Registry: print a list of all courses which includes course name, code, and instructor
          else if(userAction == "overall") {
              for(auto element : courseRegistry) {
                  element.second.PrintCourseSummary();
              }
          }
        }

        // Prints the full log
        else if(userAction == "log") {
          for(auto logItem: log) {
            cout << logItem << endl;
          }
        }
            
      }
  
    // Modify Branch:
    else if(userAction == "modify") {
      // Things that can be done: add, update, remove
      cout << "Type what you would like to do (\"add\", \"update\", \"remove\", or \"back\"): ";
      cin >> userAction;
  
        // Add: student or course
        if(userAction == "add") {
            cout << "What would you like to add? (\"student\", \"course\", or \"back\"): ";
            cin >> userAction;
            cin.ignore();
          
            // Student: create a new student
            if(userAction == "student") {
              Student newStudent;
              newStudent.SetStudentID();
              newStudent.SetName();

              // Check to see if the randomly generated id already exists (unlikely but necessary for edge cases)
              auto alreadyPresent = studentRegistry.emplace(newStudent.id, newStudent);
            
              while(!alreadyPresent.second) {
                cout << "Randomly generated student id already in use. Regenerating..." << endl;
                newStudent.SetStudentID();
                alreadyPresent = studentRegistry.emplace(newStudent.id, newStudent);
              }

              log.push_back("Student created");
  
              cout << "Student successfully added to registry." << endl;
            }
    
            // Course: create a new course
            if(userAction == "course") {
              Course newCourse;
              newCourse.SetCourseCode();
              newCourse.SetCourseTitle();
              newCourse.SetCourseInstructor();

              // Check to see if randomly generated course code already exists
              auto alreadyPresent = courseRegistry.emplace(newCourse.code, newCourse);

              while(!alreadyPresent.second) {
                cout << "Randomly generated course code is already in use. Regenerating..." << endl;
                newCourse.SetCourseCode();
                alreadyPresent = courseRegistry.emplace(newCourse.code, newCourse);
              }

              log.push_back("Course created");

              cout << "Course successfully added to registry." << endl;
            }
        }
        // Update: student or course
        else if(userAction == "update") {
              cout << "What would you like to update? (\"student\", \"course\", or \"back\"): ";
              cin >> userAction;
              // Pressing enter creates a new line character that needs to be ignored, otherwise the next input will take in the newline character automatically instead of the user input
              cin.ignore();
    
            // Student: update student data (name, course enrollments)
            if(userAction == "student") {
              StudentIDInput(id, studentRegistry);
              studentRegistry.at(id).PrintStudentInfo(courseRegistry);

              cout << "What would you like to update for this student? (\"name\", \"courses\", or \"back\"): ";
              cin >> userAction;
              cin.ignore();

                // Name: update name
                if(userAction == "name") {
                  studentRegistry.at(id).SetName();
                  log.push_back("Student updated");
                }
                  
                // Enrollment: Add course using course code
                else if(userAction == "courses") {
                  CourseCodeInput(code, courseRegistry);
                  courseRegistry.at(code).PrintCourseSummary();

                  // Must update both student and course object
                  courseRegistry.at(code).AddStudent(id, true);
                  studentRegistry.at(id).AddCourse(code);

                  log.push_back("Student registered for course");
                    
                }
            }
            // Course: update course data (name, instructor, students enrolled)
            else if(userAction == "course") {
                CourseCodeInput(code, courseRegistry);
                courseRegistry.at(code).PrintCourseInfo(studentRegistry);

                cout << "What would you like to update for this course? (\"title\", \"instructor\", \"students\", or \"back\"): ";
                cin >> userAction;
                cin.ignore();
                
                // Name: update title
                if(userAction == "title") {
                    courseRegistry.at(code).SetCourseTitle();
                  log.push_back("Course updated");
                }
  
                // Instructor: update instructor
                else if(userAction == "instructor") {
                    courseRegistry.at(code).SetCourseInstructor();
                  log.push_back("Course updated");
                }
  
                // Enrollment: Add student using their id
                else if (userAction == "students") {
                  StudentIDInput(id, studentRegistry);
                  studentRegistry.at(id).PrintStudentSummary();

                  // Must update both student and course object
                  courseRegistry.at(code).AddStudent(id);
                  studentRegistry.at(id).AddCourse(code, true);

                  log.push_back("Added student to course");
                }
  
                    
            }  
        }

          // Remove: student from course, course from student, entire student, entire course
        else if(userAction == "remove") {
          
          cout << "What would you like to remove? (\"student\", \"course\", or \"back\"): ";
          cin >> userAction;
          if(userAction == "student") {
            cout << "Would you like to remove the student entirely or remove them from a course? (\"student\", \"course\", or \"back\"): ";
            cin >> userAction;
            cin.ignore();

            StudentIDInput(id, studentRegistry);
            studentRegistry.at(id).PrintStudentInfo(courseRegistry);

            if(userAction == "student") {
              studentRegistry.erase(id);

              // Drops student from any courses that contain the student
              for (auto& [key, course] : courseRegistry) {
                if(course.HasStudent(id)) {
                  course.DropStudent(id, true);
                }
              }

              cout << "Successfully removed student from the registry." << endl;

              log.push_back("Removed student");
            }
            // Removes any relationship containing this student and this course
            else if (userAction == "course") {
              CourseCodeInput(code, courseRegistry);
              
              studentRegistry.at(id).DropCourse(code, true);
              courseRegistry.at(code).DropStudent(id);
              
              courseRegistry.at(code).PrintCourseInfo(studentRegistry);

              

              log.push_back("Removed student from course");
            }
          }

          // Fully removes course from registry and from courses students are taking
          else if(userAction == "course") {
            CourseCodeInput(code, courseRegistry);
            courseRegistry.at(code).PrintCourseInfo(studentRegistry);

            courseRegistry.erase(code);
            for (auto& [key, student] : studentRegistry) {
              if(student.HasCourse(code)) {
                student.DropCourse(code, true);
              }
            }

            log.push_back("Removed course");

            cout << "Successfully removed course from the registry." << endl;
          }
        }
      }
    
    cout << "What would you like to do? (\"view\" or \"modify\"): ";
    cin >> userAction;
  }
}