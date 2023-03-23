#ifndef FIBOCACHE_H
#define FIBOCACHE_H

#include <cstddef>

class FiboCache
{
public:
    FiboCache();
    ~FiboCache() = default;
    
    size_t size() const;
    unsigned int operator[] (unsigned int n) const;
private:
    void push_back(unsigned int value) const;
    
    mutable unsigned int m_previous;
    mutable unsigned int m_last;
    mutable size_t m_size;
};

#endif
