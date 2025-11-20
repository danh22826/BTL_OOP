#ifndef MOVIE_H
#define MOVIE_H
#include<iostream>
#include "Entity.h"
using namespace std;
class Movie : public Entity {
private:
    string title;
    string genre;
    string description;
    int duration; 
    double rating;
public:
    Movie(const string &id = "", const string &title = "",
          const string &genre = "", int duration = 0,
          double rating = 0.0, const string &desc = "");

    Movie(const Movie &other);
    Movie& operator=(const Movie &other);
    virtual ~Movie();

    string getTitle() const;
    string getGenre() const;
    string getDescription() const;
    int getDuration() const;
    double getRating() const;

    void setTitle(const string &t);
    void setGenre(const string &g);
    void setDescription(const string &d);
    void setDuration(int d);
    void setRating(double r);
    virtual void info() const override;
};

#endif
