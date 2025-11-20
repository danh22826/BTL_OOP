#ifndef BOOKING_H
#define BOOKING_H
#include<bits/stdc++.h>
#include"Ticket.h"
using namespace std;
class Booking {
    vector<Ticket> tickets;
public:
    void addTicket(const Ticket& t) ;
    void removeTicket(string id) ;
    vector<Ticket>& getTickets(); 
    Ticket* findTicket(const string& id);
    void cancelTicket(const string& id, bool removeAfterCancel = false);
};
#endif
