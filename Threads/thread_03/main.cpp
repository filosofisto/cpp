#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

int main() {
    int id { 1 };
    int numIterations { 5 };

    thread t { [id, numIterations] {
        for (int i { 0 }; i < numIterations; ++i) {
            cout << "Counter " << id << " has value " << i << "\n";
        }

        cout << endl;
    }};

    t.join();

    return EXIT_SUCCESS;
}
