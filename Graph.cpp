#include "Graph.h"


AirportInfo::AirportInfo(const string &code, const string &name, const string &city, const string &country, const double latitude, const double longitude) :
 code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

const string& AirportInfo::getCode() const {
    return code;
}

const string& AirportInfo::getName() const {
    return name;
}

const string& AirportInfo::getCity() const {
    return city;
}

const string& AirportInfo::getCountry() const {
    return country;
}

double AirportInfo::getLatitude() const {
    return latitude;
}

double AirportInfo::getLongitude() const {
    return longitude;
}




Airport::Airport(const AirportInfo &airportInfo) :
        airportInfo(airportInfo){}

Airport::Airport(const string &code, const string &name, const string &city, const string &country, double latitude, double longitude) :
airportInfo(code,name,city,country,latitude, longitude), visited(false) {}

Airport::~Airport() {
    for (Flight* flight : getFlights())
        delete flight;
}

const AirportInfo &Airport::getAirportInfo() const {
    return airportInfo;
}

void Airport::setAirportInfo(const AirportInfo &info) {
    this->airportInfo = info;
}

bool Airport::isVisited() const {
    return visited;
}

void Airport::setVisited(bool v) {
    visited = v;
}

const vector<Flight*> &Airport::getFlights() const {
    return flights;
}

void Airport::addFlight(Airport *dest, const string &airlineCode) {
    Flight* newFlight = new Flight(dest, airlineCode);
    flights.push_back(newFlight);
}

void Airport::removeFlightTo(Airport *d) {
    for (auto flight : getFlights()) {
        if (flight->getDest()->getAirportInfo().getCode() == d->getAirportInfo().getCode()) {
            delete flight;
        }
    }
}


Flight::Flight(Airport *d, const string &airlineCode) :
dest(d), airlineCode(airlineCode){}

Airport* Flight::getDest() const {
    return dest;
}

const string &Flight::getAirlineCode() const {
    return airlineCode;
}




Airport* Graph::findAirport(const string &airportCode) const {
    Airport* res;
    for (auto airport : airportSet) {
        if (airport->getAirportInfo().getCode() == airportCode) {
            res = airport;
        }
    }
    return res;
}

void Graph::addAirport(const AirportInfo &info) {
    airportSet.push_back(new Airport(info));
}

void Graph::removeAirport(const string &airportCode) {
    delete findAirport(airportCode);
}

void Graph::addFlight(const string &sourcCode, const string &destCode, const string &airlineCode) {
    Airport* source = findAirport(sourcCode);
    Airport* dest = findAirport(destCode);
    source->addFlight(dest, airlineCode);
}

const vector<Airport *> &Graph::getAirportSet() const {
    return airportSet;
}
