#ifndef EXPECTED_H
#define EXPECTED_H

#include <stdexcept>
#include <optional>

template <typename T, typename E>
class Expected
{
public:
    Expected() { }
    
    Expected(const Expected& source): m_valid(source.m_valid)
    {
        if (m_valid) {
            new (&m_value) T(source.m_value);
        } else {
            new (&m_error) E(source.m_error);
        }
    }
    
    Expected(Expected&& source): m_valid(source.m_valid)
    {
        if (m_valid) {
            new (&m_value) T(std::move(source.m_value));
        } else {
            new (&m_error) E(std::move(source.m_error));
        }
    }

    ~Expected()
    {
        if (m_valid) {
            m_value.~T();
        } else {
            m_error.~E();
        }
    }
    
    T& get()
    {
        if (!m_valid) {
            throw std::logic_error("Missing a value");
        }
        
        return m_value;
    }
    
    E& error()
    {
        if (m_valid) {
            throw std::logic_error("There is no error");
        }
        
        return m_error;
    }
    
    template <typename... Args>
    static Expected success(Args&&... params)
    {
        Expected result;
        result.m_valid = true;
        new (&result.m_value) T(std::forward<Args>(params)...);
        
        return result;
    }
    
    template <typename... Args>
    static Expected error(Args&&... params)
    {
        Expected result;
        result.m_valid = false;
        new (&result.m_error) E(std::forward<Args>(params)...);
        
        return result;
    }
    
    Expected& operator=(Expected other)
    {
        swap(other);
        return *this;
    }

    operator bool() const
    {
        return m_valid;
    }

    operator std::optional<T>() const
    {
        if (m_valid) {
            return m_value;
        } else {
            return std::optional<T>();
        }
    }
private:
    void swap(Expected& other)
    {
        using std::swap;
        using std::move;
        
        if (m_valid) {
            if (other.m_valid) {
                swap(m_value, other.m_value);
            } else {
                auto temp = move(other.m_error);
                other.m_error.~E();
                new (&other.m_value) T(move(m_value));
                m_value.~T();
                new (&m_error) E(move(temp));
                swap(m_valid, other.m_valid);
            }
        } else {
            if (other.m_valid) {
                other.swap(*this);
            } else {
                swap(m_error, other.m_error);
            }
        }
    }
    
    union {
        T m_value;
        E m_error;
    };
    
    bool m_valid;
};

    
#endif
