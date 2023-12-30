#ifndef PROJ_AED2_DATA_H
#define PROJ_AED2_DATA_H

#include <vector>
#include <unordered_map>
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

    static int getNumAirports();

    static int getNumFlights();

};


#endif //PROJ_AED2_DATA_H