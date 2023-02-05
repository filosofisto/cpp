#include <iostream>
#include <thread>
#include "Counter.h"

using std::cout;
using std::endl;
using std::thread;
using std::ref;

int main() {
    thread t1 { Counter{ 1, 20 } };

    Counter c { 2, 20 };
//    thread t2 { c };

    thread t2 { ref(c) }; // to execute on actual object instead of copied one
    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}
