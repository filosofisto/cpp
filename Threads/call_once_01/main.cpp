#include <iostream>
#include <thread>
#include <vector>

using std::once_flag;
using std::cout;
using std::endl;
using std::call_once;
using std::vector;
using std::thread;

once_flag g_once_flag;

void initializeSharedResources() {
    // .. Initialize shared resources to be used by multiple threads
    cout << "Shared resources initialized." << endl;
}

void processingFunction() {
    // Make sure the shared resources are initialized
    call_once(g_once_flag, initializeSharedResources);

    // Do some work, including using the shared resources
    cout << "Processing" << endl;
}

int main() {
    vector<thread> threads { 3 };
    for (auto& t: threads) {
        t = thread{ processingFunction };
    }

    for (auto& t: threads) {
        t.join();
    }

    return EXIT_SUCCESS;
}
