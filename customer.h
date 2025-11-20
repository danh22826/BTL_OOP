#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Showtime.h"
#include "Booking.h"
#include "Ticket.h"
#include "Person.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Customer : public Person {
private:
    vector<Ticket> bookingHistory;
public:
   Customer(const string &id = "", const string &name = "",
             const string &email = "", const string &phone = "");

    Customer(const Customer &other);
    Customer& operator=(const Customer &other);
    virtual ~Customer();

    // dat ve
    void bookTicket(Booking &booking, Showtime &show, int seatNumber);

    // huy ve
    void cancelTicket(Booking &booking, int ticketId);

    // xem lich su ve
    void viewHistory() const ;
    void addTicketToHistory(const Ticket& ticket);
    const vector<Ticket>& getBookingHistory() const;
    
};

/*
class Customer : public Person {
private:
     vector<Ticket> bookingHistory;

public:
	//Dung gia tri tu class ngoai nhieu qua dung tham chieu cho do kho bo nho
    Customer(const string &id = "", const string &name = "",
             const string &email = "", const string &phone = "");

    Customer(const Customer &other);
    Customer& operator=(const Customer &other);
    virtual ~Customer();

    void addBookingToHistory(const string &bookingId);
    void printBookingHistory() const;

    virtual void info() const override;
};
*/
#endif
