#include "Seat.h"
#include <sstream>
#include<bits/stdc++.h>
using namespace std;
Seat::Seat(int r, int n, bool occ)
    : row(r), number(n), occupied(occ) {}

Seat::Seat(const Seat &other)
    : row(other.row), number(other.number), occupied(other.occupied) {}

Seat& Seat::operator=(const Seat &other) {
    if (this != &other) {
        row = other.row;
        number = other.number;
        occupied = other.occupied;
    }
    return *this;
}

Seat::~Seat() {}

bool Seat::isAvailable() const { return !occupied; }
void Seat::occupy() { occupied = true; }
void Seat::release() { occupied = false; }

string Seat::getId() const {
    char rowLetter = 'A' + (row - 1);
    ostringstream oss;
    oss << rowLetter << number;
    return oss.str();
}
