#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
using namespace std;
class Entity {
protected:
    string id;
public:
    explicit Entity(const string &id = "");

    Entity(const Entity &other);

    Entity& operator=(const Entity &other);

    virtual ~Entity();

    string getId() const;
    void setId(const string &newId);

    virtual void info() const = 0;
};

#endif
