#ifndef PROJ_AED2_DATA_H
#define PROJ_AED2_DATA_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <set>
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
    static int getNumDestFromSource(const string& airportCode, int choice);

    //3.6
    static int numReachableDestinations(const string& startAirport, int layouts, int choice);

    //3.7 -> este ta mal acho eu
    static vector<pair<Airport*, Airport*>> longestTrips();

    //3.8
    static vector<Airport*> topAirportsByFlights(int k);

    //3.9
    static vector<Airport*> essentialAirports() ;

    //4.1
    [[nodiscard]] static vector<Flight *> getBestFlightOption_AirportCode(const string& sourceCode, const string& destinationCode) ;
    static vector<Flight*> getBestFlightOption_AirportName(const string& sourceName, const string& destinationName) ;
    static string getAirportNameByCode(const string& code);
    static string getAirlineNameByCode(const string& code);



    vector<vector<Flight*>> getBestFlightOption_CityName(const string& sourceCity, const string& destinationCity) const;
    vector<Airport*> findClosestAirports(double lat, double lon) const;
    vector<Airport*> findClosestAirports(double lat, double lon,double maxDistance) const;
    double haversineDistance(double lat1, double lon1, double lat2, double lon2) const;
    vector<Flight*> getBestFlightOptionToClosestAirports(string& airportCode) const;
    vector<Flight*> getBestFlightOptionToClosestAirports_Distance(string& airportCode, double maxDistance) const;
};


#endif //PROJ_AED2_DATA_H