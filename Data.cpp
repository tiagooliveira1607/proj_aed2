#include "Data.h"


Graph Data::graph;
unordered_map<string, Airline> Data::airlines;


Data::Data() {

    graph = Graph();
    airlines = {};

    string airportsFilepath = "../dataset/airports.csv";
    string flightsFilepath = "../dataset/flights.csv";
    string airlinesFilepath = "../dataset/airlines.csv";


    readAirports(airportsFilepath);
    readFlights(flightsFilepath);
    readAirlines(airlinesFilepath);
}


void Data::readAirports(const string& airportsFilePath) {
    // Read and parse airports data
    ifstream airportsFile(airportsFilePath);

    if (!airportsFile.is_open()) {
        cerr << "Error opening airports.csv" << endl;
        return;
    }

    string line;
    getline(airportsFile, line); // Skip header line

    while (getline(airportsFile, line)) {
        istringstream ss(line);
        string code, name, city, country;
        double latitude, longitude;

        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        ss >> latitude;
        ss.ignore(); // Ignore the comma
        ss >> longitude;

        // Create nodes in the graph using airport information
        graph.addAirport(AirportInfo(code,name,city, country, latitude, longitude));
    }
    airportsFile.close();
}


void Data::readFlights(const string &flightsFilePath) {
    //read and parse flights data
    ifstream flightsFile(flightsFilePath);

    if (!flightsFile.is_open()) {
        cerr << "Error opening airports.csv" << endl;
        return;
    }

    string line;
    getline(flightsFile, line); // Skip header line

    while (getline(flightsFile, line)) {
        istringstream ss(line);
        string sourceCode, destCode, airlineCode;

        getline(ss, sourceCode, ',');
        getline(ss, destCode, ',');
        getline(ss, airlineCode, '\n');

        // Create edges in the graph using flights information
        graph.addFlight(sourceCode,destCode, airlineCode);
    }
    flightsFile.close();
}


void Data::readAirlines(const string &airlinesFilePath){
    // Read and parse airports data
    ifstream airlinesFile(airlinesFilePath);

    if (!airlinesFile.is_open()) {
        cerr << "Error opening airports.csv" << endl;
        return;
    }

    string line;
    getline(airlinesFile, line); // Skip header line

    while (getline(airlinesFile, line)) {
        istringstream ss(line);
        string code, name, callsign, country;

        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callsign, ',');
        getline(ss, country, ',');

        airlines.insert(make_pair(code, Airline(name, callsign, country)));
    }
    airlinesFile.close();
}

int Data::getNumAirports() {

    return graph.getAirportSet().size();
}

int Data::getNumFlights() {
    int total = 0;
    for(auto airport : graph.getAirportSet()){
        total += airport->getFlights().size();
    }
    return total;
}

pair<int,int> Data::airportFlightStats(const string &airportCode) {
    auto airport = graph.findAirport(airportCode);

    if(airport == nullptr) return {0,0};

    auto flights = airport->getFlights();

    unordered_set<string> airlines;

    for(auto flight : flights){
        airlines.insert(flight->getAirlineCode());
    }
    return {flights.size(), airlines.size()};
}

map<string,int> Data::getNumFlightsPerCity() {
    map<string, int> flightsPerCity;

    for (auto airport : graph.getAirportSet()) {
        auto city = airport->getAirportInfo().getCity();
        const int numFlights = static_cast<int>(airport->getFlights().size());

        flightsPerCity[city] += numFlights;
    }

    return flightsPerCity;
}

map<string,int> Data::getNumFlightsPerAirline() {
    map<string,int> flightsPerAirline;
    for(auto airport : graph.getAirportSet()){
        auto flights = airport->getFlights();

        for(auto flight : flights){
            auto airlineName = getAirlineNameByCode(flight->getAirlineCode());

            flightsPerAirline[airlineName]++;
        }
    }


    return flightsPerAirline;
}



int Data::getNumCountriesFlyingToAirport(string &airportCode) {
    auto airport = graph.findAirport(airportCode);

    if(!airport){
        return -1;
    }

    unordered_set<string> countries;

    auto flights = airport->getFlights();
    for(auto flight : flights){
        auto dest = flight->getDest();
        auto destCountry = dest->getAirportInfo().getCountry();

        countries.insert(destCountry);
    }

    return static_cast<int>(countries.size());
}

int Data::getNumCountriesFlyingToCity(string &city) {
    vector<Airport*> airports = graph.getAirportsInCity(city);



    unordered_set<string> countries;
    for (Airport* airport : airports ) {
        auto flights = airport->getFlights();
        for (auto flight: flights) {
            auto dest = flight->getDest();
            auto destCountry = dest->getAirportInfo().getCountry();

            countries.insert(destCountry);
        }
    }

    return static_cast<int>(countries.size());
}


