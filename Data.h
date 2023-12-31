#ifndef PROJ_AED2_DATA_H
#define PROJ_AED2_DATA_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "Airline.h"
#include "Graph.h"


class Data {
private:

    static Graph graph; // Graph structure with airports as vertices and flights as edges
    static unordered_map<string, Airline> airlines; // Map to store airline details (Airline struct/class needed)


public:
    Data();

    // Methods to populate data structures from CSV files
    static void readAirports(const string& airportsFilePath);
    static void readAirlines(const string& airlinesFilePath);
    static void readFlights(const string& flightsFilePath);

    //3.1
    static int getNumAirports();
    static int getNumFlights();

    //3.2
    static pair<int,int> airportFlightStats(const string& airportCode) ;

    //3.3
    static unordered_map<string,int> getNumFlightsPerCity();
    static unordered_map<string,int> getNumFlightsPerAirline();

    //3.4
    static int getNumCountriesFlyingToAirport(string& airportCode);
    static int getNumCountriesFlyingToCity(string& airportCode);

    //3.5
    static int getNumAirportsFromAirport(const string& airportCode);
    static int getNumCitiesFromAirport(const string &airportCode);
    static int getNumCountriesFromAirport(const string &airportCode);

    //3.6
    int numReachableDestinations(const string& startAirport, int layouts) const;

};


#endif //PROJ_AED2_DATA_H