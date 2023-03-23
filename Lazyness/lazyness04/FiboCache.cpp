#include "FiboCache.h"

FiboCache::FiboCache(): m_previous{0}, m_last{1}, m_size{2}
{
}

size_t FiboCache::size() const
{
    return m_size;
}

unsigned int FiboCache::operator[] (unsigned int n) const
{
    if (n == m_size-1) return m_last;
    if (n == m_size-2) return m_previous;
    
    auto result = m_last + m_previous;
    push_back(result);
    
    return result;
}

void FiboCache::push_back(unsigned int value) const
{
    m_size++;
    m_previous = m_last;
    m_last = value;
}

