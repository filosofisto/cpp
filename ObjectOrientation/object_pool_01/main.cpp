#include <iostream>
#include <memory>
#include <chrono>
#include "ObjectPool.h"
#include "ExpensiveObject.h"

using std::shared_ptr;
using std::cout;
using std::endl;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::milli;
using MyPool = ObjectPool<ExpensiveObject>;

shared_ptr<ExpensiveObject> getExpensiveObject(MyPool& pool) {
    // Obtain an ExpensiveObject object from the pool
    auto object { pool.acquireObject() };

    // Populate the object, etc

    return object;
}

void processExpensiveObject(ExpensiveObject* object) {
    // Do some processing
}

int main() {
    const size_t NumberOfIterations { 10'000 };
    cout << "Starting loop using Pool..." << endl;
    MyPool requestPool;

    auto start1 { steady_clock::now() };
    for (size_t i { 0 }; i < NumberOfIterations; ++i) {
        auto object { getExpensiveObject(requestPool) };
        processExpensiveObject(object.get());
    }
    auto end1 { steady_clock::now() };
    auto diff1 { end1 - start1 };
    cout << "Duration (using pool): " << duration<double, milli>(diff1).count() << endl;

    auto start2 { steady_clock::now() };
    for (size_t i { 0 }; i < NumberOfIterations; ++i) {
        auto object { new ExpensiveObject{} };
        processExpensiveObject(object);
        delete object;
        object = nullptr;
    }
    auto end2 { steady_clock::now() };
    auto diff2 { end2 - start2 };
    cout << "Duration: " << duration<double, milli>(diff2).count() << endl;

    return EXIT_SUCCESS;
}
