#include <iostream>
#include "Person.h"

void processPerson(Person p /* object by value */) {
    // do some processing
}

void processPersonRef(const Person& p /* by ref */) {
    // do some processing
}

using std::cout;
using std::endl;

int main() {
    Person me { "Eduardo", "Silva", 51 };
    processPerson(me);

    cout << endl;

    Person djo { "Djovana", "Bronnemann", 51 };
    processPersonRef(djo);

    return EXIT_SUCCESS;
}
