# University Course Management System

This university course management system, designed using C++, can be used to suit most administrative needs involved in university management. The system (preloaded with test data) can be accessed at https://replit.com/@RandomMaker/University-Course-Management-System?v=1 where it can be remixed for personal testing and modification.

Note: Test data is contained in the students.txt and courses.txt files. Any attempt to change these files should maintain the format of the files for compatibility with the file parsing script.

## Design

### STL Containers

1. ```std::map``` - The system uses two map containers to hold the registries for courses and students. By using a map container, courses and students can easily be retrieved using a key (set to be student ID and course code respectively), allowing for efficient searching of students and courses. Moreover, due to the nature of the ```std::map``` container, duplicate keys cannot be used, ensuring that student IDs and course codes do not conflict with each other and are regenerated if they do.
2. ```std::set``` - The Student and Course classes each use a set to store their respective course and student lists. Using the ```std::set``` container guarantees that duplicate students will not be linked to a course and duplicate courses will not be linked to a student. The ```std::set``` doesn't requiring key value pairs like the ```std::map``` container, making it a simpler and cleaner choice for storing the student and course lists. Initially the lists contained respective Student and Course objects. However, in implementing the test data, it became apparent that having to hold a copy of each full object was causing a memory overload and would cause the program to crash during the parsing of the test files. So, the sets were instead changed to contain the identifiers of each object (student id and course code) which significantly reduced the memory sag created by courses for each student and students for each course.
4. ```std::queue``` - The Course class uses the ```std::queue``` container as a way of effectively managing the course waitlists once maximum capacity has been reached. This container makes it very simple and straightforward to quickly add and remove students from waitlist due to the ```pop()``` and ```front()``` methods.
5. ```std::deque``` - The system keeps track of all modifications made to the registry including adding, updating, and removing students or courses. These modifications are stored as strings in the ```std::deque``` container for quick logging of events.

### Other Design Choices

1. Test Data Formatting - The test data in students.txt and courses.txt are formatted using tab separated values to form groups of variables. This is done to ensure that spaces for variables such as names and titles are preserved while kept distinct from each other.
2. Prompting System - The program takes the user through a series of prompts based on categories. This allows for a wide variety of options for users to select in a structured and intuitive way. There are many branches to each option and by prompting the user in a step by step manner, it eases the mental load of bombarding tens of options at once.
3. User Freedom - When the user goes through the prompts designated in the code, they have the option to enter "back" in order to return to the main prompting selection. This ensures that a user is not forced to commit actions they had no intention of doing.
4. Linking of Courses and Students - Each student object has a set of courses associated with it just as each course has a set of students associated with it. This makes printing information relevant to each student or course significantly easier. However, when a student adds or drops a course (or a student or course is removed), this means that both the relevant student and course objects must be independently updated, adding a minor redundancy.
