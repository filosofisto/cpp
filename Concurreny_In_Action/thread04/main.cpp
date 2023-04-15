#include <iostream>
#include <thread>
#include <mutex>
#include "hierarchical_mutex.h"

using namespace std;

hierarchical_mutex high_level_mutex{10000};
hierarchical_mutex low_level_mutex{10000};
hierarchical_mutex other_mutex{10000};

int do_low_level_stuff()
{
    cout << "low level stuff" << endl;
    return 0;
}

int low_level_func()
{
    lock_guard<hierarchical_mutex> lk(low_level_mutex);
    return do_low_level_stuff();
}

void high_level_stuff(int some_param)
{
    cout << "high level stuff" << endl;
}

void high_level_func()
{
    lock_guard<hierarchical_mutex> lk(high_level_mutex);
    high_level_stuff(low_level_func());
}

void thread_a()
{
    high_level_func();
}

void do_other_stuff()
{
    cout << "do other stuff" << endl;
}

void other_stuff()
{
    high_level_func();
    do_other_stuff();
}

void thread_b()
{
    lock_guard<hierarchical_mutex> lk(other_mutex);
    other_stuff();
}

int main()
{
    thread_a();
    thread_b();
    
    return EXIT_SUCCESS;
}
