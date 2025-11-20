#include "DataLoader.h"

vector<string> DataLoader::parseLine(const string& line) {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

void DataLoader::loadMovies(const string& filename, vector<Movie>& movies) {
    movies.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> data = parseLine(line);
        if (data.size() >= 6) {
            try {
                movies.emplace_back(
                    data[0], data[1], data[2],
                    stoi(data[3]),
                    stod(data[4]),
                    data[5]
                );
            } catch (...) {}
        }
    }
    file.close();
}

void DataLoader::loadCustomers(const string& filename, vector<Customer>& customers) {
    customers.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> data = parseLine(line);
        if (data.size() >= 4) {
            customers.emplace_back(data[0], data[1], data[2], data[3]);
        }
    }
    file.close();
}

void DataLoader::loadStaff(const string& filename, vector<Staff>& staffList) {
    staffList.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> data = parseLine(line);
        if (data.size() >= 5) {
            staffList.emplace_back(
                data[0], data[1], data[2], data[3], data[4]
            );
        }
    }
    file.close();
}

void DataLoader::loadShowtimes(
    const string& filename,
    vector<Showtime>& showtimes,
    const vector<Movie>& movies
) {
    showtimes.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> data = parseLine(line);
        if (data.size() >= 4) {
            try {
                string showId = data[0];
                string movieId = data[1];

                for (const auto& m : movies) {
                    if (m.getId() == movieId) {
                        showtimes.emplace_back(
                            showId, m, data[2], stod(data[3])
                        );
                        break;
                    }
                }
            } catch (...) {}
        }
    }
    file.close();
}

void DataLoader::saveShowtimes(const string& filename, const vector<Showtime>& showtimes) {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& s : showtimes) {
        file << s.getId() << ","
             << s.getMovie().getId() << ","
             << s.getDateTime() << ","
             << (long long)s.getPrice()
             << endl;
    }
    file.close();
}

