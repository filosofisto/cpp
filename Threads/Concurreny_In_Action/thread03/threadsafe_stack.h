#ifndef THREADSAFE_STACK_H
#define THREADSAFE_STACK_H

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

using std::exception;
using std::stack;
using std::lock_guard;
using std::move;
using std::mutex;
using std::make_shared;
using std::shared_ptr;

struct empty_stack: exception
{
    const char* what() const throw() 
    {
        return "stack is empty";
    }
};

template<typename T>
class threadsafe_stack
{
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other)
    {
        lock_guard<mutex> lock(other.m_mutex);
        m_stack = other.m_stack;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;
    
    void push(T new_value)
    {
        lock_guard<mutex> lock(m_mutex);
        m_stack.push(move(new_value));
    }
    
    shared_ptr<T> pop()
    {
        lock_guard<mutex> lock(m_mutex);
        if (m_stack.empty()) throw empty_stack();
        const shared_ptr<T> res(make_shared<T>(m_stack.top()));
        m_stack.pop();
        return res;
    }
    
    void pop(T& value)
    {
        lock_guard<mutex> lock(m_mutex);
        if (m_stack.empty()) throw empty_stack();
        value = m_stack.top();
        m_stack.pop();
    }
    
    bool empty() const
    {
        lock_guard<mutex> lock(m_mutex);
        return m_stack.empty();
    }
private:
    stack<T> m_stack;
    mutable mutex m_mutex;
};


#endif
