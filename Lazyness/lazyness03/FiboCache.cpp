#include "FiboCache.h"

unsigned int FiboCache::calc(unsigned int n)
{    
    if (cache.size() > n) {
        return cache[n];
    }
    
    const auto result = calc(n-1) + calc(n-2);
    cache.push_back(result);
    
    return result;
}
