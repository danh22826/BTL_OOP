#include "Ticket.h"
#include<bits/stdc++.h>
using namespace std;

Ticket::Ticket(const string &id, Showtime *st, const Seat &s, double p, TicketStatus stt)
    : Entity(id), showtime(st), seatInfo(s), price(p), status(stt) {}

Ticket::Ticket()
    : Entity(""), showtime(nullptr), seatInfo(), price(0), status(TicketStatus::CANCELED) {}

void Ticket::printTicket() const {
    if (showtime == nullptr) {
        cout << "--- VE KHONG HOP LE ---"<<endl;
        return;
    }

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

void Ticket::cancel() {
    if (status == TicketStatus::CANCELED) {
        cout << "Ve da duoc huy truoc do!\n";
        return;
    }
    status = TicketStatus::CANCELED;
    cout << "Ve da duoc huy thanh cong!\n";
}

Showtime* Ticket::getShowtime() const {
    return showtime;
}

Seat Ticket::getSeatInfo() const {
    return seatInfo;
}

TicketStatus Ticket::getStatus() const {
    return status;
}

void Ticket::info() const {
    if (showtime == nullptr) {
        cout << "Ve[" << id << "]: Khong hop le\n";
        return;
    }

    string statusStr = (status == TicketStatus::BOOKED) ? "BOOKED" : "CANCELED";

    cout << "Ve[" << id << "]: "
         << showtime->getMovie().getTitle()
         << " - Ghe: " << seatInfo.getId()
         << " - Trang thai: " << statusStr << "\n";
}

