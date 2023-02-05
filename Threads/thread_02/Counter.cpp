//
// Created by Eduardo Ribeiro Silva on 05/02/2023.
//

#include <iostream>
#include "Counter.h"

Counter::Counter(int id, int numIterations)
    : id(id), numIterations(numIterations) {

}

void Counter::operator()() const {
    using std::cout;
    using std::endl;

    for (int i { 0 }; i < numIterations; ++i) {
        cout << "Counter " << id << " has value " << i << "\n";
    }

    cout << endl;
}
