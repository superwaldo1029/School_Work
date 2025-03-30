#include <iostream>
#include <string>
#include <iomanip>

class Payroll {
private:
    std::string name;
    std::string role;
    float hourlyRate;
    int hoursWorked;
    float totalPay;

    // Private validation method
    bool isValidHours(int hours) const {
        return (hours >= 0 && hours <= 60);
    }

    // Private calculation method
    void calculatePay() {
        totalPay = hourlyRate * hoursWorked;
    }

public:
    // Constructor
    Payroll(const std::string& empName = "", const std::string& empRole = "", float rate = 0.0)
        : name(empName), role(empRole), hourlyRate(rate), hoursWorked(0), totalPay(0.0) {}

    // Setter for hours with validation
    bool setHours(int hours) {
        if (isValidHours(hours)) {
            hoursWorked = hours;
            calculatePay();
            return true;
        }
        return false;
    }

    // Print payroll information
    void printPayroll() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Role: " << role << std::endl;
        std::cout << "Hours Worked: " << hoursWorked << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Hourly Rate: $" << hourlyRate << std::endl;
        std::cout << "Gross Pay: $" << totalPay << std::endl;
    }

    // Getters
    std::string getName() const { return name; }
    std::string getRole() const { return role; }
    float getHourlyRate() const { return hourlyRate; }
};

int main() {
    const int NUM_EMPLOYEES = 7;
    Payroll employees[NUM_EMPLOYEES] = {
        Payroll("Michael Scott", "Regional Manager", 35.50),
        Payroll("Dwight Schrute", "Assistant to the Regional Manager", 22.50),
        Payroll("Jim Halpert", "Sales Representative", 21.00),
        Payroll("Pam Beesly", "Receptionist", 17.50),
        Payroll("Stanley Hudson", "Sales Representative", 21.00),
        Payroll("Angela Martin", "Senior Accountant", 23.50),
        Payroll("Kevin Malone", "Accountant", 19.50)
    };

    int hours;
    std::cout << "\nEnter hours worked for Dunder Mifflin employees (0-60 hours):\n";

    for (int i = 0; i < NUM_EMPLOYEES; i++) {
        do {
            std::cout << employees[i].getName() << " - "
                     << employees[i].getRole() << " (Rate: $"
                     << std::fixed << std::setprecision(2)
                     << employees[i].getHourlyRate() << "/hr): ";

            std::cin >> hours;

            if (!employees[i].setHours(hours)) {
                std::cout << "Invalid input. Hours must be between 0 and 60.\n";
            }
        } while (!employees[i].setHours(hours));
    }

    std::cout << "\nDunder Mifflin Scranton Branch - Payroll Summary:\n";
    std::cout << "============================================\n";

    for (int i = 0; i < NUM_EMPLOYEES; i++) {
        std::cout << "\nEmployee " << (i + 1) << ":\n";
        employees[i].printPayroll();
        std::cout << "----------------\n";
    }

    return 0;
}