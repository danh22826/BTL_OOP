#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Entity.h"
#include "Person.h"
#include "Movie.h"
#include "Seat.h"
#include "Showtime.h"
#include "Ticket.h"
#include "Booking.h"
#include "customer.h"
#include "Staff.h"
#include "datveo.h"

using namespace std;

void handleStaffAddShowtime(Staff& staff, vector<Showtime>& allShowtimes, const vector<Movie>& allMovies);
void handleStaffRemoveShowtime(Staff& staff, vector<Showtime>& allShowtimes);
void handleStaffManageShowtime(Staff& staff, vector<Showtime>& allShowtimes);
void showStaffMenu(Staff& staff, vector<Showtime>& showtimes, vector<Movie>& movies);
void showCustomerMenu(Customer& customer, Booking& bookingSystem, vector<Showtime>& showtimes);

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressEnterToContinue() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getMenuChoice() {
    int choice;
    cout << "\n> Nhap lua chon: ";
    while (!(cin >> choice)) {
        cout << "[!] Nhap lai so: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

string getStringInput(string prompt) {
    string input;
    cout << prompt;
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, input);
    return input;
}

vector<string> parseCSVLine(const string& line) {
    vector<string> result;
    stringstream ss(line);
    string item;
    while (getline(ss, item, ',')) result.push_back(item);
    return result;
}

void loadMovies(vector<Movie>& movies) {
    ifstream file("movies.csv");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> data = parseCSVLine(line);
        if (data.size() >= 6) {
            try {
                movies.emplace_back(data[0], data[1], data[2], stoi(data[3]), stod(data[4]), data[5]);
            } catch (...) { continue; }
        }
    }
    file.close();
}

void loadCustomers(vector<Customer>& customers) {
    ifstream file("customers.csv");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> data = parseCSVLine(line);
        if (data.size() >= 4) {
            customers.emplace_back(data[0], data[1], data[2], data[3]);
        }
    }
    file.close();
}

void saveCustomers(const vector<Customer>& customers) {
    ofstream file("customers.csv", ios::trunc);
    if (!file.is_open()) return;
    for (const auto& c : customers) {
        file << c.getId() << "," << c.getName() << "," << c.getEmail() << "," << c.getPhone() << endl;
    }
    file.close();
}

void loadStaff(vector<Staff>& staff) {
    ifstream file("staff.csv");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> data = parseCSVLine(line);
        if (data.size() >= 5) {
            staff.emplace_back(data[0], data[1], data[2], data[3], data[4]);
        }
    }
    file.close();
}

void loadShowtimes(vector<Showtime>& showtimes, const vector<Movie>& movies) {
    ifstream file("showtimes.csv");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> data = parseCSVLine(line);
        if (data.size() >= 4) {
            string showID = data[0];
            string movieID = data[1];
            string time = data[2];
            double price = 0;
            try { price = stod(data[3]); } catch(...) { continue; }

            Movie selectedMovie("Unknown", "Unknown", "Unknown", 0, 0.0, "");
            bool found = false;
            for (const auto& m : movies) {
                if (m.getId() == movieID) {
                    selectedMovie = m;
                    found = true;
                    break;
                }
            }
            if (found) showtimes.emplace_back(showID, selectedMovie, time, price, 5, 8);
        }
    }
    file.close();
}

void saveShowtimes(const vector<Showtime>& showtimes) {
    ofstream file("showtimes.csv", ios::trunc);
    if (!file.is_open()) return;
    for (const auto& s : showtimes) {
        file << s.getId() << "," << s.getMovie().getId() << "," << s.getDateTime() << "," << (long)s.getPrice() << endl;
    }
    file.close();
}

