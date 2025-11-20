#include "datveo.h"

vector<Seat> BookingAlgorithm::checkAvailableSeats(const Showtime& showtime) {
    vector<Seat> availableSeats;
    vector<Seat> allSeats = showtime.getSeats();
    
    for (const auto& seat : allSeats) {
        if (seat.isAvailable()) {
            availableSeats.push_back(seat);
        }
    }
    
    return availableSeats;
}

void BookingAlgorithm::displayAvailableSeats(const Showtime& showtime) {
    vector<Seat> available = checkAvailableSeats(showtime);
    
    cout << "\n--- DANH SACH GHE TRONG ---\n";
    if (available.empty()) {
        cout << "Khong co ghe nao trong!\n";
        return;
    }
    
    cout << "Cac ghe trong: ";
    for (size_t i = 0; i < available.size(); ++i) {
        cout << available[i].getId();
        if (i < available.size() - 1) cout << ", ";
    }
    cout << "\nTong so: " << available.size() << " ghe trong\n";
}

int BookingAlgorithm::countAvailableSeats(const Showtime& showtime) {
    vector<Seat> available = checkAvailableSeats(showtime);
    return available.size();
}

Seat* BookingAlgorithm::findSeatById(vector<Seat>& seats, const string& seatId) {
    for (auto& seat : seats) {
        if (seat.getId() == seatId) {
            return &seat;
        }
    }
    return nullptr;
}

bool BookingAlgorithm::bookSeat(Showtime& showtime, Booking& booking, 
                               const string& seatId, double price, 
                               const string& ticketId) {
    
    vector<Seat> seats = showtime.getSeats();
    Seat* targetSeat = findSeatById(seats, seatId);
    
    if (targetSeat == nullptr) {
        cout << "Khong tim thay ghe " << seatId << "!\n";
        return false;
    }
    
    if (targetSeat->isAvailable()) {
        targetSeat->occupy();
        
        string finalTicketId = ticketId.empty() ? 
            "T" + to_string(booking.getTickets().size() + 1) : ticketId;
        
        Ticket newTicket(finalTicketId, &showtime, *targetSeat, price, TicketStatus::BOOKED);
        booking.addTicket(newTicket);
        showtime.setSeats(seats);
        
        cout << "Dat ve thanh cong! Ghe " << seatId 
             << " | Ma ve: " << finalTicketId << endl;
        return true;
    } else {
        cout << "Ghe " << seatId << " da duoc dat!\n";
        return false;
    }
}

bool BookingAlgorithm::cancelTicket(Showtime& showtime, Booking& booking, 
                                  const string& ticketId) {
    
    Ticket* ticket = booking.findTicket(ticketId);
    
    if (ticket == nullptr) {
        cout << "Khong tim thay ve " << ticketId << "!\n";
        return false;
    }
    
    if (ticket->getStatus() == TicketStatus::CANCELED) {
        cout << "Ve " << ticketId << " da bi huy truoc do!\n";
        return false;
    }
    
    Seat seat = ticket->getSeatInfo();
    string seatId = seat.getId();
    vector<Seat> seats = showtime.getSeats();
    Seat* targetSeat = findSeatById(seats, seatId);
    
    if (targetSeat != nullptr) {
        targetSeat->release();
        showtime.setSeats(seats);
        ticket->cancel();
        
        cout << "Huy ve thanh cong! Ghe " << seatId 
             << " da duoc tra ve trang thai trong.\n";
        return true;
    } else {
        cout << "Loi: Khong the cap nhat trang thai ghe!\n";
        return false;
    }
}
