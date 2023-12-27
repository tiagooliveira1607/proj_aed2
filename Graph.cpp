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

bool Airport::isProcessing() const {
    return processing;
}

void Airport::setProcessing(bool p) {
    this->processing = p;
}

int Airport::getIndegree() const {
    return indegree;
}

void Airport::setIndegree(int indegree) {
    this->indegree = indegree;
}

int Airport::getNum() const{
    return num;
}

void Airport::setNum(int num) {
    this->num = num;
}

int Airport::getLow() const{
    return low;
}

void Airport::setLow(int low) {
    this->low = low;
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

const Airport* Flight::getDest() const {
    return dest;
}

void Flight::setDest(Airport *d) {
    this->dest = d;
}

const string &Flight::getAirlineCode() const {
    return airlineCode;
}




Airport* Graph::findAirport(const string &airportCode) const {
    Airport* res;
    for (auto airport : airportSet) {
        if (airport->getAirportInfo().getCode() == airportCode) {
            res = airport;
            return res;
        }
    }
    return nullptr;
}

int Graph::getNumAirport() const {
    return airportSet.size();
}

bool Graph::addAirport(const AirportInfo &info) {
    if(findAirport(info.getCode()) != nullptr){
        return false;
    }
    airportSet.push_back(new Airport(info));
    return true;

}

bool Graph::removeAirport(const string &airportCode) {
    for(auto airport = airportSet.begin(); airport != airportSet.end(); airport++){
        if((*airport)->airportInfo.getCode() == airportCode){
            auto ap = *airport;
            airportSet.erase(airport);
            for(auto flight : airportSet){
                flight->removeFlightTo(ap);
            }
            delete ap;
            return true;
        }
    }
    return false;
}

bool Graph::addFlight(const string &sourcCode, const string &destCode, const string &airlineCode) {
    auto source = findAirport(sourcCode);
    auto dest = findAirport(destCode);

    if(source == nullptr || dest == nullptr){
        return false;
    }
    source->addFlight(dest,airlineCode);
    return true;
}

bool Graph::removeFlight(const string &sourcCode, const string &destCode) const {
    auto source = findAirport(sourcCode);
    auto dest = findAirport(destCode);

    if(source == nullptr || dest == nullptr){
        return false;
    }
    source->removeFlightTo(dest);
}

const vector<Airport *> &Graph::getAirportSet() const {
    return airportSet;
}
