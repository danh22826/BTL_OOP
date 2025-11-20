#include "Showtime.h"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
Showtime::Showtime(const string &id, const Movie &mv,
                   const string &time, double p,
                   int rows, int cols)
    : Entity(id), movie(mv), dateTime(time), price(p) {
    for (int r = 1; r <= rows; ++r)
        for (int c = 1; c <= cols; ++c)
            seats.emplace_back(r, c, false); // Tạo ghế tại vị trí (hàng r, cột c)
            // false = ghế Ban đầu luôn trống
}

Showtime::Showtime(const Showtime &other)
    : Entity(other), movie(other.movie), dateTime(other.dateTime),
      price(other.price), seats(other.seats) {}

Showtime& Showtime::operator=(const Showtime &other) {
    if (this != &other) { // tránh tự gán chính nó
        Entity::operator=(other); // gọi operator = lớp cha
        movie = other.movie; // sao chép toàn bộ thuộc tính (movie, ngày giờ, giá vé, ghế ngồi)
        dateTime = other.dateTime;
        price = other.price;
        seats = other.seats;
    }
    return *this; // trả về đối tượng sau khi gán
}

Showtime::~Showtime() {}

bool Showtime::checkSeatAvailable(const string &seatId) const {
    for (const auto &s : seats) // duyệt toàn bộ ghế
        if (s.getId() == seatId) // tìm đúng mã ghế
            return s.isAvailable(); // trả về trngj thái trống hay kh
	   return false; // kh tìm thấy ghế or đã đặt
}

bool Showtime::occupySeat(const string &seatId) {
    for (auto &s : seats) // duyệt toàn bộ danh sách ghế của suất chiếu
        if (s.getId() == seatId && s.isAvailable()) { // kiểm tra cùng mã ghế
            s.occupy(); // đánh dấu ghế đã đặt
            return true; // đặt thành công
        }
    return false; // đặt kh thành công
}

bool Showtime::releaseSeat(const string &seatId) { 
    for (auto &s : seats)
        if (s.getId() == seatId && !s.isAvailable()) { // kiểm tra khác mã ghế
            s.release(); // trả ghế về trạng thái trống
            return true; // hủy thành công
        }
    return false; // sai nếu ghế không tồn tại hoặc đang trống
}

int Showtime::totalAvailableSeats() const {
    int count = 0;
    for (const auto &s : seats)
        if (s.isAvailable()) ++count; // tăng lượt khi ghế trống
    return count; // trả về số ghế trống
}

void Showtime::info() const { // in ra màn hình thông tin cơ bản của suất chiếu
    cout << "Showtime[" << id << "] | Movie: ";
    movie.info();
    cout << "Time: " << dateTime
              << " | Price: " << price
              << " | Available: " << totalAvailableSeats() << " seats\n";
}

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
    return seats;
}

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
