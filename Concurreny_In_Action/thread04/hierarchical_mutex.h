#ifndef HIERARQUICAL_MUTEX_H
#define HIERARQUICAL_MUTEX_H

#include <mutex>
#include <climits>

using std::mutex;

class hierarchical_mutex
{
public:
    explicit hierarchical_mutex(unsigned long value);
    void lock();
    void unlock();
    bool try_lock();
private:
    void check_for_hierarchy_violation();
    void update_hierarchy_value();
    
    mutex m_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;
};

#endif
