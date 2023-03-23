#include <iostream>
#include "FiboCache.h"

using namespace std;

int main()
{
    FiboCache fib;
    
    for (int i = 0; i < 10; ++i) {
        cout << "Fib( " << i << "): " << fib.calc(i) << endl;
    }
    
    return EXIT_SUCCESS;
}
