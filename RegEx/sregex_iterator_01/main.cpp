#include <iostream>
#include <regex>

using namespace std;

int main() {
    regex reg { "[\\w]+" };

    while (true) {
        cout << "Enter a string to split (q=quit): ";
        string input;
        if (!getline(cin, input) || input == "q") break;

        const sregex_iterator end;
        for (sregex_iterator it { cbegin(input), cend(input), reg }; it != end; ++it) {
            cout << "\"" << (*it)[0].str() << "\"\n";
        }

        cout << endl;
    }

    return EXIT_SUCCESS;
}