Customer* selectCustomerAccount(vector<Customer>& customers) {
    clearScreen();
    cout << "=== CHON TAI KHOAN KHACH HANG ===\n";
    if (customers.empty()) {
        cout << "Chua co tai khoan. Vui long Dang ky.\n";
        return nullptr;
    }
    cout << left << setw(5) << "STT" << setw(10) << "ID" << setw(25) << "TEN KHACH HANG" << endl;
    cout << "----------------------------------------\n";
    for (size_t i = 0; i < customers.size(); ++i) {
        cout << left << setw(5) << (i + 1) 
             << setw(10) << customers[i].getId() 
             << setw(25) << customers[i].getName() << endl;
    }
    cout << "----------------------------------------\n";
    cout << "0. Quay lai\n";
    int choice = getMenuChoice();
    if (choice == 0) return nullptr;
    if (choice > 0 && choice <= (int)customers.size()) return &customers[choice - 1];
    cout << "[!] Lua chon khong hop le.\n"; pressEnterToContinue();
    return nullptr;
}

Staff* selectStaffAccount(vector<Staff>& staffList) {
    clearScreen();
    cout << "=== DANG NHAP HE THONG NHAN VIEN ===\n";
    if (staffList.empty()) {
        cout << "[!] Khong tim thay du lieu trong staff.csv.\n";
        return nullptr;
    }

    cout << left << setw(5) << "STT" 
         << setw(10) << "ID" 
         << setw(25) << "TEN NHAN VIEN" 
         << setw(15) << "CHUC VU" << endl;

    cout << "-------------------------------------------------------\n";
    
    for (size_t i = 0; i < staffList.size(); ++i) {
        cout << left << setw(5) << (i + 1) 
             << setw(10) << staffList[i].getId() 
             << setw(25) << staffList[i].getName()
             << setw(15) << staffList[i].getRole() << endl; 
    }
    
    cout << "-------------------------------------------------------\n";
    cout << "0. Quay lai\n";

    int choice = getMenuChoice();
    if (choice == 0) return nullptr;
    
    if (choice > 0 && choice <= (int)staffList.size()) {
        return &staffList[choice - 1];
    }
    cout << "[!] Lua chon khong hop le.\n";
    pressEnterToContinue();
    return nullptr;
}

void handleRegister(vector<Customer>& allCustomers) {
    clearScreen();
    cout << "=== DANG KY TAI KHOAN ===\n";
    string name = getStringInput("Ho ten: ");
    string email = getStringInput("Email: ");
    string phone = getStringInput("SDT: ");
    string newId = "C" + to_string(allCustomers.size() + 101);
    allCustomers.emplace_back(newId, name, email, phone);
    saveCustomers(allCustomers);
    cout << "\nDang ky thanh cong! ID: " << newId << "\n";
    pressEnterToContinue();
}

void handleCustomerBooking(Customer& customer, Booking& bookingSystem, vector<Showtime>& showtimes) {
    clearScreen();
    cout << "--- DAT VE ---\n";
    if (showtimes.empty()) { cout << "Trong.\n"; pressEnterToContinue(); return; }
    for (size_t i = 0; i < showtimes.size(); ++i) {
        cout << "[" << (i + 1) << "] " << showtimes[i].getMovie().getTitle() << " - " << showtimes[i].getDateTime() << endl;
    }
    int choice = getMenuChoice();
    if (choice <= 0 || choice > (int)showtimes.size()) return;

    Showtime& selectedShow = showtimes[choice - 1];
    BookingAlgorithm::displayAvailableSeats(selectedShow);
    string seatId = getStringInput("> Chon ghe (vd: A5): ");

    if (BookingAlgorithm::bookSeat(selectedShow, bookingSystem, seatId, selectedShow.getPrice())) {
        string newTicketId = "T" + to_string(bookingSystem.getTickets().size());
        Ticket* t = bookingSystem.findTicket(newTicketId);
        if (t) {
            customer.addTicketToHistory(*t);
            cout << "Dat ve thanh cong!\n";
        }
    }
    pressEnterToContinue();
}

