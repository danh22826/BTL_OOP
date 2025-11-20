#ifndef SHOWTIME_H
#define SHOWTIME_H

#include "Entity.h"
#include "Movie.h"
#include "Seat.h"
#include <vector>
using namespace std;
class Showtime : public Entity {
private:
    Movie movie;
    string dateTime;
    double price;
    vector<Seat> seats;
public:
    Showtime(const string &id, const Movie &mv,
             const string &time, double price,
             int rows = 5, int cols = 10);

    Showtime(const Showtime &other);
    Showtime& operator=(const Showtime &other);
    virtual ~Showtime();

    // Methods
    bool checkSeatAvailable(const string &seatId) const;
    bool occupySeat(const string &seatId);
    bool releaseSeat(const string &seatId);
    int totalAvailableSeats() const;

    virtual void info() const override;
	// Getter
	Movie getMovie() const;
	string getDateTime() const;
	double getPrice() const;
	vector<Seat> getSeats() const;
	
	// Setter
	void setMovie(const Movie &mv);
	void setDateTime(const string &dt);
	void setPrice(double p);
	void setSeats(const vector<Seat> &s);

};

#endif
