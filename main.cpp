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

// Khai bao nguyen mau cac ham xu ly nghiep vu chinh
void handleStaffAddShowtime(Staff& staff, vector<Showtime>& allShowtimes, const vector<Movie>& allMovies);
void void handleStaffRemoveShowtime(Staff& staff, vector<Showtime>& allShowtimes);
void handleStaffManageShowtime(Staff& staff, vector<Showtime>& allShowtimes);
void showStaffMenu(Staff& staff, vector<Showtime>& showtimes, vector<Movie>& movies);
void showCustomerMenu(Customer& customer, Booking& bookingSystem, vector<Showtime>& showtimes);

// --- NHOM HAM TIEN ICH CHUNG ---

// Chuc nang: Xoa man hinh console (Tuy he dieu hanh)
void clearScreen() {
#ifdef _WIN32
    system("cls"); // Lenh xoa man hinh cho Windows
#else
    system("clear"); // Lenh xoa man hinh cho Linux/Mac
#endif
}

// Chuc nang: Tam dung chuong trinh. Kho: Phai lam sach bo dem nhap lieu
void pressEnterToContinue() {
    cout << "\nNhan Enter de tiep tuc...";
    // Lam sach bo dem nhap lieu truoc
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Chuc nang: Nhan lua chon so tu menu. Kho: Kiem tra va bat loi nhap ky tu/chu
int getMenuChoice() {
    int choice;
    cout << "\n> Nhap lua chon: ";
    // Vong lap bat loi: neu nhap khong phai so thi nhap lai
    while (!(cin >> choice)) { 
        cout << "[!] Nhap lai so: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Lam sach ky tu \n sau khi nhap
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return choice;
}

// Chuc nang: Nhan du lieu dang chuoi co chua khoang trang
string getStringInput(string prompt) {
    string input;
    cout << prompt;
    // Neu bo dem con ky tu \n thi bo qua
    if (cin.peek() == '\n') cin.ignore(); 
    getline(cin, input);
    return input;
}

// Chuc nang: Tach mot dong chuoi CSV thanh cac phan tu trong Vector
vector<string> parseCSVLine(const string& line) {
    vector<string> result;
    // Su dung Stringstream de tach chuoi bang dau phay
    stringstream ss(line); 
    string item;
    while (getline(ss, item, ',')) result.push_back(item);
    return result;
}

// --- NHOM HAM TAI VA LUU DU LIEU (I/O) ---

// Chuc nang: Tai du lieu Phim tu movies.csv
void loadMovies(vector<Movie>& movies) {
    ifstream file("movies.csv");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> data = parseCSVLine(line);
        if (data.size() >= 6) {
            /* Kho: Su dung try-catch de bat loi dinh dang du lieu (VD: chu thay vi so) */
            try { 
                movies.emplace_back(data[0], data[1], data[2], stoi(data[3]), stod(data[4]), data[5]);
            } catch (...) { continue; } // Neu loi thi bo qua dong nay
        }
    }
    file.close();
}

// Chuc nang: Tai du lieu Khach hang tu customers.csv
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

// Chuc nang: Luu du lieu Khach hang ra file customers.csv
void saveCustomers(const vector<Customer>& customers) {
    /* Kho: ios::trunc dam bao xoa toan bo noi dung cu truoc khi ghi moi */
    ofstream file("customers.csv", ios::trunc); 
    if (!file.is_open()) return;
    for (const auto& c : customers) {
        file << c.getId() << "," << c.getName() << "," << c.getEmail() << "," << c.getPhone() << endl;
    }
    file.close();
}

// Chuc nang: Tai du lieu Nhan vien tu staff.csv
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

// Chuc nang: Tai du lieu Suat chieu tu showtimes.csv
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
            /* Kho: Lien ket du lieu - Phai tim doi tuong Movie tuong ung voi movieID */
            for (const auto& m : movies) {
                if (m.getId() == movieID) {
                    selectedMovie = m;
                    found = true;
                    break;
                }
            }
            // Chi tao Showtime neu tim thay Movie lien ket
            if (found) showtimes.emplace_back(showID, selectedMovie, time, price, 5, 8);
        }
    }
    file.close();
}

