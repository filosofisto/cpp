
#ifndef LAZYVAL_H
#define LAZYVAL_H

#include <mutex>
#include <type_traits>

using std::once_flag;
using std::call_once;
using std::forward;

template <typename F>
class LazyVal 
{

public:
    using result_type = std::result_of_t<F()>;
    
    LazyVal(F computation): computation{ computation }
    {
    }
    
    ~LazyVal() = default;
    
    operator const result_type&() const
    {
        call_once(valueFlag, [this] { cache = computation(); });
        
        return cache;
    }

private:
    F computation;
    mutable result_type cache;
    mutable once_flag valueFlag;
};

template <typename F>
inline LazyVal<F> make_lazy_val(F&& computation)
{
    return LazyVal<F>(std::forward<F>(computation));
}

#endif
