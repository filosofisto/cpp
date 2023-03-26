#include <iostream>
#include <string>
#include "Expected.h"
#include "MyException.h"

using namespace std;

int main()
{
    auto expected = Expected<int, exception>::success(10);
    
    cout << expected.get() << endl;
    
    try {
        throw MyException("Some error");
    } catch (MyException& e) {
        auto errorExpected = Expected<int, MyException>::error(e);
        cout << errorExpected.error().what() << endl;
    }
    
    return EXIT_SUCCESS;
}
