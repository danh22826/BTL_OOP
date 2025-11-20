#include "Movie.h"
#include <iostream>
using namespace std;
Movie::Movie(const string &id, const string &title,
             const string &genre, int duration,
             double rating, const string &desc)
    : Entity(id), title(title), genre(genre),
      description(desc), duration(duration), rating(rating) {}

Movie::Movie(const Movie &other)
    : Entity(other), title(other.title), genre(other.genre),
      description(other.description), duration(other.duration), rating(other.rating) {}

Movie& Movie::operator=(const Movie &other) {
    if (this != &other) {
        Entity::operator=(other);
        title = other.title;
        genre = other.genre;
        description = other.description;
        duration = other.duration;
        rating = other.rating;
    }
    return *this;
}

Movie::~Movie() {}

string Movie::getTitle() const { return title; }
string Movie::getGenre() const { return genre; }
string Movie::getDescription() const { return description; }
int Movie::getDuration() const { return duration; }
double Movie::getRating() const { return rating; }

void Movie::setTitle(const string &t) { title = t; }
void Movie::setGenre(const string &g) { genre = g; }
void Movie::setDescription(const string &d) { description = d; }
void Movie::setDuration(int d) { duration = d; }
void Movie::setRating(double r) { rating = r; }

void Movie::info() const {
    cout << "Movie[" << id << "] " << title
              << " (" << genre << "), " << duration << " min, Rating: "
              << rating << endl;
}