// Chuc nang: Luu du lieu Suat chieu ra file showtimes.csv
void saveShowtimes(const vector<Showtime>& showtimes) {
    ofstream file("showtimes.csv", ios::trunc);
    if (!file.is_open()) return;
    for (const auto& s : showtimes) {
        // Luu lai thong tin can thiet (ID, MovieID, Time, Price)
        file << s.getId() << "," << s.getMovie().getId() << "," << s.getDateTime() << "," << (long)s.getPrice() << endl;
    }
    file.close();
}

// --- NHOM HAM DANG NHAP / DANG KY ---

// Chuc nang: Hien thi va chon tai khoan Khach hang. 
// Kho: Tra ve con tro (&) den doi tuong goc trong vector
Customer* selectCustomerAccount(vector<Customer>& customers) {
    clearScreen();
    cout << "=== CHON TAI KHOAN KHACH HANG ===\n";
    if (customers.empty()) {
        cout << "Chua co tai khoan. Vui long Dang ky.\n";
        return nullptr;
    }
    // Hien thi danh sach khach hang de lua chon
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
    // Tra ve dia chi (&) cua Customer duoc chon
    if (choice > 0 && choice <= (int)customers.size()) return &customers[choice - 1]; 
    cout << "[!] Lua chon khong hop le.\n"; pressEnterToContinue();
    return nullptr;
}

// Chuc nang: Hien thi va chon tai khoan Nhan vien. 
Staff* selectStaffAccount(vector<Staff>& staffList) {
    clearScreen();
    cout << "=== DANG NHAP HE THONG NHAN VIEN ===\n";
    if (staffList.empty()) {
        cout << "[!] Khong tim thay du lieu trong staff.csv.\n";
        return nullptr;
    }

    // Hien thi danh sach nhan vien
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
    
    // Tra ve dia chi (&) cua Staff duoc chon
    if (choice > 0 && choice <= (int)staffList.size()) {
        return &staffList[choice - 1];
    }
    cout << "[!] Lua chon khong hop le.\n";
    pressEnterToContinue();
    return nullptr;
}

// Chuc nang: Dang ky tai khoan khach hang moi
void handleRegister(vector<Customer>& allCustomers) {
    clearScreen();
    cout << "=== DANG KY TAI KHOAN ===\n";
    string name = getStringInput("Ho ten: ");
    string email = getStringInput("Email: ");
    string phone = getStringInput("SDT: ");
    // Tao ID moi dua tren kich thuoc hien tai cua vector
    string newId = "C" + to_string(allCustomers.size() + 101); 
    allCustomers.emplace_back(newId, name, email, phone);
    saveCustomers(allCustomers); // Luu vao file
    cout << "\nDang ky thanh cong! ID: " << newId << "\n";
    pressEnterToContinue();
}

// --- NHOM HAM XU LY NGHIEP VU CHINH (CUSTOMER) ---

// Chuc nang: Quy trinh dat ve hoan chinh
void handleCustomerBooking(Customer& customer, Booking& bookingSystem, vector<Showtime>& showtimes) {
    clearScreen();
    cout << "--- DAT VE ---\n";
    if (showtimes.empty()) { cout << "Trong.\n"; pressEnterToContinue(); return; }
    // Hien thi danh sach suat chieu
    for (size_t i = 0; i < showtimes.size(); ++i) {
        cout << "[" << (i + 1) << "] " << showtimes[i].getMovie().getTitle() << " - " << showtimes[i].getDateTime() << endl;
    }
    int choice = getMenuChoice();
    if (choice <= 0 || choice > (int)showtimes.size()) return;

    Showtime& selectedShow = showtimes[choice - 1]; // Lay suat chieu tham chieu (&)
    // Hien thi so do ghe
    BookingAlgorithm::displayAvailableSeats(selectedShow);
    string seatId = getStringInput("> Chon ghe (vd: A5): ");

    // Goi ham xu ly dat ghe (chua cac buoc kiem tra/khoa ghe/tao ve)
    if (BookingAlgorithm::bookSeat(selectedShow, bookingSystem, seatId, selectedShow.getPrice())) {
        // Tao ID ve moi (Dua tren so luong ve hien tai trong BookingSystem)
        string newTicketId = "T" + to_string(bookingSystem.getTickets().size()); 
        
        // Tim ve vua duoc tao ra de lay dia chi con tro
        Ticket* t = bookingSystem.findTicket(newTicketId);
        if (t) {
            // Luu ve vao lich su ca nhan cua khach hang nay
            customer.addTicketToHistory(*t); 
            cout << "Dat ve thanh cong!\n";
        }
    }
    pressEnterToContinue();
}

