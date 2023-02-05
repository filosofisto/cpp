#include <iostream>
#include <thread>
#include "Counter.h"

using std::cout;
using std::endl;
using std::thread;

int main() {
    thread t1 { Counter{ 1, 20 } };

    Counter c { 2, 20 };
    thread t2 { c };

    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}
