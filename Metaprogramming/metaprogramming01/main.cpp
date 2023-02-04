#include <iostream>
#include <chrono>

template <unsigned char f>
class Factorial
{
public:
    static const unsigned long long value { f * Factorial<f-1>::value };
};

template<>
class Factorial<0>
{
public:
    static const unsigned long long value { 1 };
};

unsigned long long fat(unsigned char n)
{
    if (n == 1) return 1;
    return n * fat(n-1);
}

int main() {
    using std::cout;
    using std::endl;
    using std::milli;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;

    auto start { high_resolution_clock::now() };
    unsigned long long constFat6 = Factorial<60>::value;
    auto end { high_resolution_clock::now() };
    auto diff { end - start };
    cout << constFat6 << " - const duration: " << duration<double, milli> { diff }.count() << "ms" << endl;

    start = high_resolution_clock::now();
    unsigned long long oldFat6 = fat(10);
    end = high_resolution_clock::now();
    diff = end - start;
    cout << oldFat6 << " - old duration: " << duration<double, milli> { diff }.count() << "ms" << endl;


    return EXIT_SUCCESS;
}
