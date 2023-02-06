#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include "Logger.h"

using std::stringstream;
using std::vector;
using std::thread;
using std::ref;

void logSomeMessages(int id, Logger& logger) {
    for (int i { 0 }; i < 10; ++i) {
        // why format is not working in my env???
        stringstream s { "Log entry "};
        s << i << " from thread " << id;

        logger.log(s.str());
    }
}

int main() {
    Logger logger;
    vector<thread> threads;

    // Create a few threads all working with the same Logger instance
    for (int i { 0 }; i < 10; ++i) {
        threads.push_back(thread { logSomeMessages, i, ref(logger) });
    }

    for (auto& t: threads) {
        t.join();
    }

    return EXIT_SUCCESS;
}
