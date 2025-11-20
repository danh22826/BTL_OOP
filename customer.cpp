#include "Customer.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// DINH NGHIA CONSTRUCTOR, DESTRUCTOR
// Constructor (Ham khoi tao co tham so)
// Goi constructor cua lop cha Person de khoi tao cac thong tin co ban
Customer::Customer(const string &id, const string &name,
                   const string &email, const string &phone)
    : Person(id, name, email, phone) {}

// Constructor sao chep (Copy Constructor)
// Sao chep thong tin tu mot khach hang khac (bao gom ca lich su dat ve)
Customer::Customer(const Customer &other)
    : Person(other), bookingHistory(other.bookingHistory) {}

// Toan tu gan (Assignment Operator)
// Copy du lieu tu khach hang khac vao doi tuong hien tai
Customer& Customer::operator=(const Customer &other) {
    if (this != &other) { // Kiem tra de tranh tu gan chinh minh
        Person::operator=(other); // Goi toan tu gan cua lop cha
        bookingHistory = other.bookingHistory; // Copy lich su dat ve
    }
    return *this;
}

// Destructor (Ham huy)
Customer::~Customer() {}


// DINH NGHIA HAM NGHIEP VU

// Dat ve - VERSION HOAN CHINH
void Customer::bookTicket(Booking &booking, Showtime &show, int seatNumber) {
    // Lay danh sach ghe hien tai cua suat chieu
    vector<Seat> seats = show.getSeats();
    
    // Kiem tra so ghe hop le (khong duoc nho hon 0 hoac lon hon tong so ghe)
    if (seatNumber <= 0 || seatNumber > (int)seats.size()) {
        cout << "[!] Ghe khong ton tai!\n";
        return;
    }
    
    // Lay ghe ma khach muon dat (index bat dau tu 0 nen phai tru 1)
    Seat s = seats[seatNumber - 1];
    
    // Kiem tra xem ghe nay da co nguoi dat chua
    if (!s.isAvailable()) {
        cout << "[!] Ghe nay da duoc dat roi!\n";
        return;
    }
    
    // --- BAT DAU QUY TRINH DAT VE ---
    // 1. Danh dau ghe la "dat" trong doi tuong Seat tam thoi
    s.occupy(); 
    
    // 2. Cap nhat lai thong tin ghe do vao danh sach ghe cua suat chieu
    // (Day la buoc quan trong de luu trang thai ghe)
    seats[seatNumber - 1] = s;
    show.setSeats(seats); 
    
    // 3. Tao ID cho ve moi (Vi du: T1, T2...) dua tren so luong ve hien co
    string ticketId = "T" + to_string(booking.getTickets().size() + 1); 
    
    // 4. Khoi tao doi tuong Ticket moi voi thong tin day du
    Ticket newTicket(ticketId, &show, s, show.getPrice(), TicketStatus::BOOKED); 
    
    // 5. Luu ve vao he thong quan ly chung (Booking)
    booking.addTicket(newTicket);
    
    // 6. Luu ve vao lich su ca nhan cua khach hang nay
    bookingHistory.push_back(newTicket);
    
    cout << "[OK] Dat ve thanh cong! Ma ve: " << ticketId << "\n";
}

// Huy ve - VERSION HOAN CHINH
void Customer::cancelTicket(Booking &booking, int seatNumber) {
    // Tao ID ghe tu so thu tu (Vi du: nhap 1 -> "A1")
    // Luu y: Code nay dang gia dinh ghe co dinh dang "A" + so
    string seatId = "A" + to_string(seatNumber); 
    bool found = false;

    // Duyet qua toan bo ve trong he thong Booking de tim ve tuong ung
    for (auto &t : booking.getTickets()) {
        // So sanh ID ghe cua ve voi ghe khach muon huy
        if (t.getSeatInfo().getId() == seatId) {
            t.cancel(); // Goi ham huy ve (chuyen trang thai sang CANCELED)
            found = true;
            cout << "[OK] Da huy ve cho ghe " << seatId << "\n";
            break; // Tim thay va huy xong thi dung vong lap
        }
    }

    if (!found)
        cout << "[!] Khong tim thay ve nao cho ghe nay!" << endl;
}

// Xem lich su dat ve (viewHistory)
void Customer::viewHistory() const {
    cout << "\n--- Lich su dat ve cua " << getName() << " ---\n";
    
    // Kiem tra neu lich su trong
    if (bookingHistory.empty()) {
        cout << "(Chua co ve nao duoc dat trong lich su.)\n";
        return;
    }
    
    // Duyet va in thong tin chi tiet tung ve
    for (const auto& ticket : bookingHistory) {
        ticket.info();
    }
}

// Ham phu tro: Them ve vao lich su (thuong dung khi load du lieu tu file)
void Customer::addTicketToHistory(const Ticket& ticket) {
    bookingHistory.push_back(ticket);
}

// Ham phu tro: Lay danh sach lich su (tra ve tham chieu hang de khong bi sua doi)
const vector<Ticket>& Customer::getBookingHistory() const {
    return bookingHistory;
}
