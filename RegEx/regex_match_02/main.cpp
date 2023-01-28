#include <iostream>
#include <regex>
#include <format>

using namespace std;

int main() {
    regex dateRE { "(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])" };

    while (true) {
        cout << "Enter a date (year/month/day) (q=quit): ";
        string input;
        if (!getline(cin, input) || input == "q") break;

        if (smatch m; regex_match(input, m, dateRE)) {
            int year { stoi(m[1]) };
            int month { stoi(m[2]) };
            int day { stoi(m[3]) };

            cout << " Valid date: Year=" << year << " Month=" << month << " Day=" << day << endl;
        } else {
            cout << " Invalid date!" << endl;
        }
    }

    return EXIT_SUCCESS;
}