int Data::getNumDestFromSource(const string &airportCode, int choice){
    auto source = graph.findAirport(airportCode);

    if(!source) return -1;

    unordered_set<string> destinations;

    switch (choice) {
        case 1:
            for(auto flight : source->getFlights()){
                destinations.insert(flight->getDest()->getAirportInfo().getCode());
            }
            break;
        case 2:
            for(auto flight : source->getFlights()){
                destinations.insert(flight->getDest()->getAirportInfo().getCity());
            }
            break;

        case 3:
            for(auto flight : source->getFlights()){
                destinations.insert(flight->getDest()->getAirportInfo().getCountry());
            }
            break;
    }


    return static_cast<int>(destinations.size());
}


int Data::numReachableDestinations(const string &startAirportCode, int layouts, int choice) {
    auto startAirport = graph.findAirport(startAirportCode);

    if(!startAirport) return -1;

    graph.bfs(startAirportCode,layouts);
    set<Airport*> visitedAirports;
    for (Airport *airport: graph.getAirportSet()) {
        if (airport->isVisited()) {
            visitedAirports.insert(airport);
        }
    }

    switch (choice) {
        case 1:
            return static_cast<int>(visitedAirports.size());

        case 2: {
            set<string> cities = {};
            for (Airport* airport : visitedAirports) {
                cities.insert(airport->getAirportInfo().getCity());
            }
            return static_cast<int>(cities.size());}

        case 3: {
            set<string> countries = {};
            for (Airport* airport : visitedAirports) {
                countries.insert(airport->getAirportInfo().getCountry());
            }
            return static_cast<int>(countries.size());
        }
    }
    return 0;
}

vector<pair<Airport*, Airport*>> Data::longestTrips() {
    vector<pair<Airport*, Airport*>> maxTrips;
    int maxStops = 0;

    for (Airport* source : graph.getAirportSet()) {

        stack<std::pair<Airport*, int>> dfsStack;
        dfsStack.push({source, 0});

        while (!dfsStack.empty()) {
            auto currentPair = dfsStack.top();
            dfsStack.pop();

            Airport* current = currentPair.first;
            int stops = currentPair.second;

            if (stops > maxStops) {
                maxStops = stops;
                maxTrips.clear();
                maxTrips.emplace_back(source, current);
            } else if (stops == maxStops) {
                maxTrips.emplace_back(source, current);
            }

            for (Flight* flight : current->getFlights()) {
                Airport* dest = flight->getDest();
                if (!dest->isVisited()) {
                    dest->setVisited(true);
                    dfsStack.push({dest, stops + 1});
                }
            }
        }

        for (Airport* airport : graph.getAirportSet()) {
            airport->setVisited(false);
        }
    }

    return maxTrips;
}

//Create a struct to store airport with number of flights
struct AirportWithFlights {
    Airport* airport;
    int flightsCount;

    AirportWithFlights(Airport* ap, int count) : airport(ap), flightsCount(count) {}
};



bool compareByFlights(const AirportWithFlights& a, const AirportWithFlights& b) {
    return a.flightsCount > b.flightsCount; // Sort in descending order
}

vector<Airport*> Data::topAirportsByFlights(int k) {
    vector<AirportWithFlights> airportsWithFlights;

    for (auto airport : graph.getAirportSet()) {
        int flightsCount = airport->getFlights().size();
        airportsWithFlights.push_back(AirportWithFlights(airport, flightsCount));
    }

    // Sort the airports by the number of flights
    sort(airportsWithFlights.begin(), airportsWithFlights.end(), compareByFlights);

    vector<Airport*> topAirports;
    for (int i = 0; i < k && i < airportsWithFlights.size(); ++i) {
        topAirports.push_back(airportsWithFlights[i].airport);
    }

    return topAirports;
}

vector<Airport*> Data::essentialAirports() {
    unordered_map<Airport*, int> disc;    // Discovery time
    unordered_map<Airport*, int> low;     // Earliest visited vertex reachable from subtree rooted with current vertex
    unordered_map<Airport*, Airport*> parent;  // To store parent vertices in DFS tree
    unordered_set<Airport*> articulationPoints;

    int time = 0;

    // Initialize visited and parent arrays
    for (Airport* u : graph.getAirportSet()) {
        disc[u] = 0;
        low[u] = 0;
        parent[u] = nullptr;
    }

    // Call the recursive helper function to find articulation points in DFS tree rooted with vertex 'i'
    for (Airport* u : graph.getAirportSet()) {
        if (!disc[u]) {
            dfsArticulationPoints(u, time, disc, low, parent, articulationPoints);
        }
    }

    // Convert unordered_set to vector
    vector<Airport*> essentialAirports(articulationPoints.begin(), articulationPoints.end());

    return essentialAirports;
}

