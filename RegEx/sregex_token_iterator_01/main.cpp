#include <iostream>
#include <regex>
#include <vector>

using namespace std;

int main() {
    regex dateRE { "^(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])$" };

    while (true) {
        cout << "Enter a date (year/month/day) (q=quit): ";
        string input;
        if (!getline(cin, input) || input == "q") break;

        vector indices { 2, 3 };
        const sregex_token_iterator end;
        for (sregex_token_iterator it { cbegin(input), cend(input), dateRE, indices}; it != end; ++it) {
            cout << it->str() << "\n";
        }

        cout << endl;
    }

    return EXIT_SUCCESS;
}
