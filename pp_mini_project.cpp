#include <iostream>
#include <string>
#include <vector>
#include <map>

// Define a base class Person
class Person {
public:
    std::string name;
    virtual void displayDetails() const = 0; // Pure virtual function
};

// Define a derived class Student
class Student : public Person {
public:
    int rollNo;
    char attendance;

    Student(int rollNo, const std::string& name, char attendance)
        : rollNo(rollNo), attendance(attendance) {
        this->name = name;
    }

    void displayDetails() const override {
        std::cout << "Roll No: " << rollNo << "\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Attendance: " << attendance << "\n";
    }
};

// Define a class for Classroom that contains a vector of persons (students)
class Classroom {
private:
    std::vector<Person*> persons;

public:
    // Function to add a person (student) to the classroom
    void addPerson(Person* person) {
        persons.push_back(person);
    }

    // Function to display details for all persons (students) in the classroom
    void displayDetails() const {
        std::cout << "Classroom Details:\n";
        for (const Person* person : persons) {
            person->displayDetails();
            std::cout << "--------------------------\n";
        }
    }

    // Public function to clean up dynamically allocated objects
    void cleanup() {
        for (Person* person : persons) {
            delete person;
        }
        persons.clear();
    }
};

int main() {
    std::map<std::string, std::map<std::string, Classroom> > dateSectionClassroomMap;

    while (true) {
        std::cout << "Student Attendance Manager\n";
        std::cout << "1. Enter details\n";
        std::cout << "2. Display attendance details\n";
        std::cout << "3. Exit\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string date, section;
            std::cout << "Enter the date: ";
            std::cin.ignore(); // Ignore the newline character left in the input stream
            std::getline(std::cin, date);
            std::cout << "Enter the section (A, B, C, etc.): ";
            std::cin >> section;

            int numStudents = 10;

            Classroom classroom;

            for (int i = 0; i < numStudents; i++) {
                int rollNo = i + 1;
                std::string name;
                char attendance;

                std::cout << "Enter name for Student " << rollNo << ": ";
                std::cin.ignore(); // Ignore the newline character left in the input stream
                std::getline(std::cin, name);

                while (true) {
                    std::cout << "Mark attendance (p for present, a for absent): ";
                    std::cin >> attendance;

                    if (attendance == 'p' || attendance == 'a') {
                        break;
                    } else {
                        std::cout << "Invalid input. Please enter 'p' for present or 'a' for absent.\n";
                    }
                }

                Student* student = new Student(rollNo, name, attendance);
                classroom.addPerson(student);
            }

            dateSectionClassroomMap[date][section] = classroom;
        } else if (choice == 2) {
            std::string date, section;
            std::cout << "Enter the date to display attendance: ";
            std::cin.ignore(); // Ignore the newline character left in the input stream
            std::getline(std::cin, date);
            std::cout << "Enter the section to display attendance: ";
            std::cin >> section;

            if (dateSectionClassroomMap.find(date) != dateSectionClassroomMap.end() &&
                dateSectionClassroomMap[date].find(section) != dateSectionClassroomMap[date].end()) {
                dateSectionClassroomMap[date][section].displayDetails();
            } else {
                std::cout << "No attendance data found for the given date and section.\n";
            }
        } else if (choice == 3) {
            // Clean up dynamically allocated Student objects
            for (auto& dateEntry : dateSectionClassroomMap) {
                for (auto& sectionEntry : dateEntry.second) {
                    sectionEntry.second.cleanup();
                }
            }
            std::cout<<"Exited Successfully"<<std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }

    return 0;
}

