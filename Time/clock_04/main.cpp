#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
    time_point<steady_clock, seconds> tpSeconds { 42s };

    //Convert seconds to milliseconds implicitly
    time_point<steady_clock, milliseconds> tpMilliseconds { tpSeconds };
    cout << tpMilliseconds.time_since_epoch().count() << endl;

    // Convert milliseconds to seconds explicitly
    time_point<steady_clock, milliseconds> tpMilliseconds2 { 42'424ms };
    time_point<steady_clock, seconds> tpSeconds2 { time_point_cast<seconds>(tpMilliseconds2) };

    milliseconds ms { tpSeconds.time_since_epoch() };
    cout << ms.count() << "ms" << endl;

    return EXIT_SUCCESS;
}
