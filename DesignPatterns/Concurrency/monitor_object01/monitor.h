#ifndef MONITOR_H
#define MONITOR_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

class Monitor 
{
public:
    void lock() const
    {
        monitMutex.lock();
    }

    void unlock() const
    {
        monitMutex.unlock();
    }

    void notify_one() const noexcept
    {
        monitCond.notify_one();
    }
    
    template<typename Predicate>
    void wait(Predicate pred) const
    {
        std::unique_lock<std::mutex> monitLock(monitMutex);
        monitCond.wait(monitLock, pred);
    }

private:
    mutable std::mutex monitMutex;
    mutable std::condition_variable monitCond;
};

template <typename T>
class ThreadSafeQueue: public Monitor
{
public:
    void add(T value)
    {
        lock();
        myQueue.push(value);
        unlock();
        notify_one();
    }
    
    T get()
    {
        wait([this] { return !myQueue.empty(); });
        lock();
        auto value = myQueue.front();
        myQueue.pop();
        unlock();
        
        return value;
    }

private:
    std::queue<T> myQueue;
};
    
class Dice
{
public:
    int operator()()
    {
        return rand();
    }
private:
    std::function<int()> rand = std::bind(std::uniform_int_distribution<>(1,6), std::default_random_engine());
};

#endif
