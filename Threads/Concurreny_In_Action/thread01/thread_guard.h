#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

#include <thread>

using std::thread;

class thread_guard 
{
public:
    explicit thread_guard(thread& t);
    ~thread_guard();
    
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
    
private:
    thread& m_thread;
};

#endif
