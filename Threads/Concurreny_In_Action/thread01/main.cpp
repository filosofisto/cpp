#include <iostream>
#include <thread>
#include "thread_guard.h"

using namespace std;

struct func
{
    int& i;
    func(int& i): i(i) {}
    void operator()() {
        for (unsigned j = 0; j < 1000000; ++j) {
            std::cout << j << "\n";
        }
    }
};

int main()
{
    int some_local_state = 0;
    func my_func{some_local_state};
    std::thread my_thread(my_func);
    
    thread_guard guard(my_thread);
    
    return EXIT_SUCCESS;
}
