#include <iostream>
#include <thread>
#include "Request.h"

using std::thread;

int main() {
    Request req { 10 };
    thread t { &Request::process, &req };
    t.join();

    return EXIT_SUCCESS;
}
