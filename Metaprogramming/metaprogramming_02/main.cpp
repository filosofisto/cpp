#include <iostream>

using std::cout;
using std::endl;

template <int i>
class Loop
{
public:
    template <typename FuncType>
    static inline void run(FuncType f) {
        Loop<i-1>::run(f);
        f(i);
    }
};

template <>
class Loop<0>
{
public:
    template <typename FuncType>
    static inline void run(FuncType /* f */) { }
};

void doWork(int i)
{
    cout << "doWork(" << i << ")" << endl;
}

int main() {
    Loop<3>::run(doWork);

    return EXIT_SUCCESS;
}
