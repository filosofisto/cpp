#ifndef THREADSAFE_QUEUE_H
#define THREADSAFE_QUEUE_H

#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class threadsafe_queue
{
public:
    threadsafe_queue() {}
    
    void push(T value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(value));
        cond.notify_one();
    }
    
    void wait_and_pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        cond.wait(lock, [this] { return !data.empty(); });
        value = std::move(data.front());
    }
    
    std::shared_ptr<T> wait_and_pop()
    {
        std::lock_guard<std::mutex> lock(m);
        cond.wait(lock, [this] { return !data.empty(); });
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data.front())));
        data.pop();
        return res;
    }
    
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data.front())));
        data.pop();
        return res;
    }
    
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
    
private:
    mutable std::mutex m;
    std::queue<T> data;
    std::condition_variable cond;
};
#endif
