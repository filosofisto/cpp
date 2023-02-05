//
// Created by Eduardo Ribeiro Silva on 05/02/2023.
//

#ifndef THREAD_04_REQUEST_H
#define THREAD_04_REQUEST_H

#include <iostream>

using std::cout;
using std::endl;

class Request {
public:
    Request(int id): id{ id } {};
    void process() { cout << "Processing request " << id << endl; }
private:
    int id;
};


#endif //THREAD_04_REQUEST_H
