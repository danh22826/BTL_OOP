#include "Customer.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// =======================================================
// Ð?NH NGHIA CONSTRUCTOR, DESTRUCTOR (S?a l?i liên k?t)
// =======================================================

// Constructor
Customer::Customer(const string &id, const string &name,
                   const string &email, const string &phone)
    : Person(id, name, email, phone) {}

// Constructor sao chép
Customer::Customer(const Customer &other)
    : Person(other), bookingHistory(other.bookingHistory) {}

// Operator gán
Customer& Customer::operator=(const Customer &other) {
    if (this != &other) {
        Person::operator=(other);
        bookingHistory = other.bookingHistory;
    }
    return *this;
}

// Destructor
Customer::~Customer() {}


// =======================================================
// Ð?NH NGHIA HÀM NGHI?P V? (Ðã có logic)
// =======================================================

// Dat ve - VERSION HOAN CHINH
void Customer::bookTicket(Booking &booking, Showtime &show, int seatNumber) {
    // L?y gh?
    vector<Seat> seats = show.getSeats();
    
    // Kiem tra so ghe hop le
    if (seatNumber <= 0 || seatNumber > (int)seats.size()) {
        cout << "? Seat not found!\n";
        return;
    }
    
    Seat s = seats[seatNumber - 1];
    
    // Kiem tra ghe da dat chua
    if (!s.isAvailable()) {
        cout << "? Seat already booked!\n";
        return;
    }
    
    // Ðánh d?u gh? dã d?t và t?o Ticket
    
    // Dánh d?u trong d?i tu?ng Seat
    s.occupy(); 
    
    // Cap nhat lai gh? trong showtime (can setSeats trong Showtime.h)
    seats[seatNumber - 1] = s;
    show.setSeats(seats); 
    
    // Tao ticket ID dang string
    string ticketId = "T" + to_string(booking.getTickets().size() + 1); // C?n Booking::getTickets()
    
    // Tao ticket moi
    Ticket newTicket(ticketId, &show, s, show.getPrice(), TicketStatus::BOOKED); 
    
    // Them vao booking (C?n Booking::addTicket)
    booking.addTicket(newTicket);
    
    // Them vao lich su (Nhi?m v? Ngu?i 3)
    bookingHistory.push_back(newTicket);
    
    cout << "? Ticket booked successfully! Ma ve: " << ticketId << "\n";
}

// Huy ve - VERSION HOAN CHINH
void Customer::cancelTicket(Booking &booking, int seatNumber) {
    string seatId = "A" + to_string(seatNumber); // gh? A7, A8, ...
    bool found = false;

    for (auto &t : booking.getTickets()) {
        if (t.getSeatInfo().getId() == seatId) {
            t.cancel();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "? Ticket not found in history!" << endl;
}
// Xem l?ch s? (viewHistory)
void Customer::viewHistory() const {
    cout << "\n--- Lich su dat ve cua " << getName() << " ---\n";
    if (bookingHistory.empty()) {
        cout << "(Chua co ve nao duoc dat trong lich su.)\n";
        return;
    }
    for (const auto& ticket : bookingHistory) {
        ticket.info();
    }
}
void Customer::addTicketToHistory(const Ticket& ticket) {
    // Hàm này ch? có m?t nhi?m v? là thêm vé vào l?ch s?
    bookingHistory.push_back(ticket);
}
const vector<Ticket>& Customer::getBookingHistory() const {
    return bookingHistory;
}
