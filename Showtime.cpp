#include "Showtime.h"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

// --- HAM KHOI TAO (CONSTRUCTOR) ---
// Khoi tao suat chieu voi thong tin phim, thoi gian, gia ve va tao danh sach ghe ngoi
Showtime::Showtime(const string &id, const Movie &mv,
                   const string &time, double p,
                   int rows, int cols)
    : Entity(id), movie(mv), dateTime(time), price(p) {
    
    // Vong lap tao danh sach ghe dua tren so hang (rows) va so cot (cols)
    for (int r = 1; r <= rows; ++r)
        for (int c = 1; c <= cols; ++c)
            // emplace_back giup tao doi tuong Seat va day vao vector ngay lap tuc
            // false: nghia la trang thai ban dau la ghe TRONG (chua co nguoi)
            seats.emplace_back(r, c, false); 
}

// --- COPY CONSTRUCTOR (KHOI TAO SAO CHEP) ---
// Tao mot suat chieu moi giong het suat chieu cu (other)
Showtime::Showtime(const Showtime &other)
    : Entity(other), movie(other.movie), dateTime(other.dateTime),
      price(other.price), seats(other.seats) {}

// --- TOAN TU GAN (=) ---
// Copy du lieu tu suat chieu nay sang suat chieu khac
Showtime& Showtime::operator=(const Showtime &other) {
    if (this != &other) { // Kiem tra de tranh viec tu gan chinh minh (a = a)
        Entity::operator=(other); // Goi ham gan cua lop cha (Entity) de copy ID
        
        // Sao chep toan bo thuoc tinh
        movie = other.movie; 
        dateTime = other.dateTime;
        price = other.price;
        seats = other.seats; // Copy nguyen ca danh sach ghe
    }
    return *this; // Tra ve doi tuong sau khi da gan gia tri
}

Showtime::~Showtime() {}

// --- KIEM TRA TRANG THAI GHE ---
bool Showtime::checkSeatAvailable(const string &seatId) const {
    for (const auto &s : seats) // Duyet qua tat ca cac ghe
        if (s.getId() == seatId) // Tim thay ghe co ID trung khop
            return s.isAvailable(); // Tra ve True neu ghe trong, False neu da dat
            
    return false; // Tra ve False neu khong tim thay ghe nay trong suat chieu
}

// --- DAT GHE (KHOA GHE) ---
// Chuyen trang thai ghe tu TRONG -> DA DAT
bool Showtime::occupySeat(const string &seatId) {
    for (auto &s : seats) // Duyet qua danh sach ghe (dung & de co the sua doi truc tiep)
        // Chi dat duoc khi: Tim dung ID va Ghe do phai dang TRONG
        if (s.getId() == seatId && s.isAvailable()) { 
            s.occupy(); // Goi ham cua class Seat de doi status thanh false
            return true; // Bao dat thanh cong
        }
    return false; // Bao that bai (do ghe khong ton tai hoac da co nguoi dat truoc)
}

// --- HUY GHE (MO KHOA GHE) ---
// Chuyen trang thai ghe tu DA DAT -> TRONG (Dung khi khach huy ve)
bool Showtime::releaseSeat(const string &seatId) { 
    for (auto &s : seats)
        // Chi huy duoc khi: Tim dung ID va Ghe do dang BI DAT (!isAvailable)
        if (s.getId() == seatId && !s.isAvailable()) { 
            s.release(); // Goi ham cua class Seat de doi status thanh true
            return true; // Bao huy thanh cong
        }
    return false; // Bao that bai (ghe khong ton tai hoac ghe von da trong roi)
}

// --- THONG KE GHE TRONG ---
int Showtime::totalAvailableSeats() const {
    int count = 0;
    for (const auto &s : seats)
        if (s.isAvailable()) ++count; // Dem so luong ghe dang trong
    return count;
}

// --- IN THONG TIN ---
void Showtime::info() const { 
    cout << "Showtime[" << id << "] | Movie: ";
    movie.info(); // Goi ham in thong tin phim
    cout << "Time: " << dateTime
         << " | Price: " << price
         << " | Available: " << totalAvailableSeats() << " seats\n";
}

// --- CAC HAM GETTER (LAY THONG TIN) ---

Movie Showtime::getMovie() const {
    return movie;
}

string Showtime::getDateTime() const {
    return dateTime;
}

double Showtime::getPrice() const {
    return price;
}

std::vector<Seat> Showtime::getSeats() const {
    return seats; // Tra ve toan bo danh sach ghe
}

// --- CAC HAM SETTER (CAP NHAT THONG TIN) ---

void Showtime::setMovie(const Movie &mv) {
    movie = mv;
}

void Showtime::setDateTime(const string &dt) {
    dateTime = dt;
}

void Showtime::setPrice(double p) {
    price = p;
}

void Showtime::setSeats(const vector<Seat> &s) {
    seats = s;
}
