#include<bits/stdc++.h>
#include"Booking.h"
using namespace std;

// Them mot doi tuong ve moi vao danh sach quan ly
void Booking::addTicket(const Ticket& t) { 
    tickets.push_back(t); 
}

// Xoa hoan toan mot ve khoi danh sach dua tren ID (Xoa han khoi bo nho)
void Booking::removeTicket(string id) {
    for (auto it = tickets.begin(); it != tickets.end(); ++it) {
        if (it->getId() == id) {
            tickets.erase(it); // Lenh xoa phan tu khoi vector
            cout << "Da xoa ve " << id << " khoi danh sach." << endl;
            return;
        }
    }
    cout << "Khong tim thay ve co ma " << id << " de xoa." << endl;
}

// Lay toan bo danh sach ve hien co (tra ve tham chieu de co the chinh sua truc tiep)
vector<Ticket>& Booking::getTickets() { 
    return tickets; 
}

// Tim kiem ve theo ID va tra ve con tro (de co the sua doi thong tin ve do)
Ticket* Booking::findTicket(const string& id) {
    for(auto &it : tickets) {
        if(it.getId() == id) {
            return &it; // Tra ve dia chi cua ve tim thay
        }
    }
    return nullptr; // Tra ve null neu khong tim thay
}

// Thuc hien huy ve: Chuyen trang thai sang "Da huy" va tuy chon co xoa khoi danh sach luon hay khong
void Booking::cancelTicket(const string& id, bool removeAfterCancel) {
    for (auto &t : tickets) {
        if (t.getId() == id) {
            t.cancel(); // Goi ham cancel() cua class Ticket de doi trang thai ve
            
            // Neu bien removeAfterCancel la true thi xoa luon ve khoi vector
            if (removeAfterCancel) {
                removeTicket(id); 
            }
            return;
        }
    }
    cout << "Khong tim thay ve co ma " << id << " de huy." << endl;
}
