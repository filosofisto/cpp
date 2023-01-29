#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

int main() {
    auto start { high_resolution_clock::now() };

    double d { 0 };
    for (int i { 0 }; i < 1'000'000; ++i) {
        d += sqrt(sin(i) * cos(i));
    }

    auto end { high_resolution_clock ::now() };
    auto diff { end - start };

    cout << duration<double, milli> { diff }.count() << "ms" << endl;
    return EXIT_SUCCESS;
}
