
#ifndef LAZYVAL_H
#define LAZYVAL_H

#include <mutex>
#include <type_traits>

using std::mutex;
using std::forward;
using std::unique_lock;

template <typename F>
class LazyVal 
{

public:
    using result_type = std::result_of_t<F()>;
    
    LazyVal(F computation): computation{ computation }, cacheInitialized{ false }
    {
    }
    
    ~LazyVal() = default;
    
    operator const result_type&() const
    {
        unique_lock<mutex> lock(cacheMutex);
        
        if (!cacheInitialized) {
            cache = computation();
            cacheInitialized = true;
        }
        
        return cache;
    }

private:
    F computation;
    mutable bool cacheInitialized;
    mutable result_type cache;
    mutable mutex cacheMutex;
};

template <typename F>
inline LazyVal<F> make_lazy_val(F&& computation)
{
    return LazyVal<F>(std::forward<F>(computation));
}

#endif
