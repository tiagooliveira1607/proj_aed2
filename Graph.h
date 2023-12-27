#ifndef PROJ_AED2_GRAPH_H
#define PROJ_AED2_GRAPH_H

#include <vector>
#include <list>
#include <string>

using namespace std;

class Flight;

class AirportInfo {
    string code, name, city, country;
    double latitude, longitude;

public:
    AirportInfo(const string& code, const string& name, const string& city, const string& country, const double latitude, const double longitude);

    // Getters
    const string& getCode() const;
    const string& getName() const;
    const string& getCity() const;
    const string& getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

    friend class Airport;
};

class Airport {
    AirportInfo airportInfo;
    vector<Flight*> flights;
    bool visited;

public:
    explicit Airport(const AirportInfo& airportInfo);
    Airport(const string &code, const string &name, const string &city, const string &country, const double latitude, const double longitude);
    ~Airport();

    const AirportInfo& getAirportInfo() const;
    void setAirportInfo(const AirportInfo& info);

    bool isVisited() const;
    void setVisited(bool v);

    const vector<Flight*>& getFlights() const;
    void addFlight(Airport* dest, const string& airlineCode);
    void removeFlightTo(Airport* d);
    friend class Graph;
};

class Flight {
    Airport* dest;
    string airlineCode;

public:
    Flight(Airport* d, const string& airlineCode);

    Airport* getDest() const;
    void setDest(Airport* dest) const;

    const string& getAirlineCode() const;
    void setAirlineCode() const;

    friend class Graph;
    friend class Airport;
};

class Graph {
    vector<Airport*> airportSet;

public:
    Airport* findAirport(const string& airportCode) const;
    void addAirport(const AirportInfo& info);
    bool removeAirport(const string& airportCode); //return true if airport exists/is successfully removed
    void addFlight(const string &sourcCode, const string& destCode, const string& airlineCode);
    const vector<Airport*>& getAirportSet() const;
};

#endif //PROJ_AED2_GRAPH_H