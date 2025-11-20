// Staff.h
#ifndef STAFF_H
#define STAFF_H

#include "Person.h"     
#include "Showtime.h"   
#include <string>       
#include <vector>       
using namespace std;

class Staff : public Person
{
private:
    vector<Showtime> showtimes; 
    string department;      

public:
    Staff();
    Staff(const string &id, const string &name,
          const string &email, const string &phone,
          const string &dept) ;
    
    virtual ~Staff();

    void manageShowtime(Showtime &showtime, const string &newTime, double newPrice) ;
    
    void addShowtime(const Showtime &show) ;
    
    void removeShowtime(const string &time) ;
    
    virtual void info() const override ;
    string getRole() const;
};

#endif
