#ifndef SEAT_H
#define SEAT_H

#include <string>
#include<iostream>
using namespace std;
class Seat {
private:
    int row;
    int number;
    bool occupied;
public:
    Seat(int r = 0, int n = 0, bool occ = false);
    Seat(const Seat &other);
    Seat& operator=(const Seat &other);
    ~Seat();

    bool isAvailable() const;
    void occupy();
    void release();

    string getId() const; 
};

#endif
