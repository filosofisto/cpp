#include <iostream>
#include "LazyStringConcatHelper.h"

using namespace std;

int main()
{
    LazyStringConcatHelper lazyStringConcat;
    string name = "Eduardo ";
    string surname = "Silva";
    
    const string fullname = lazyStringConcat + surname + ", " + name;
    
    cout << fullname << endl;
    
    return EXIT_SUCCESS;
}
