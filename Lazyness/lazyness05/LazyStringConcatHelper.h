#ifndef LAZY_STRING_CONCAT_HELPER_H
#define LAZY_STRING_CONCAT_HELPER_H

#include <string>

template <typename... Strings>
class LazyStringConcatHelper;

template <typename LastString, typename... Strings>
class LazyStringConcatHelper<LastString, Strings...>
{
public:
    LazyStringConcatHelper(LastString data, LazyStringConcatHelper<Strings...> tail): data(data), tail(tail) { }
    
    int size() const { return data.size() + tail.size(); }
    
    template <typename It>
    void save(It end) const
    {
        const auto begin = end - data.size();
        std::copy(data.cbegin(), data.cend(), begin);
        tail.save(begin);
    }
    
    // cast operator to std::string -> (std::string) lazyInstance
    operator std::string() const
    {
        std::string result(size(), '\0');
        save(result.end());
        return result;
    }
    
    LazyStringConcatHelper<std::string, LastString, Strings...>
    operator+(const std::string& other) const
    {
        return LazyStringConcatHelper<std::string, LastString, Strings...>(other, *this);
    }
    
private:
    LastString data;
    LazyStringConcatHelper<Strings...> tail;
};

template<>
class LazyStringConcatHelper<>
{
public:
    LazyStringConcatHelper() { }
    
    int size() const { return 0; }
    
    template <typename It>
    void save(It) const { }
    
    LazyStringConcatHelper<std::string>
    operator+(const std::string& other) const
    {
        return LazyStringConcatHelper<std::string>(other, *this);
    }
};

#endif
