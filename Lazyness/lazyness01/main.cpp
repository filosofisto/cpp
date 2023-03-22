#include <iostream>
#include "LazyVal.h"

using namespace std;

int main()
{
    auto hugeCalculation = []() { 
        cout << "That is a huge calculation that I want put the result on cache and execute only once and thread safe" << endl;
        return 100;
    };
    
    auto lazyValCalculation{ make_lazy_val(hugeCalculation) };
    
    cout << static_cast<const decltype(lazyValCalculation)&>(lazyValCalculation) << endl;
    cout << static_cast<const decltype(lazyValCalculation)&>(lazyValCalculation) << endl;

    return EXIT_SUCCESS;
}
