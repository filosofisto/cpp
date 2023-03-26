#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

// #include <exception>
// #include <stdexcept>
#include <string>

class MyException: public std::exception
{
public:
    MyException(const std::string& message): m_message(message) { }
    virtual const char* what() const noexcept { return m_message.c_str(); } 
private:
    std::string m_message;
};

#endif
