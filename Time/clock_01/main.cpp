#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

int main() {
    // Get current time as a time_point
    system_clock::time_point  tpoint { system_clock::now() };
    // Convert to a time_t
    time_t tt { system_clock::to_time_t(tpoint) };
    // Convert to localtime
    tm* t { localtime(&tt) };
    // Write the time
    cout << put_time(t, "%H:%M:%S") << endl;
    return EXIT_SUCCESS;
}
