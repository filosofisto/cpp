#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>

using std::cout;
using std::endl;
using std::chrono::duration;
using std::vector;
using std::thread;
using std::ref;
using std::atomic;

void increment(atomic<int>& counter) {
    int result { 0 };

    for (int i { 0 }; i < 100; ++i) {
        ++result;
        std::this_thread::sleep_for(duration<int, std::milli>(1));
    }

    counter += result;
}

int main() {
    atomic<int> counter { 0 };
    vector<thread> threads;

    for (int i { 0 }; i < 10; ++i) {
        threads.push_back(thread { increment, ref(counter) });
    }

    for (auto& t: threads) {
        t.join();
    }

    cout << "Result = " << counter << endl;
    cout << " * more performatic than atomic_01 sample" << endl;

    return EXIT_SUCCESS;
}
