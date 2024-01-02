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

    return graph.getNumAirports();
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

unordered_map<string,int> Data::getNumFlightsPerCity() {
    unordered_map<string,int> flightsPerCity;

    for(auto airport : graph.getAirportSet()){
        auto city = airport->getAirportInfo().getCity();
        const int numFlights = static_cast<int>(airport->getFlights().size());

        flightsPerCity[city] += numFlights;
    }
    return flightsPerCity;
}

unordered_map<string,int> Data::getNumFlightsPerAirline() {
    unordered_map<string,int> flightsPerAirline;
    for(auto airport : graph.getAirportSet()){
        auto flights = airport->getFlights();

        for(auto flight : flights){
            auto airlineCode = flight->getAirlineCode();

            flightsPerAirline[airlineCode]++;
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
    set<Airport*> visitedAirports = {};
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
    vector<pair<Airport*, Airport*>> longestPairs;

    for (Airport* source : graph.getAirportSet()) {
        vector<pair<Airport*, int>> distances = graph.bfsLongestDistance(source);

        // Track the maximum distance found for the current source airport
        int maxDistance = 0;

        // Store pairs of airports for the longest trips found
        vector<pair<Airport*, Airport*>> currentLongestPairs;

        for (const auto& distancePair : distances) {
            int currentDistance = distancePair.second;

            if (currentDistance > maxDistance) {
                maxDistance = currentDistance;
                currentLongestPairs.clear();
                currentLongestPairs.emplace_back(source, distancePair.first);
            } else if (currentDistance == maxDistance) {
                currentLongestPairs.emplace_back(source, distancePair.first);
            }
        }

        // Append currentLongestPairs to longestPairs
        longestPairs.insert(longestPairs.end(), currentLongestPairs.begin(), currentLongestPairs.end());
    }

    return longestPairs;
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
    vector<Airport*> essentialAirportsList;

    for (Airport* currentAirport : graph.getAirportSet()) {
        // Temporarily mark the current airport as ignored
        currentAirport->setIgnored(true);

        // Perform a traversal from another airport
        graph.dfs3_9(); // Or use any appropriate traversal method here

        // Check if all non-ignored airports are reachable
        bool allNonIgnoredAirportsReachable = true;
        for (Airport* airport : graph.getAirportSet()) {
            if (!airport->isIgnored() && !airport->isVisited()) {
                allNonIgnoredAirportsReachable = false;
                break;
            }
        }

        // If any non-ignored airport becomes unreachable, mark the current airport as essential
        if (!allNonIgnoredAirportsReachable) {
            essentialAirportsList.push_back(currentAirport);
        }

        // Reset the ignored status of the current airport for the next iteration
        currentAirport->setIgnored(false);
    }

    return essentialAirportsList;
}


