#include <string>
#include <iostream>

class scheduleItem {
private:
    std::string subject, catalog, section, component, session, instructor;
    int units, totEnrl, capEnrl;

public:
    // Constructor with default values for fields
    scheduleItem(std::string sub = "", std::string cat = "", std::string sec = "",
                 std::string comp = "", std::string ses = "", std::string instr = "", 
                 int u = 0, int te = 0, int ce = 0)
        : subject(sub), catalog(cat), section(sec), component(comp), session(ses),
          instructor(instr), units(u), totEnrl(te), capEnrl(ce) {}

    // Getters for each field
    std::string getSubject() const { return subject; }
    std::string getCatalog() const { return catalog; }
    std::string getSection() const { return section; }
    std::string getComponent() const { return component; }
    std::string getSession() const { return session; }
    std::string getInstructor() const { return instructor; }
    int getUnits() const { return units; }
    int getTotEnrl() const { return totEnrl; }
    int getCapEnrl() const { return capEnrl; }

    // Overloading operators to compare based on the key (subject, catalog, section)
    bool operator==(const scheduleItem& other) const {
        return (subject == other.subject && catalog == other.catalog && section == other.section);
    }

    bool operator!=(const scheduleItem& other) const {
        return !(*this == other);
    }

    bool operator>=(const scheduleItem& other) const {
        return (subject > other.subject) || 
               (subject == other.subject && catalog > other.catalog) || 
               (subject == other.subject && catalog == other.catalog && section >= other.section);
    }

    // Print function to display schedule item
    void print() const {
        std::cout << subject << " " << catalog << " " << section << " " << component << " "
                  << session << " " << units << " " << totEnrl << " " << capEnrl << " "
                  << instructor << std::endl;
    }
};
