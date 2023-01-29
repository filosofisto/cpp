#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
    // Create a time_point representing the epoch of the associated steady clock
    time_point<steady_clock> tp1;

    // Add 10 minutes to the time_point
    tp1 += minutes { 10 };

    // Store the duration between epoch and time_point
    auto d1 { tp1.time_since_epoch() };

    // Convert the duration to seconds and output to the console
    duration<double> d2 { d1 };

    cout << d2.count() << " seconds" << endl;

    return EXIT_SUCCESS;
}
