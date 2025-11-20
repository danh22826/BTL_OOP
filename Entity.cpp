#include "Entity.h"
using namespace std;
Entity::Entity(const string &id) : id(id) {}

Entity::Entity(const Entity &other) : id(other.id) {}
Entity::~Entity() {}

Entity& Entity::operator=(const Entity &other) {
    if (this != &other) {
        id = other.id;
    }
    return *this;
}


string Entity::getId() const {
    return id;
}

void Entity::setId(const string &newId) {
    id = newId;
}