void handleCustomerCancel(Customer& customer, Booking& bookingSystem, vector<Showtime>& showtimes) {
    clearScreen();
    cout << "--- HUY VE ---\n";
    vector<Ticket>& myHistory = const_cast<vector<Ticket>&>(customer.getBookingHistory());

    if (myHistory.empty()) {
        cout << "Lich su trong.\n";
        pressEnterToContinue();
        return;
    }

    cout << "DANH SACH VE:\n";
    for (const auto& t : myHistory) t.info();
    cout << "----------------\n";

    string tId = getStringInput("> Nhap MA VE muon huy: ");
    bool found = false;

    for (auto& ticket : myHistory) {
        if (ticket.getId() == tId) {
            found = true;
            if (ticket.getStatus() == TicketStatus::CANCELED) {
                cout << "[!] Ve nay da duoc huy truoc do.\n";
            } else {
                ticket.cancel(); 
                if (ticket.getShowtime()) cout << "-> Da gui yeu cau tra ghe ve he thong.\n";
            }
            break;
        }
    }
    if (!found) cout << "[!] Khong tim thay ma ve.\n";
    pressEnterToContinue();
}

void showCustomerMenu(Customer& customer, Booking& bookingSystem, vector<Showtime>& showtimes) {
    bool running = true;
    while (running) {
        clearScreen();
        cout << "--- HI, " << customer.getName() << " ---\n";
        cout << "1. Dat ve\n";
        cout << "2. Huy ve\n";
        cout << "3. Xem lich su\n";
        cout << "0. Dang xuat\n";
        int c = getMenuChoice();
        switch (c) {
            case 1: handleCustomerBooking(customer, bookingSystem, showtimes); break;
            case 2: handleCustomerCancel(customer, bookingSystem, showtimes); break;
            case 3: 
                clearScreen(); 
                if (customer.getBookingHistory().empty()) cout << "Lich su trong.\n";
                else for(const auto& t : customer.getBookingHistory()) t.printTicket();
                pressEnterToContinue(); 
                break;
            case 0: running = false; break;
        }
    }
}

void handleStaffAddShowtime(Staff& staff, vector<Showtime>& allShowtimes, const vector<Movie>& allMovies) {
    clearScreen();
    cout << "--- THEM SUAT CHIEU ---\n";
    if (allMovies.empty()) { cout << "Chua co phim.\n"; pressEnterToContinue(); return; }
    for (size_t i = 0; i < allMovies.size(); ++i) 
        cout << "[" << (i + 1) << "] " << allMovies[i].getTitle() << endl;
    
    int mc = getMenuChoice();
    if (mc <= 0 || mc > (int)allMovies.size()) return;
    
    const Movie& movie = allMovies[mc - 1];
    string showId = "S" + to_string(allShowtimes.size() + 101);
    string time = getStringInput("Thoi gian (DD/MM/YYYY HH:MM): ");
    double price = 0;
    cout << "Gia ve: "; cin >> price; cin.ignore();

    Showtime newShow(showId, movie, time, price, 5, 8);
    staff.addShowtime(newShow);
    allShowtimes.push_back(newShow);
    saveShowtimes(allShowtimes);
    cout << "Da them suat chieu moi!\n";
    pressEnterToContinue();
}