// Chuc nang: Huy ve
// Kho: Ep kieu const_cast de sua doi lich su dat ve cua khach hang
void handleCustomerCancel(Customer& customer, Booking& bookingSystem, vector<Showtime>& showtimes) {
    clearScreen();
    cout << "--- HUY VE ---\n";
    // const_cast cho phep lay ve tham chieu co the sua doi tu ham const
    vector<Ticket>& myHistory = const_cast<vector<Ticket>&>(customer.getBookingHistory()); 

    if (myHistory.empty()) {
        cout << "Lich su trong.\n";
        pressEnterToContinue();
        return;
    }

    cout << "DANH SACH VE:\n";
    for (const auto& t : myHistory) t.info(); // Hien thi lich su ve
    cout << "----------------\n";

    string tId = getStringInput("> Nhap MA VE muon huy: ");
    bool found = false;

    for (auto& ticket : myHistory) {
        if (ticket.getId() == tId) {
            found = true;
            if (ticket.getStatus() == TicketStatus::CANCELED) {
                cout << "[!] Ve nay da duoc huy truoc do.\n";
            } else {
                ticket.cancel(); // Goi ham huy (soft delete)
                // Logic tra ghe ve he thong can duoc code ben trong ham ticket.cancel()
                if (ticket.getShowtime()) cout << "-> Da gui yeu cau tra ghe ve he thong.\n"; 
            }
            break;
        }
    }
    if (!found) cout << "[!] Khong tim thay ma ve.\n";
    pressEnterToContinue();
}

// Chuc nang: Hien thi menu va dieu phoi chuc nang cho Khach hang
void showCustomerMenu(Customer& customer, Booking& bookingSystem, vector<Showtime>& showtimes) {
    bool running = true;
    while (running) { // Vong lap chay menu
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
            case 0: running = false; break; // Thoat vong lap de Dang xuat
        }
    }
}

// Chuc nang: Them suat chieu moi vao vector toan cuc
void handleStaffAddShowtime(Staff& staff, vector<Showtime>& allShowtimes, const vector<Movie>& allMovies) {
    clearScreen();
    cout << "--- THEM SUAT CHIEU ---\n";
    if (allMovies.empty()) { cout << "Chua co phim.\n"; pressEnterToContinue(); return; }
    // Chon Phim
    for (size_t i = 0; i < allMovies.size(); ++i) 
        cout << "[" << (i + 1) << "] " << allMovies[i].getTitle() << endl;
    
    int mc = getMenuChoice();
    if (mc <= 0 || mc > (int)allMovies.size()) return;
    
    const Movie& movie = allMovies[mc - 1];
    string showId = "S" + to_string(allShowtimes.size() + 101); // Tao ID moi
    string time = getStringInput("Thoi gian (DD/MM/YYYY HH:MM): ");
    double price = 0;
    cout << "Gia ve: "; cin >> price; cin.ignore();

    Showtime newShow(showId, movie, time, price, 5, 8);
    staff.addShowtime(newShow); // [Ghi chu: Ham nay nen duoc xoa bo vi thua, xem phan tich truoc]
    allShowtimes.push_back(newShow); // Them vao vector toan cuc
    saveShowtimes(allShowtimes); // Luu ra file
    cout << "Da them suat chieu moi!\n";
    pressEnterToContinue();
}

