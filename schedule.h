#include "scheduleItem.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

class schedule {
private:
    std::map<std::string, scheduleItem> scheduleData;

    std::string parseQuotedField(std::stringstream& ss) {
        std::string field;
        char ch;

        if (ss.peek() == '"') {
            ss.get();  
            while (ss.get(ch) && ch != '"') {
                field += ch;
            }
            ss.get();  
        }
        else {
            std::getline(ss, field, ',');
        }

        return field;
    }

public:
    // Initialize the schedule by reading from a file
    void initSchedule(std::ifstream& file) {
        std::string line;
        std::getline(file, line);  // Discard the header line

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string subject, catalog, section, component, session, instructor;
            int units, totEnrl, capEnrl;

            // Parse the necessary fields, adjusting the positions according to your data
            std::getline(ss, subject, ',');    // Subject
            std::getline(ss, catalog, ',');    // Catalog
            std::getline(ss, section, ',');    // Section
            std::getline(ss, component, ',');  // Component
            std::getline(ss, session, ',');    // Session

            // Skip over MinUnits field
            std::string minUnits;
            std::getline(ss, minUnits, ',');  

            // Parse Units, TotEnrl, CapEnrl
            ss >> units; ss.ignore();  
            ss >> totEnrl; ss.ignore();  
            ss >> capEnrl; ss.ignore(); 

            // Parse Unused AcadOrg
            std::string acadOrg;
            std::getline(ss, acadOrg, ',');

            // Parse Instructor using the helper function
            instructor = parseQuotedField(ss);

            // Skip over the other fields (Capacity, Room, etc.)
            std::string capacity, room, mtgStart, mtgEnd, days, startDate, endDate, term, campus, classNbr, totalCredits, dup, full, over;
            std::getline(ss, capacity, ',');
            std::getline(ss, room, ',');
            std::getline(ss, mtgStart, ',');
            std::getline(ss, mtgEnd, ',');
            std::getline(ss, days, ',');
            std::getline(ss, startDate, ',');
            std::getline(ss, endDate, ',');
            std::getline(ss, term, ',');
            std::getline(ss, campus, ',');
            std::getline(ss, classNbr, ',');
            std::getline(ss, totalCredits, ',');
            std::getline(ss, dup, ',');
            std::getline(ss, full, ',');
            std::getline(ss, over, ',');  

            // Create the scheduleItem object and add it to the map
            scheduleItem item(subject, catalog, section, component, session, instructor, units, totEnrl, capEnrl);
            addEntry(item);
        }
    }

    // Add a scheduleItem to the map
    void addEntry(const scheduleItem& item) {
        std::string key = item.getSubject() + "_" + item.getCatalog() + "_" + item.getSection();
        scheduleData[key] = item;
    }

    // Print the entire schedule
    void print() const {
        //Header row (adjusted widths as needed)
        std::cout << std::setw(10) << std::left << "Subject"
            << std::setw(10) << "Catalog"
            << std::setw(10) << "Section"
            << std::setw(10) << "Component"
            << std::setw(10) << "Session"
            << std::setw(30) << "Instructor"
            << std::setw(10) << "Units"
            << std::setw(10) << "TotEnrl"
            << std::setw(10) << "CapEnrl" << std::endl;

        // Print each schedule item in a neatly aligned format
        for (const auto& entry : scheduleData) {
            const scheduleItem& item = entry.second;

            std::cout << std::setw(10) << std::left << item.getSubject()
                << std::setw(10) << item.getCatalog()
                << std::setw(10) << item.getSection()
                << std::setw(10) << item.getComponent()
                << std::setw(10) << item.getSession()
                << std::setw(30) << item.getInstructor()  // Increased space for name
                << std::setw(10) << item.getUnits()
                << std::setw(10) << item.getTotEnrl()
                << std::setw(10) << item.getCapEnrl() << std::endl;
        }
    }

#include <iomanip>  // Ensure this is included for std::setw and formatting

    // Find records by subject
    void findBySubject(const std::string& subject) const {
        // Print the header for the search results
        std::cout << std::setw(10) << std::left << "Subject"
            << std::setw(10) << "Catalog"
            << std::setw(10) << "Section"
            << std::setw(10) << "Component"
            << std::setw(10) << "Session"
            << std::setw(30) << "Instructor"
            << std::setw(10) << "Units"
            << std::setw(10) << "TotEnrl"
            << std::setw(10) << "CapEnrl" << std::endl;

        // Loop through the schedule data and print matching records
        for (const auto& entry : scheduleData) {
            if (entry.second.getSubject() == subject) {
                const scheduleItem& item = entry.second;
                std::cout << std::setw(10) << std::left << item.getSubject()
                    << std::setw(10) << item.getCatalog()
                    << std::setw(10) << item.getSection()
                    << std::setw(10) << item.getComponent()
                    << std::setw(10) << item.getSession()
                    << std::setw(30) << item.getInstructor()  // Adjusted for instructor name
                    << std::setw(10) << item.getUnits()
                    << std::setw(10) << item.getTotEnrl()
                    << std::setw(10) << item.getCapEnrl() << std::endl;
            }
        }
    }

    // Find records by subject and catalog
    void findBySubjectCatalog(const std::string& subject, const std::string& catalog) const {
        // Print the header for the search results
        std::cout << std::setw(10) << std::left << "Subject"
            << std::setw(10) << "Catalog"
            << std::setw(10) << "Section"
            << std::setw(10) << "Component"
            << std::setw(10) << "Session"
            << std::setw(30) << "Instructor"
            << std::setw(10) << "Units"
            << std::setw(10) << "TotEnrl"
            << std::setw(10) << "CapEnrl" << std::endl;

        // Loop through the schedule data and print matching records
        for (const auto& entry : scheduleData) {
            if (entry.second.getSubject() == subject && entry.second.getCatalog() == catalog) {
                const scheduleItem& item = entry.second;
                std::cout << std::setw(10) << std::left << item.getSubject()
                    << std::setw(10) << item.getCatalog()
                    << std::setw(10) << item.getSection()
                    << std::setw(10) << item.getComponent()
                    << std::setw(10) << item.getSession()
                    << std::setw(30) << item.getInstructor()  // Adjusted for instructor name
                    << std::setw(10) << item.getUnits()
                    << std::setw(10) << item.getTotEnrl()
                    << std::setw(10) << item.getCapEnrl() << std::endl;
            }
        }
    }

    // Find records by instructor's last name
    void findByInstructor(const std::string& instructor) const {
        // Print the header for the search results
        std::cout << std::setw(10) << std::left << "Subject"
            << std::setw(10) << "Catalog"
            << std::setw(10) << "Section"
            << std::setw(10) << "Component"
            << std::setw(10) << "Session"
            << std::setw(30) << "Instructor"
            << std::setw(10) << "Units"
            << std::setw(10) << "TotEnrl"
            << std::setw(10) << "CapEnrl" << std::endl;

        // Loop through the schedule data and print matching records
        for (const auto& entry : scheduleData) {
            if (entry.second.getInstructor().find(instructor) != std::string::npos) {
                const scheduleItem& item = entry.second;
                std::cout << std::setw(10) << std::left << item.getSubject()
                    << std::setw(10) << item.getCatalog()
                    << std::setw(10) << item.getSection()
                    << std::setw(10) << item.getComponent()
                    << std::setw(10) << item.getSession()
                    << std::setw(30) << item.getInstructor()  // Adjusted for instructor name
                    << std::setw(10) << item.getUnits()
                    << std::setw(10) << item.getTotEnrl()
                    << std::setw(10) << item.getCapEnrl() << std::endl;
            }
        }
    }

};
