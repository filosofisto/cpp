#ifndef THREADSAFE_STACK_H
#define THREADSAFE_STACK_H

#include <exception>
#include <mutex>
#include <memory>
#include <stack>

struct empty_stack: std::exception
{
    const char* what() const throw() 
    {
        return "Stack is empty";
    }
};

template<typename T>
class threadsafe_stack
{
public:
    threadsafe_stack() { }
    
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;
    
    void push(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(value));
    }
    
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack();
        
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        
        return res;
    }
    
    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack();
        
        value = std::move(data.top());
        data.pop();
    }
    
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
private:
    std::stack<T> data;
    mutable std::mutex m;
};

#endif
