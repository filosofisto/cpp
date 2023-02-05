#include <iostream>
#include <thread>
#include <vector>

using std::thread;
using std::cout;
using std::endl;
using std::atomic_flag;
using std::vector;

atomic_flag spinlock = ATOMIC_FLAG_INIT;
static const size_t NumberOfThreads { 50 };
static const size_t LoopsPerThread { 100 };

void doWork(size_t threadNumber, vector<size_t>& data) {
    for (size_t i { 0 }; i < LoopsPerThread; ++i) {
        // Spin until lock is acquired
        while (spinlock.test_and_set()) { }

        // Save to handle shared data
        data.push_back(threadNumber);

        // Release the acquired lock
        spinlock.clear();
    }
}

int main() {
    vector<size_t> data;
    vector<thread> threads;

    for (int i { 0 }; i < NumberOfThreads; ++i) {
        threads.push_back(thread { doWork, i, ref(data) });
    }

    for (auto& t: threads) {
        t.join();
    }

    cout << "data contains " << data.size() << " elements, expected " << NumberOfThreads * LoopsPerThread << endl;
    return EXIT_SUCCESS;
}
