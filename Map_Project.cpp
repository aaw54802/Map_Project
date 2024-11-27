#include <iostream>
#include <fstream>
#include "schedule.h"

int main() {
    schedule mySchedule;
    std::ifstream file("STEM - Summer 2022 Schedule of Classes as of 05-02-22(1).csv");  // Open the CSV file
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    mySchedule.initSchedule(file);  // Initialize schedule with file data
    file.close();  // Close the file

    // Example menu to interact with the schedule
    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Print all Schedule\n";
        std::cout << "2. Find by Subject\n";
        std::cout << "3. Find by Subject and Catalog\n";
        std::cout << "4. Find by Instructor\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            mySchedule.print();  // Print the entire schedule
        }
        else if (choice == 2) {
            std::string subject;
            std::cout << "Enter Subject: ";
            std::cin >> subject;
            mySchedule.findBySubject(subject);  // Find by subject
        }
        else if (choice == 3) {
            std::string subject, catalog;
            std::cout << "Enter Subject and Catalog Number (Format|| SUB ###): ";
            std::cin >> subject >> catalog;
            mySchedule.findBySubjectCatalog(subject, catalog);  // Find by subject and catalog
        }
        else if (choice == 4) {
            std::string instructor;
            std::cout << "Enter Instructor's Name: ";
            std::cin >> instructor;
            mySchedule.findByInstructor(instructor);  // Find by instructor
        }
    } while (choice != 5);

    return 0;
}
