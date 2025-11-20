#ifndef DATALOADER_H
#define DATALOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Movie.h"
#include "Customer.h"
#include "Staff.h"
#include "Showtime.h"

using namespace std;

class DataLoader {
public:
    static vector<string> parseLine(const string& line);

    static void loadMovies(const string& filename, vector<Movie>& movies);
    static void loadCustomers(const string& filename, vector<Customer>& customers);
    static void loadStaff(const string& filename, vector<Staff>& staffList);

    static void loadShowtimes(
        const string& filename,
        vector<Showtime>& showtimes,
        const vector<Movie>& movies
    );

    static void saveShowtimes(
        const string& filename,
        const vector<Showtime>& showtimes
    );
};

#endif

