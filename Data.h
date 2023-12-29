#ifndef PROJ_AED2_DATA_H
#define PROJ_AED2_DATA_H

#include <vector>
#include <unordered_map>
#include "Airline.h"
#include "Graph.h"


class Data {
private:
     // Graph structure with airports as vertices and flights as edges
    unordered_map<string, Airline> airlines; // Map to store airline details (Airline struct/class needed)

public:
    Data();
    Graph graph;

    // Methods to populate data structures from CSV files
    void readAirports(const string& airportsFilePath);
    void readAirlines(const string& airlinesFilePath);
    void readFlights(const string& flightsFilePath);

};


#endif //PROJ_AED2_DATA_H