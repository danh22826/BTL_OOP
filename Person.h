#ifndef PERSON_H
#define PERSON_H
#include<iostream>
#include "Entity.h"
using namespace std;
class Person : public Entity {
protected:
    string name;
    string email;
    string phone;
public:
    Person(const string &id = "", const string &name = "",
           const string &email = "", const string &phone = "");

    Person(const Person &other);
    Person& operator=(const Person &other);
    virtual ~Person();
    string getName() const;
    string getEmail() const;
    string getPhone() const;

    void setName(const string &n);
    void setEmail(const string &e);
    void setPhone(const string &p);

    virtual void info() const override;
};

#endif
