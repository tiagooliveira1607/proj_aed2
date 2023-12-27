#include "Airline.h"

Airline::Airline(string &name, string &callsign, string &country) :
        name(name), callsign(callsign), country(country) {}

const string& Airline::getName() const {
    return name;
}

const string& Airline::getCallsign() const {
    return callsign;
}

const string& Airline::getCountry() const {
    return country;
}