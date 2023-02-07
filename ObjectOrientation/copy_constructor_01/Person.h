//
// Created by Eduardo Ribeiro Silva on 07/02/2023.
//

#ifndef COPY_CONSTRUCTOR_01_PERSON_H
#define COPY_CONSTRUCTOR_01_PERSON_H

#include <iostream>
#include <string>

class Person {
public:
    Person();
    Person(const Person& person); // copy constructor
    Person(std::string firstName, std::string lastName, int age);
    virtual ~Person();

    [[nodiscard]] const std::string& getFirstName() const;
    [[nodiscard]] const std::string& getLastName() const;
    [[nodiscard]] int getAge() const;
private:
    std::string m_first_name, m_last_name;
    int m_age { 0 };
};

#endif //COPY_CONSTRUCTOR_01_PERSON_H