// Chuc nang: Xoa suat chieu khoi vector toan cuc
// Kho: Phai dung Iterator de xoa phan tu va dung lenh saveShowtimes de luu lai thay doi vao file
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
    // Kho: Vong lap dung Iterator de xoa phan tu
    for (auto it = allShowtimes.begin(); it != allShowtimes.end(); ++it) {
        if (it->getId() == id) {
            string time = it->getDateTime();
            allShowtimes.erase(it); // Xoa khoi vector toan cuc
            staff.removeShowtime(time); // [Ghi chu: Ham nay nen duoc xoa bo vi thua]
            saveShowtimes(allShowtimes); // Cap nhat vao file
            cout << "Da xoa thanh cong.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Khong tim thay ID.\n";
    pressEnterToContinue();
}

// Chuc nang: Sua thong tin Gio chieu va Gia ve
// Kho: Su dung con tro/tham chieu de tim va sua truc tiep doi tuong goc trong vector
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
    // Tim dia chi (con tro) cua doi tuong Showtime muon sua
    for (auto& s : allShowtimes) if (s.getId() == id) { target = &s; break; }

    if (!target) { cout << "Khong tim thay.\n"; pressEnterToContinue(); return; }

    cout << "Thoi gian cu: " << target->getDateTime() << endl;
    string newTime = getStringInput("Thoi gian moi (Enter de giu nguyen): ");
    if (newTime.empty()) newTime = target->getDateTime();

    cout << "Gia cu: " << (long)target->getPrice() << endl;
    string newPriceStr = getStringInput("Gia moi (Enter de giu nguyen): ");
    double newPrice = target->getPrice();
    // Kho: Kiem tra va chuyen doi chuoi gia moi thanh so (double)
    if (!newPriceStr.empty()) { 
        try { newPrice = stod(newPriceStr); } catch(...) {}
    }

    // Goi ham manageShowtime cua staff, truyen doi tuong goc de sua
    staff.manageShowtime(*target, newTime, newPrice); 
    saveShowtimes(allShowtimes); 
    cout << "Cap nhat thanh cong!\n";
    pressEnterToContinue();
}

// Chuc nang: Hien thi menu va dieu phoi chuc nang cho Nhan vien
void showStaffMenu(Staff& staff, vector<Showtime>& showtimes, vector<Movie>& movies) {
    bool running = true;
    while (running) { // Vong lap chay menu
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
            case 0: running = false; break; // Thoat vong lap de Dang xuat
        }
    }
}

// Chuc nang: Diem bat dau. Thuc hien tai du lieu ban dau va quan ly cac vong lap menu lon
int main() {
    Booking bookingSystem; // Khoi tao he thong quan ly ve
    vector<Movie> allMovies; // Cac vector luu tru du lieu toan cuc
    vector<Showtime> allShowtimes;
    vector<Customer> allCustomers;
    vector<Staff> allStaff;

    // Tai du lieu tu CSV vao vector
    loadMovies(allMovies);
    loadCustomers(allCustomers);
    loadStaff(allStaff);
    // Kho: Tai suat chieu sau cung vi can du lieu Movie
    loadShowtimes(allShowtimes, allMovies); 

    bool appRunning = true;
    while (appRunning) { // Vong lap menu chinh
        clearScreen();
        cout << "=== HE THONG DAT VE ===\n";
        cout << "1. Dang nhap (Khach hang)\n";
        cout << "2. Dang nhap (Nhan vien)\n";
        cout << "3. Dang ky moi\n";
        cout << "0. Thoat\n";

        int choice = getMenuChoice();
        switch (choice) {
            case 1: { // Dang nhap Khach hang
                Customer* u = selectCustomerAccount(allCustomers);
                if (u) showCustomerMenu(*u, bookingSystem, allShowtimes); // Vao menu Khach hang
                break;
            }
            case 2: { // Dang nhap Nhan vien
                Staff* s = selectStaffAccount(allStaff);
                if (s) showStaffMenu(*s, allShowtimes, allMovies); // Vao menu Nhan vien
                break;
            }
            case 3: handleRegister(allCustomers); break; // Dang ky
            case 0: appRunning = false; break; // Thoat ung dung
        }
    }
    return 0;
}
