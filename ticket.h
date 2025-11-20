#ifndef TICKET_H
#define TICKET_H
#include "Entity.h"     
#include "Showtime.h"   
#include "Seat.h"      
#include "Movie.h"
#include <iostream>
#include <string>
using namespace std;
enum class TicketStatus { BOOKED, CANCELED };
class Ticket : public Entity {
private:
    Showtime* showtime; //thong tin ve dung lai nhieu lan
    Seat      seatInfo; 
    double    price;
    TicketStatus status;

public:
    Ticket(const string &id = "", Showtime *st = nullptr, 
           const Seat &s = Seat(), double p = 0,TicketStatus=TicketStatus::BOOKED);
    Ticket();     
    void printTicket() const;
    void cancel();
    Showtime* getShowtime() const;
    Seat      getSeatInfo() const;
    TicketStatus getStatus() const;
    virtual void info() const override;
};

#endif
