#include "Data.h"
#include <fstream>
#include <sstream>
#include <iostream>

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
    return graph.getNumFlights();
}


bool Data::isValidAirportCode(const string& airportCode) {
    // Assume you have a vector or another container containing valid airport codes/names
    vector<string> validAirportCodes = graph.getListOfAirportCodes(); // Sample list

    // Check if the entered code is present in the list
    return (find(validAirportCodes.begin(), validAirportCodes.end(), airportCode) != validAirportCodes.end());
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