void Data::dfsArticulationPoints(Airport* u, int& time, unordered_map<Airport*, int>& disc, unordered_map<Airport*, int>& low, unordered_map<Airport*, Airport*>& parent, unordered_set<Airport*>& articulationPoints){
    int children = 0;
    disc[u] = low[u] = ++time;

    for (const Flight* flight : u->getFlights()) {
        Airport* v = flight->getDest();

        if (!disc[v]) {
            children++;
            parent[v] = u;
            dfsArticulationPoints(v, time, disc, low, parent, articulationPoints);

            low[u] = min(low[u], low[v]);

            if (low[v] >= disc[u] && parent[u] != nullptr)
                articulationPoints.insert(u);
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (parent[u] == nullptr && children > 1)
        articulationPoints.insert(u);
}

vector<Flight *> Data::getBestFlightOption_AirportCode(const string& sourceCode, const string& destinationCode) {
    Airport* sourceAirport = graph.findAirport(sourceCode);
    Airport* destinationAirport = graph.findAirport(destinationCode);

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
    vector<Flight*> bestFlightsToDestination = bestFlights[destinationAirport];


    return bestFlightsToDestination;
}

vector<Flight *> Data::getBestFlightOption_AirportName(const string& sourceName, const string& destinationName) {
    Airport* sourceAirport = nullptr;
    Airport* destinationAirport = nullptr;

    for (Airport* airport : graph.getAirportSet()) {
        if (airport->getAirportInfo().getName() == sourceName) {
            sourceAirport = airport;
            break;
        }
    }

    for (Airport* airport : graph.getAirportSet()) {
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

    vector<Flight*> bestFlightsToDestination = bestFlights[destinationAirport];

    return bestFlightsToDestination;
}

string Data::getAirportNameByCode(const string &code) {
    string airportName;
    for (Airport* airport : graph.getAirportSet()){
        if (airport->getAirportInfo().getCode() == code) {
            airportName = airport->getAirportInfo().getName();
        }
    }
    return airportName;
}

string Data::getAirlineNameByCode(const string &code) {
    auto airlineName = airlines.at(code).getName();
    return airlineName;
}



vector<vector<Flight*>> Data::getBestFlightOption_CityName(const string& sourceCity, const string& destinationCity){
    vector<vector<Flight*>> bestFlights;

    vector<Airport*> sourceAirports;
    for (Airport* airport : graph.getAirportSet()) {
        if (airport->getAirportInfo().getCity() == sourceCity) {
            sourceAirports.push_back(airport);
        }
    }

    vector<Airport*> destinationAirports;
    for (Airport* airport : graph.getAirportSet()) {
        if (airport->getAirportInfo().getCity() == destinationCity) {
            destinationAirports.push_back(airport);
        }
    }

    for (Airport* sourceAirport : sourceAirports) {
        for (Airport* destinationAirport : destinationAirports) {
            if (sourceAirport != destinationAirport) {

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


vector<Airport*> Data::findClosestAirports(double lat, double lon) const {
    vector<Airport*> closestAirports;
    double minDistance = 1000000000;

    for (auto airport : graph.getAirportSet()) {
        double distance = haversineDistance(lat, lon, airport->getAirportInfo().getLatitude(), airport->getAirportInfo().getLongitude());

        if (distance < minDistance) {
            minDistance = distance;
            closestAirports.clear();
            closestAirports.push_back(airport);
        } else if (distance == minDistance) {
            closestAirports.push_back(airport);
        }
    }

    return closestAirports;
}


double Data::haversineDistance(double lat1, double lon1, double lat2, double lon2) const {
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

vector<Flight*> Data::getBestFlightOptionToClosestAirports(double lat, double lon) const {
    auto sourceAirport = graph.getAirportByCoordinates(lat,lon);

    vector<Airport*> closestAirportsSource = findClosestAirports(lat,lon);
    vector<Flight*> bestFlightOptions;

    for (Airport* destAirport : closestAirportsSource) {
        vector<Flight*> currentFlightOption = getBestFlightOption_AirportCode(sourceAirport->getAirportInfo().getCode(),destAirport->getAirportInfo().getCode());
        bestFlightOptions.insert(bestFlightOptions.end(), currentFlightOption.begin(), currentFlightOption.end());
    }

    return bestFlightOptions;
}


bool Data::isValidAirportCode(const string &code) {
    vector<string> airportCodes = graph.getListOfAirportCodes();
    for (const string& airportCode : airportCodes) {
        if (airportCode == code) {
            return true;
        }
    }
    return false;
}

bool Data::isValidAirportName(const string &name) {
    vector<string> airportNames = graph.getListOfAirportNames();

    for (const string& airportName : airportNames) {
        if (airportName == name) {
            return true;
        }
    }
    return false;
}

bool Data::isValidCityName(const string &name) {
    vector<string> cityNames = graph.getListOfCityNames();

    for (const string &cityName: cityNames) {
        if (cityName == name) {
            return true;
        }
    }

    return false;
}

