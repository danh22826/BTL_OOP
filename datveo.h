// File: BookingAlgorithm.h
#ifndef BOOKINGALGORITHM_H
#define BOOKINGALGORITHM_H
#include "Showtime.h"
#include "Booking.h"
#include "Ticket.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class BookingAlgorithm {
public:
    static vector<Seat> checkAvailableSeats(const Showtime& showtime);
    static void displayAvailableSeats(const Showtime& showtime);
    static bool bookSeat(Showtime& showtime, Booking& booking, 
                        const string& seatId, double price, 
                        const string& ticketId = "");
    static bool cancelTicket(Showtime& showtime, Booking& booking, 
                           const string& ticketId);
    static Seat* findSeatById(vector<Seat>& seats, const string& seatId);
    static int countAvailableSeats(const Showtime& showtime);
};

#endif
