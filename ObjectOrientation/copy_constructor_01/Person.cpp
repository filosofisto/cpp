//
// Created by Eduardo Ribeiro Silva on 07/02/2023.
//

#include "Person.h"

using std::cout;
using std::endl;
using std::move;

Person::Person() {
    cout << "Default Constructor: " << m_first_name << endl;
}

Person::Person(std::string firstName, std::string lastName, int age)
    : m_first_name{ move(firstName) }, m_last_name{ move(lastName) }, m_age{ age } {
    cout << "Complete Constructor: " << m_first_name << endl;
}

Person::~Person() {
    cout << "Destructor: " << m_first_name << endl;
}

const std::string &Person::getFirstName() const {
    return m_first_name;
}

const std::string &Person::getLastName() const {
    return m_last_name;
}

int Person::getAge() const {
    return m_age;
}

Person::Person(const Person &person):
    m_first_name { person.m_first_name },
    m_last_name { person.m_last_name },
    m_age { person.m_age } {
    cout << "Copy Constructor: " << m_first_name << endl;
}
