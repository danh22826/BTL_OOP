#include "Ticket.h"
#include<bits/stdc++.h>
using namespace std;

Ticket::Ticket(const string &id, Showtime *st, const Seat &s, double p, TicketStatus stt)
    : Entity(id),showtime(st),seatInfo(s),price(p),status(stt) {}

Ticket::Ticket()
    : Entity(""), showtime(nullptr), seatInfo(), price(0), status(TicketStatus::CANCELED) {}


// In thong tin ve 
void Ticket::printTicket() const {
    // Neu con tro showtime bi Null (chua lien ket voi suat chieu nao) thi bao loi va dung lai.
    if (showtime == nullptr) {
        cout << "--- VE KHONG HOP LE ---"<<endl;
        return;
    }

    // Lay thong tin Phim thong qua con tro showtime
    Movie movie = showtime->getMovie();
    string seatId = seatInfo.getId();
    string statusNow = (status == TicketStatus::BOOKED) ? "Dat" : "Huy";

    cout << "===============VE XEM PHIM===============\n";
    cout << "+=======================================+\n";
    cout << "| Phim: " << movie.getTitle() << endl;
    cout << "| Thoi gian: " << showtime->getDateTime() << endl;
    cout << "| Thoi luong: " << movie.getDuration() << " phut" << endl;
    cout << "+---------------------------------------+\n";
    cout << "| Ghe: " << seatId
         << " | Gia: " << fixed << setprecision(0) << price << " VND\n";
    
    cout << "| Ma ve: "  << id
         << " | Trang thai: " << statusNow << "\n";
    cout << "+=======================================+\n\n";
}


// Ham xu ly huy ve
void Ticket::cancel() {
    // Kiem tra logic: Neu ve da o trang thai HUY roi thi khong can lam gi ca
    if (status == TicketStatus::CANCELED) {
        cout << "Ve da duoc huy truoc do!\n";
        return;
    }
    
    // Cap nhat trang thai sang CANCELED
    status = TicketStatus::CANCELED;
    cout << "Ve da duoc huy thanh cong!\n";
}


// Tra ve con tro den suat chieu cua ve nay
Showtime* Ticket::getShowtime() const {
    return showtime;
}

// Tra ve thong tin ghe ngoi cua ve nay
Seat Ticket::getSeatInfo() const {
    return seatInfo;
}

// Tra ve trang thai hien tai (Dat hay Huy)
TicketStatus Ticket::getStatus() const {
    return status;
}


// Ham in thong tin dang dong don gian
void Ticket::info() const {
    // Kiem tra an toan con tro
    if (showtime == nullptr) {
        cout << "Ve[" << id << "]: Khong hop le\n";
        return;
    }

    // Chuyen doi Enum sang chuoi ky tu tieng Anh
    string statusStr = (status == TicketStatus::BOOKED) ? "DAT" : "HUY";

    cout << "Ve[" << id << "]: "
         << showtime->getMovie().getTitle()
         << " - Ghe: " << seatInfo.getId()
         << " - Trang thai: " << statusStr << "\n";
}
