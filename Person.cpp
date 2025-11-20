#include "Person.h"
#include <iostream>
using namespace std;
Person::Person(const string &id, const string &name,
               const string &email, const string &phone)
    : Entity(id), name(name), email(email), phone(phone) {}

Person::Person(const Person &other)
    : Entity(other), name(other.name), email(other.email), phone(other.phone) {}

Person& Person::operator=(const Person &other) {
    if (this != &other) {
        Entity::operator=(other);
        name = other.name;
        email = other.email;
        phone = other.phone;
    }
    return *this;
}

Person::~Person() {}

string Person::getName() const { return name; }
string Person::getEmail() const { return email; }
string Person::getPhone() const { return phone; }

void Person::setName(const string &n) { name = n; }
void Person::setEmail(const string &e) { email = e; }
void Person::setPhone(const string &p) { phone = p; }

void Person::info() const {
    cout << "Person[" << id << "] - " << name
              << " | Email: " << email
              << " | Phone: " << phone << endl;
}
