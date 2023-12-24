#ifndef PROJ_AED2_AIRLINE_H
#define PROJ_AED2_AIRLINE_H

#include <string>
using namespace std;


class Airline {
    string name, callsign, country;

public:
    Airline(string& name, string& callsign, string& country);


    const string& getName() const;
    const string& getCallsign() const;
    const string& getCountry() const;

};


#endif //PROJ_AED2_AIRLINE_H
