// Staff.cpp
#include "Staff.h"
#include <iostream>
using namespace std;
Staff::Staff()
{
    id = email = department = "";
}

Staff::Staff(const string &id, const string &name,
             const string &email, const string &phone,
             const string &dept)
    : Person(id, name, email, phone), department(dept) {}
Staff::~Staff() {};

void Staff::info() const
{
    Person::info();
    cout << "  Department: " << department << endl;
}
// sua thong tin ve toi gian va gia
void Staff::manageShowtime(Showtime &showtime, const string &newTime, double newPrice)
{
    cout << "Nhan vien " << name << " dang cap nhat suat chieu " << showtime.getId() << "..." << endl;

    showtime.setDateTime(newTime);
    showtime.setPrice(newPrice);

    cout << "Cap nhat thanh cong." << endl;
}
//  Them xuat chieu theo 
void Staff::addShowtime(const Showtime &show)
{
    showtimes.push_back(show);
    cout << "them xuat chieu "
         << show.getMovie().getTitle()
         << " - " << show.getDateTime()<< endl;
}
//  Xoa xuat chieu theo thoi gian
void Staff::removeShowtime(const string &time)
{
    for (auto it = showtimes.begin(); it != showtimes.end(); ++it)
    {
        if (it->getDateTime() == time)
        {
            cout << "?xoa xua chieu: "
                 << it->getMovie().getTitle()
                 << " - " << it->getDateTime() << endl;
            showtimes.erase(it);
            return;
        }
    }
    cout << " Khong tim thay xuat chieu : " << time << endl;
}

string Staff::getRole() const {
    return department; 
}
