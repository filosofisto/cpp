#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void counter(int id, int numIterations)
{
    for (int i { 0 }; i < numIterations; ++i) {
        cout << "Counter " << id << " has value " << i << "\n";
    }
}

int main() {
    thread t1 { counter, 1, 100 };
    thread t2 { counter, 2, 100 };
    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}
