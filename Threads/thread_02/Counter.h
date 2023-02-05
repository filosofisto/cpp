//
// Created by Eduardo Ribeiro Silva on 05/02/2023.
//

#ifndef THREAD_02_COUNTER_H
#define THREAD_02_COUNTER_H

class Counter {
public:
    Counter(int id, int numIterations);
    ~Counter() = default;

    void operator()() const;
private:
    int id;
    int numIterations;
};


#endif //THREAD_02_COUNTER_H
