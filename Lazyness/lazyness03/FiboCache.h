#ifndef FIBOCACHE_H
#define FIBOCACHE_H

#include <vector>

class FiboCache
{
public:
    FiboCache() = default;
    ~FiboCache() = default;
    
    unsigned int calc(unsigned int n);
private:
    std::vector<unsigned int> cache{0, 1};
};

#endif