void handleStaffRemoveShowtime(Staff& staff, vector<Showtime>& allShowtimes) {
    clearScreen();
    cout << "--- XOA SUAT CHIEU ---\n";
    if (allShowtimes.empty()) { cout << "Trong.\n"; pressEnterToContinue(); return; }

    for (size_t i = 0; i < allShowtimes.size(); ++i) {
        cout << "[" << (i + 1) << "] ID:" << allShowtimes[i].getId() 
             << " - " << allShowtimes[i].getMovie().getTitle() 
             << " - " << allShowtimes[i].getDateTime() << endl;
    }

    string id = getStringInput("> Nhap ID can xoa: ");
    bool found = false;
    for (auto it = allShowtimes.begin(); it != allShowtimes.end(); ++it) {
        if (it->getId() == id) {
            string time = it->getDateTime();
            allShowtimes.erase(it);
            staff.removeShowtime(time);
            saveShowtimes(allShowtimes); 
            cout << "Da xoa thanh cong.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Khong tim thay ID.\n";
    pressEnterToContinue();
}

void handleStaffManageShowtime(Staff& staff, vector<Showtime>& allShowtimes) {
    clearScreen();
    cout << "--- SUA SUAT CHIEU ---\n";
    if (allShowtimes.empty()) { cout << "Trong.\n"; pressEnterToContinue(); return; }

    for (size_t i = 0; i < allShowtimes.size(); ++i) {
        cout << "[" << (i + 1) << "] ID:" << allShowtimes[i].getId() 
             << " - " << allShowtimes[i].getMovie().getTitle() << endl;
    }

    string id = getStringInput("> Nhap ID can sua: ");
    Showtime* target = nullptr;
    for (auto& s : allShowtimes) if (s.getId() == id) { target = &s; break; }

    if (!target) { cout << "Khong tim thay.\n"; pressEnterToContinue(); return; }

    cout << "Thoi gian cu: " << target->getDateTime() << endl;
    string newTime = getStringInput("Thoi gian moi (Enter de giu nguyen): ");
    if (newTime.empty()) newTime = target->getDateTime();

    cout << "Gia cu: " << (long)target->getPrice() << endl;
    string newPriceStr = getStringInput("Gia moi (Enter de giu nguyen): ");
    double newPrice = target->getPrice();
    if (!newPriceStr.empty()) {
        try { newPrice = stod(newPriceStr); } catch(...) {}
    }

    staff.manageShowtime(*target, newTime, newPrice);
    saveShowtimes(allShowtimes); 
    cout << "Cap nhat thanh cong!\n";
    pressEnterToContinue();
}

void showStaffMenu(Staff& staff, vector<Showtime>& showtimes, vector<Movie>& movies) {
    bool running = true;
    while (running) {
        clearScreen();
        cout << "--- MENU NHAN VIEN: " << staff.getName() << " (" << staff.getRole() << ") ---\n";
        cout << "1. Them suat chieu\n";
        cout << "2. Xoa suat chieu\n";
        cout << "3. Sua suat chieu\n";
        cout << "4. Xem thong tin ca nhan\n";
        cout << "0. Dang xuat\n";
        
        int c = getMenuChoice();
        switch(c) {
            case 1: handleStaffAddShowtime(staff, showtimes, movies); break;
            case 2: handleStaffRemoveShowtime(staff, showtimes); break;
            case 3: handleStaffManageShowtime(staff, showtimes); break;
            case 4: clearScreen(); staff.info(); pressEnterToContinue(); break;
            case 0: running = false; break;
        }
    }
}

int main() {
    Booking bookingSystem;
    vector<Movie> allMovies;
    vector<Showtime> allShowtimes;
    vector<Customer> allCustomers;
    vector<Staff> allStaff;

    loadMovies(allMovies);
    loadCustomers(allCustomers);
    loadStaff(allStaff);
    loadShowtimes(allShowtimes, allMovies);

    bool appRunning = true;
    while (appRunning) {
        clearScreen();
        cout << "=== HE THONG DAT VE ===\n";
        cout << "1. Dang nhap (Khach hang)\n";
        cout << "2. Dang nhap (Nhan vien)\n";
        cout << "3. Dang ky moi\n";
        cout << "0. Thoat\n";

        int choice = getMenuChoice();
        switch (choice) {
            case 1: {
                Customer* u = selectCustomerAccount(allCustomers);
                if (u) showCustomerMenu(*u, bookingSystem, allShowtimes);
                break;
            }
            case 2: {
                Staff* s = selectStaffAccount(allStaff);
                if (s) showStaffMenu(*s, allShowtimes, allMovies);
                break;
            }
            case 3: handleRegister(allCustomers); break;
            case 0: appRunning = false; break;
        }
    }
    return 0;
}
