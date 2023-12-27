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

Airport* Flight::getDest() const {
    return dest;
}

void Flight::setDest(Airport *d) {
    this->dest = d;
}

const string &Flight::getAirlineCode() const {
    return airlineCode;
}

void Flight::setAirlineCode(string& airlineCode) {
    this->airlineCode = airlineCode;
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

int Graph::getNumAirports() const {
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

void Graph::dfsVisit(Airport *v, vector<Airport *> &result) const {
    v->setVisited(true);
    result.push_back(v);

    for(auto& flight : v->getFlights()){
        Airport* w = flight->getDest();
        if(!w->isVisited()){
            dfsVisit(w,result);
        }
    }
}

vector<Airport*> Graph::dfs() const{
    vector<Airport*> result;
    for(auto airport : airportSet){
        airport->setVisited(false);
    }

    for(auto airport : airportSet){
        if(!airport->isVisited()){
            dfsVisit(airport,result);
        }
    }

    return result;
}

vector<Airport*> Graph::dfs(const string& sourceCode) const{
    vector<Airport*> result;
    Airport* source = findAirport(sourceCode);
    if(source != nullptr){
        for(auto airport : airportSet){
            airport->setVisited(false);
        }
        dfsVisit(source, result);
    }
}

vector<Airport*> Graph::bfs(const string& sourceCode) const{
    vector<Airport*> result;
    Airport* source = findAirport(sourceCode);
    if(source != nullptr){
        for(auto airport : airportSet){
            airport-> setVisited(false);
        }
        queue<Airport*> auxQueue;
        source->setVisited(true);
        auxQueue.push(source);

        while(!auxQueue.empty()){
            Airport* first = auxQueue.front();
            auxQueue.pop();
            result.push_back(first);

            for(auto& flight : first->getFlights()){
                Airport* dest = flight->getDest();
                if(!dest->isVisited()){
                    dest->setVisited(true),
                    auxQueue.push(dest);
                }
            }
        }
    }

    return result;
}

vector<Airport*> Graph::topsort() const{
    vector<Airport*> result;
    queue<Airport*> auxQueue;

    if(!isDAG()) return result;

    for(auto airport : airportSet){
        airport->setIndegree(0);
    }
    for(auto airport : airportSet){
        for(auto flight : airport->getFlights()){
            flight->getDest()->setIndegree(flight->getDest()->getIndegree() + 1);
        }
    }
    for(auto airport : airportSet){
        if(airport->getIndegree() == 0){
            auxQueue.push(airport);
        }
    }

    while(!auxQueue.empty()){
        Airport* first = auxQueue.front();
        auxQueue.pop();
        for(auto flight : first->getFlights()){
            auto dest = flight->getDest();
            dest->setIndegree(dest->getIndegree() - 1);
            if(dest->getIndegree() == 0) auxQueue.push(dest);
        }
        result.push_back(first);
    }
    return result;
}

bool Graph::isDAG() const {
    for(auto airport : airportSet){
        airport->setVisited(false);
        airport->setProcessing(false);
    }
    for(auto airport : airportSet){
        if(!airport->isVisited()){
            if(!dfsIsDAG(airport)){
                return false;
            }
        }
    }
    return true;
}

bool Graph::dfsIsDAG(Airport *v) const {
    v->setVisited(true);
    v->setProcessing(true);
    for(auto flight : v->getFlights()){
        auto dest = flight->getDest();
        if(dest->isProcessing()){
            return false;
        }
        if(!dest->isVisited()){
            if(!dfsIsDAG(dest)){
                return false;
            }
        }
    }
    v->setProcessing(false);
    return true;
}

int Graph::getNumFlights() const {
    int total = 0;
    for(auto airport : airportSet){
        total += airport->getFlights().size();
    }
    return total;
}

pair<int,int> Graph::airportFlightStats(const std::string &airportCode) const {
    auto airport = findAirport(airportCode);

    if(airport == nullptr) return {0,0};

    auto flights = airport->getFlights();
    unordered_set<string> airlines;

    for(auto flight : flights){
        airlines.insert(flight->getAirlineCode());
    }
    return {flights.size(),airlines.size()};
}