#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <iomanip>
using namespace std;

class Date {
private:
    uint16_t year;
    uint8_t month;
    uint8_t day;

    // Using array and string_view for more efficient string handling
    static constexpr array<string_view, 12> MONTHS = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Array to store days in each month
    static constexpr array<uint8_t, 12> DAYS_IN_MONTH = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    // Improved date validation with exact days per month
    [[nodiscard]] static bool isValidDate(int m, int d, int y) noexcept {
        if (m < 1 || m > 12 || d < 1) return false;

        // Handle February in leap years
        if (m == 2 && isLeapYear(y)) {
            return d <= 29;
        }
        return d <= DAYS_IN_MONTH[m - 1];
    }

    [[nodiscard]] static bool isLeapYear(int y) noexcept {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

public:
    // Default constructor
    constexpr Date() noexcept : year(2000), month(1), day(1) {}

    // Parameterized constructor
    constexpr Date(int m, int d, int y) noexcept :
        year(isValidDate(m, d, y) ? y : 2000),
        month(isValidDate(m, d, y) ? m : 1),
        day(isValidDate(m, d, y) ? d : 1) {
        if (!isValidDate(m, d, y)) {
            cerr << "Invalid date! Setting to default (1/1/2000)\n";
        }
    }

    // Member functions to print dates in different formats
    void printMDY() const {
        cout << setfill('0')
             << setw(2) << static_cast<int>(month) << '/'
             << setw(2) << static_cast<int>(day) << '/'
             << setw(4) << year << '\n';
    }

    void printMonthDY() const {
        cout << MONTHS[month - 1] << ' '
             << static_cast<int>(day) << ", "
             << year << '\n';
    }

    void printDMY() const {
        cout << setw(2) << static_cast<int>(day) << ' '
             << MONTHS[month - 1] << ' '
             << year << '\n';
    }

    // Getter methods
    [[nodiscard]] constexpr uint16_t getYear() const noexcept { return year; }
    [[nodiscard]] constexpr uint8_t getMonth() const noexcept { return month; }
    [[nodiscard]] constexpr uint8_t getDay() const noexcept { return day; }
};

int main() {
    int month, day, year;

    cout << "Enter a month (1-12): ";
    if (!(cin >> month)) {
        cerr << "Invalid input for month\n";
        return 1;
    }

    cout << "Enter a day (1-31): ";
    if (!(cin >> day)) {
        cerr << "Invalid input for day\n";
        return 1;
    }

    cout << "Enter a year: ";
    if (!(cin >> year)) {
        cerr << "Invalid input for year\n";
        return 1;
    }

    cout << "\nOutputting date in three formats:\n";
    const Date userDate(month, day, year);
    userDate.printMDY();
    userDate.printMonthDY();
    userDate.printDMY();

    cout << "\nTest cases for validation:\n";

    cout << "\nTest case 1 - Invalid month (13):\n";
    const Date date1(13, 1, 2028);
    date1.printMDY();
    date1.printMonthDY();
    date1.printDMY();

    cout << "\nTest case 2 - Invalid day (32):\n";
    const Date date2(7, 32, 2028);
    date2.printMDY();
    date2.printMonthDY();
    date2.printDMY();

    return 0;
}