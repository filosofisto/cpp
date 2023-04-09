#include "thread_guard.h"

thread_guard::thread_guard(thread& t): m_thread(t) 
{
    
}

thread_guard::~thread_guard()
{
    if (m_thread.joinable()) {
        m_thread.join();
    }
}
