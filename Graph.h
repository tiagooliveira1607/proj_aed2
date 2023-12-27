#ifndef PROJ_AED2_GRAPH_H
#define PROJ_AED2_GRAPH_H

#include <vector>
#include <list>
#include <string>
#include <queue>

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
    bool processing;
    int indegree;
    int num;
    int low;

public:
    explicit Airport(const AirportInfo& airportInfo);
    Airport(const string &code, const string &name, const string &city, const string &country, const double latitude, const double longitude);
    ~Airport();

    const AirportInfo& getAirportInfo() const;
    void setAirportInfo(const AirportInfo& info);

    bool isVisited() const;
    void setVisited(bool v);

    bool isProcessing() const;
    void setProcessing(bool p);

    const vector<Flight*>& getFlights() const;

    int getIndegree() const;
    void setIndegree(int indegree);

    int getNum() const;
    void setNum(int num);

    int getLow() const;
    void setLow(int low);

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
    void setDest(Airport* d);

    const string& getAirlineCode() const;
    void setAirlineCode(string& airlineCode);

    friend class Graph;
    friend class Airport;
};

class Graph {
    vector<Airport*> airportSet;

public:
    Airport* findAirport(const string& airportCode) const;
    int getNumAirport() const;
    bool addAirport(const AirportInfo& info);
    bool removeAirport(const string& airportCode); //return true if airport exists/is successfully removed
    bool addFlight(const string &sourcCode, const string& destCode, const string& airlineCode);
    bool removeFlight(const string &sourcCode, const string &destCode) const;
    const vector<Airport*>& getAirportSet() const;

    void dfsVisit(Airport* v, vector<Airport*>& result) const;
    vector<Airport*> dfs() const;
    vector<Airport*> dfs(const string& sourceCode) const;
    vector<Airport*> bfs(const string& sourceCode) const;
    vector<Airport*> topsort() const;
    bool isDAG() const;
    bool dfsIsDAG(Airport* v) const;

};

#endif //PROJ_AED2_GRAPH_H