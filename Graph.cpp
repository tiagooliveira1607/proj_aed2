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
airportInfo(code,name,city,country,latitude, longitude), visited(false), ignored(false) {}

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

bool Airport::isIgnored() const {
    return ignored;
}

void Airport::setIgnored(bool v) {
    ignored = v;
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


Graph::Graph() {
    airportSet = vector<Airport*>();
}

Airport* Graph::findAirport(const string &airportCode) const {
    for (auto airport : airportSet) {
        if (airport->getAirportInfo().getCode() == airportCode) {
            return airport;
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
    return true;
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
    return result;
}


void Graph::bfs(const string& sourceCode, int x) const {
    Airport* source = findAirport(sourceCode);

    if (source != nullptr) {
        for (auto airport : airportSet) {
            airport->setVisited(false);
        }

        queue<pair<Airport*, int>> auxQueue;
        source->setVisited(true);
        auxQueue.push({source, 0});

        while (!auxQueue.empty()) {
            auto currentPair = auxQueue.front();
            auxQueue.pop();
            Airport* current = currentPair.first;
            int stops = currentPair.second;

            if (stops >= x) break;

            for (auto& flight : current->getFlights()) {
                Airport* dest = flight->getDest();
                if (!dest->isVisited()) {
                    dest->setVisited(true);
                    auxQueue.push({dest, stops + 1});
                }
            }
        }
    }
}

vector<pair<Airport*, int>> Graph::bfsLongestDistance(Airport* source) const {
    vector<pair<Airport*, int>> distances;

    if (source != nullptr) {
        queue<pair<Airport*, int>> auxQueue;
        unordered_set<const Airport*> visited;

        auxQueue.push({source,0});
        visited.insert(source);

        while (!auxQueue.empty()) {
            pair<Airport*, int> currentPair = auxQueue.front();
            auxQueue.pop();

            distances.push_back(currentPair);

            Airport* currentAirport = currentPair.first;
            int currentDistance = currentPair.second;

            for (Flight* flight : currentAirport->getFlights()) {
                Airport* nextAirport = flight->getDest();
                if (visited.find(nextAirport) == visited.end()) {
                    visited.insert(nextAirport);
                    auxQueue.push({nextAirport, currentDistance + 1});
                }
            }
        }
    }
    return distances;
}



/*

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
*/



//3)ix


void Graph::dfs3_9() const {
    Airport* source = airportSet[0];
    for(auto airport : airportSet){
        airport->setVisited(false);
    }
    dfsVisit3_9(source);
    }

void Graph::dfsVisit3_9(Airport *v) const {
    v->setVisited(true);

    for (auto &flight: v->getFlights()) {
        Airport *w = flight->getDest();
        if (!w->isVisited()) {
            dfsVisit3_9(w);
        }
    }
}




vector<Flight *> Graph::getBestFlightOption_AirportCode(const string& sourceCode, const string& destinationCode) const {
    Airport* sourceAirport = findAirport(sourceCode);
    Airport* destinationAirport = findAirport(destinationCode);

    if (!sourceAirport || !destinationAirport) {
        return {};
    }

    unordered_map<Airport*, vector<Flight*>> bestFlights;
    queue<Airport*> q;
    q.push(sourceAirport);
    bestFlights[sourceAirport] = vector<Flight*>();

    while (!q.empty()) {
        Airport* currentAirport = q.front();
        q.pop();

        for (Flight* flight : currentAirport->getFlights()) {
            Airport* nextAirport = flight->getDest();

            if (bestFlights.find(nextAirport) == bestFlights.end()) {
                bestFlights[nextAirport] = bestFlights[currentAirport];
                bestFlights[nextAirport].push_back(flight);
                q.push(nextAirport);
            }
        }
    }
    // Retrieve the best flights for the destination airport
    vector<Flight*> bestFlightsToDestination = bestFlights[destinationAirport];


    return bestFlightsToDestination;
}

vector<Flight *> Graph::getBestFlightOption_AirportName(const string& sourceName, const string& destinationName) const{
    Airport* sourceAirport = nullptr;
    Airport* destinationAirport = nullptr;

    for (Airport* airport : airportSet) {
        if (airport->getAirportInfo().getName() == sourceName) {
            sourceAirport = airport;
            break;
        }
    }

    for (Airport* airport : airportSet) {
        if (airport->getAirportInfo().getName() == destinationName) {
            destinationAirport = airport;
            break;
        }
    }


    if (!sourceAirport || !destinationAirport) {
        return {};
    }

    unordered_map<Airport*, vector<Flight*>> bestFlights;
    queue<Airport*> q;
    q.push(sourceAirport);
    bestFlights[sourceAirport] = vector<Flight*>();

    while (!q.empty()) {
        Airport* currentAirport = q.front();
        q.pop();

        for (Flight* flight : currentAirport->getFlights()) {
            Airport* nextAirport = flight->getDest();

            if (bestFlights.find(nextAirport) == bestFlights.end()) {
                bestFlights[nextAirport] = bestFlights[currentAirport];
                bestFlights[nextAirport].push_back(flight);
                q.push(nextAirport);
            }
        }
    }

    // Retrieve the best flights for the destination airport
    vector<Flight*> bestFlightsToDestination = bestFlights[destinationAirport];

    return bestFlightsToDestination;
}

vector<vector<Flight*>> Graph::getBestFlightOption_CityName(const string& sourceCity, const string& destinationCity) const{
    vector<vector<Flight*>> bestFlights;

    // Find all airports in the source city
    vector<Airport*> sourceAirports;
    for (Airport* airport : airportSet) {
        if (airport->getAirportInfo().getCity() == sourceCity) {
            sourceAirports.push_back(airport);
        }
    }

    // Find all airports in the destination city
    vector<Airport*> destinationAirports;
    for (Airport* airport : airportSet) {
        if (airport->getAirportInfo().getCity() == destinationCity) {
            destinationAirports.push_back(airport);
        }
    }

    for (Airport* sourceAirport : sourceAirports) {
        for (Airport* destinationAirport : destinationAirports) {
            if (sourceAirport != destinationAirport) {
                // Use BFS to find the best flights between the current pair
                unordered_map<Airport*, vector<Flight*>> bestFlightsMap;
                queue<Airport*> q;
                q.push(sourceAirport);
                bestFlightsMap[sourceAirport] = vector<Flight*>();

                while (!q.empty()) {
                    Airport* currentAirport = q.front();
                    q.pop();

                    for (Flight* flight : currentAirport->getFlights()) {
                        Airport* nextAirport = flight->getDest();

                        if (bestFlightsMap.find(nextAirport) == bestFlightsMap.end()) {
                            bestFlightsMap[nextAirport] = bestFlightsMap[currentAirport];
                            bestFlightsMap[nextAirport].push_back(flight);
                            q.push(nextAirport);
                        }
                    }
                }

                vector<Flight*> bestFlightsToDestination = bestFlightsMap[destinationAirport];
                bestFlights.push_back(bestFlightsToDestination);
            }
        }
    }

    return bestFlights;
}

vector<string> Graph::getListOfAirportCodes() const {
    vector<string> res = {};

    for (Airport* airport: airportSet) {
        res.push_back(airport->getAirportInfo().getCode());
    }

    return res;
}

vector<Airport *> Graph::getAirportsInCity(string &city) {

    vector<Airport*> airports;
    for (Airport* airport : airportSet) {
        if (airport->getAirportInfo().getCity() == city) {
            airports.push_back(airport);
        }
    }

    return airports;
}

vector<Airport*> Graph::findClosestAirports(double lat, double lon) const {
    vector<Airport*> closesteAirports;
    double minDistance = 100000000000;
    for(auto airport : airportSet){
        double distance = haversineDistance(lat, lon, airport->getAirportInfo().getLatitude(),airport->getAirportInfo().getLongitude());

        if(distance < minDistance){
            minDistance = distance;
            closesteAirports.clear();
            closesteAirports.push_back(airport);
        } else if (distance == minDistance){
            closesteAirports.push_back(airport);
        }
    }
    return closesteAirports;
}

vector<Airport*> Graph::findClosestAirports(double lat, double lon, double maxDistance) const{
    vector<Airport*> closestAirports;
    for(auto airport : airportSet){
        double distance = haversineDistance(lat,lon,airport->getAirportInfo().getLatitude(),airport->getAirportInfo().getLongitude());

        if(distance <= maxDistance){
            closestAirports.push_back(airport);
        }
    }
    return closestAirports;
}

double Graph::haversineDistance(double lat1, double lon1, double lat2, double lon2) const {
    const double R = 6371.0; //Raio da terra em km

    //Converter de graus pra radianos
    lat1 = lat1 * M_PI/180.0;
    lon1 = lon1 * M_PI/180.0;
    lat2 = lat2 * M_PI/180.0;
    lon2 = lon2 * M_PI/180.0;

    double deltalat = lat2 - lat1;
    double deltalon = lon2 - lon1;
    double a = sin(deltalat/2.0) * sin(deltalat/2.0) + cos(lat1) * cos(lat2) * sin(deltalon/2.0) * sin(deltalon/2.0);
    double c = 2.0 * atan2(sqrt(a),sqrt(1.0 - a));

    double distance = R * c;
    return distance;
}

vector<Flight*> Graph::getBestFlightOptionToClosestAirports(string& airportCode) const {
    auto airport = findAirport(airportCode);
    vector<Airport*> closestAirportsSource = findClosestAirports(airport->getAirportInfo().getLatitude(),airport->getAirportInfo().getLongitude());

    vector<Flight*> bestFlightOptions;

    for (Airport* destAirport : closestAirportsSource) {
        vector<Flight*> currentFlightOption = getBestFlightOption_AirportCode(airport->getAirportInfo().getCode(),destAirport->getAirportInfo().getCode());
        bestFlightOptions.insert(bestFlightOptions.end(), currentFlightOption.begin(), currentFlightOption.end());
    }

    return bestFlightOptions;
}

vector<Flight*> Graph::getBestFlightOptionToClosestAirports_Distance(string& airportCode, double maxDistance) const {
    auto airport = findAirport(airportCode);
    vector<Airport*> closestAirportsSource = findClosestAirports(
            airport->getAirportInfo().getLatitude(),
            airport->getAirportInfo().getLongitude(),
            maxDistance
    );

    vector<Flight*> bestFlightOptions;

    for (Airport* destAirport : closestAirportsSource) {
        vector<Flight*> currentFlightOption = getBestFlightOption_AirportCode(
                airport->getAirportInfo().getCode(),
                destAirport->getAirportInfo().getCode()
        );

        bestFlightOptions.insert(
                bestFlightOptions.end(),
                currentFlightOption.begin(),
                currentFlightOption.end()
        );
    }

    return bestFlightOptions;
}