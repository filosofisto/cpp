#include <iostream>
#include <thread>
#include "threadsafe_stack.h"

using namespace std;

void even(threadsafe_stack<int>& stack) 
{
    for (int i = 2; i < 101; i+=2) {
        stack.push(i);
    }
}

void odd(threadsafe_stack<int>& stack) 
{
    for (int i = 1; i < 100; i+=2) {
        stack.push(i);
    }
}

int main()
{
    threadsafe_stack<int> stack;
    
    thread t_even([&stack]{
        for (int i = 2; i < 101; i+=2) {
            stack.push(i);
        }
    });
    thread t_odd([&stack]{
        for (int i = 1; i < 100; i+=2) {
            stack.push(i);
        }
    });
    
    t_even.join();
    t_odd.join();
    
    while (!stack.empty()) {
        cout << *(stack.pop()) << "\n";
    }
    
    return EXIT_SUCCESS;
}
