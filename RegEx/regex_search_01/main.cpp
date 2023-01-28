#include <iostream>
#include <regex>

using namespace std;

int main() {
    regex r { "//\\s*(.+)$" };

    while (true) {
        cout << "Enter a string with optional code comments (q=quit): ";
        string input;
        if (!getline(cin, input) || input == "q") break;

        if (smatch m; regex_search(input, m, r)) {
            cout << " Found comment '" << m[1].str() << "'" << endl;
        } else {
            cout << " No comments found!" << endl;
        }
    }

    return EXIT_SUCCESS;
}
