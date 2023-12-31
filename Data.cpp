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


int Data::getNumAirportsFromAirport(const string &airportCode){
    auto source = graph.findAirport(airportCode);

    if(!source) return -1;

    unordered_set<string> destinations;

    for(auto flight : source->getFlights()){
        destinations.insert(flight->getDest()->getAirportInfo().getCode());
    }

    return static_cast<int>(destinations.size());
}

int Data::getNumCitiesFromAirport(const string &airportCode) {
    auto source = graph.findAirport(airportCode);

    if(!source) return -1;

    unordered_set<string> destinations;

    for(auto flight : source->getFlights()){
        destinations.insert(flight->getDest()->getAirportInfo().getCity());
    }

    return static_cast<int>(destinations.size());
}

int Data::getNumCountriesFromAirport(const string &airportCode) {
    auto source = graph.findAirport(airportCode);

    if(!source) return -1;

    unordered_set<string> destinations;

    for(auto flight : source->getFlights()){
        destinations.insert(flight->getDest()->getAirportInfo().getCountry());
    }

    return static_cast<int>(destinations.size());
}


int Data::numReachableDestinations(const string &startAirportCode, int layouts) const {
    auto startAirport = graph.findAirport(startAirportCode);

    if(!startAirport) return -1;

    int count = 0;
    unordered_set<string> visitedDestinations;

    queue<pair<Airport*,int>> bfsQ;
    bfsQ.push({startAirport,0});

    while(!bfsQ.empty()){
        auto currentPair = bfsQ.front();
        bfsQ.pop();

        auto currentAirport = currentPair.first;
        int stops = currentPair.second;

        if(stops > layouts) break;

        visitedDestinations.insert(currentAirport->getAirportInfo().getCode());

        for(auto flight : currentAirport->getFlights()){
            auto nextAirport = flight->getDest();
            string nextAirportCode = nextAirport->getAirportInfo().getCode();

            if(visitedDestinations.find(nextAirportCode) == visitedDestinations.end()) {

                bfsQ.push({nextAirport, stops + 1});
                visitedDestinations.insert(nextAirportCode);
                count++;
            }
        }
    }
    return count;
}

