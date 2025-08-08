# University Course Management System

This university course management system, designed using C++, can be used to suit most administrative needs involved in university management. The system (preloaded with test data) can be accessed at https://replit.com/@RandomMaker/University-Course-Management-System?v=1.

## Design

### STL Containers

1. ```std::map``` - The system uses two map containers to hold the registries for courses and students. By using a map container, courses and students can easily be retrieved using a key (set to be student ID and course code respectively), allowing for efficient searching of students and courses. Moreover, due to the nature of the ```std::map``` container, duplicate keys cannot be used, ensuring that student IDs and course codes do not conflict with each other and are regenerated if they do.
2. ```std::set``` - The Student and Course classes each use a set to store their respective course and student lists. Using the ```std::set``` container guarantees that duplicate students will not be linked to a course and duplicate courses will not be linked to a student. The ```std::set``` doesn't requiring key value pairs like the ```std::map``` container, making it a simpler and cleaner choice for storing the student and course lists.
3. ```std::queue``` - The Course class uses the ```std::queue``` container as a way of effectively managing the course waitlists once maximum capacity has been reached. This container makes it very simple and straightforward to quickly add and remove students from waitlist due to the ```pop()``` and ```front()``` methods.
4. ```std::deque``` - The system keeps track of all modifications made to the registry including adding, updating, and removing students or courses. These modifications are stored as strings in the ```std::deque``` container for quick logging of events.


