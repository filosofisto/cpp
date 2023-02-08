//
// Created by Eduardo Ribeiro Silva on 08/02/2023.
//

#ifndef OBJECT_POOL_01_EXPENSIVEOBJECT_H
#define OBJECT_POOL_01_EXPENSIVEOBJECT_H

#include <array>

class ExpensiveObject {
public:
    ExpensiveObject() = default;
    virtual ~ExpensiveObject() = default;
private:
    // An expensive data member
    std::array<double, 4*1024*1024> m_data{};
};


#endif //OBJECT_POOL_01_EXPENSIVEOBJECT_H
