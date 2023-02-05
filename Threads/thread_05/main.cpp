#include <iostream>
#include <thread>

using std::exception_ptr;
using std::thread;
using std::cout;
using std::endl;
using std::runtime_error;
using std::current_exception;
using std::ref;
using std::exception;

void doSomeWork()
{
    for (int i { 0 }; i < 5; ++i) {
        cout << i << endl;
    }

    cout << "Throwing a runtime_exception..." << endl;
    throw runtime_error("Original exception");
}

void threadFunction(exception_ptr& error)
{
    try {
        doSomeWork();
    } catch (...) {
        cout << "Thread caught exception, returnin exception..." << endl;
        error = current_exception();
    }
}

void doWorkInThread()
{
    exception_ptr error;
    thread t { threadFunction, ref(error) };
    t.join();

    if (error) {
        cout << "Main thread received exception, rethrowing it" << endl;
    } else {
        cout << "Main thread did not receive any exception" << endl;
    }
}

int main() {
    try {
        doWorkInThread();
    } catch (const exception& e) {
        cout << "Main function caught: '" << e.what() << "'" << endl;
    }

    return EXIT_SUCCESS;
}
