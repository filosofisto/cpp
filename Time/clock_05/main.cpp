#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
    const auto& timezone_db { get_tzdb() };
    for (const auto& timezone: timezone_db.zones) {
        cout << timezone.name() << "\n";
    }

    cout << endl;

    return EXIT_SUCCESS;
}
