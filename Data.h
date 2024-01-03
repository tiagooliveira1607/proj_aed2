#ifndef PROJ_AED2_DATA_H
#define PROJ_AED2_DATA_H


#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include <stack>
#include "Airline.h"
#include "Graph.h"


class Data {
private:

    static Graph graph; // Graph structure with airports as vertices and flights as edges
    static unordered_map<string, Airline> airlines; // Map to store airline details


public:
    /**
     * @brief Constructor of the Data class. When used reads the three csv files.
     * @details Time Complexity: O(1).
     */
    Data();

    /**
     * @brief Verifies if a given airport code is valid or not.
     * @details Time Complexity: O(n).
     * @param code String that represents the code of an airport.
     * @return True is the given code is valid, false otherwise.
     */
    static bool isValidAirportCode(const string& code);

    /**
     * @brief Verifies if a given airport name is valid or not.
     * @details Time Complexity: O(n).
     * @param name String that represents the name of an airport.
     * @return True if the airport name is valid, false otherwise.
     */
    static bool isValidAirportName(const string& name);

    /**
     * @brief Verifies if a city name is valid or not.
     * @details Time Complexity: O(n).
     * @param name String that represents a city name.
     * @return True if the city name is valid or not.
     */
    static bool isValidCityName(const string& name);

    /**
     * @brief Reads the airport.csv file.
     * @details Time Complexity: O(n).
     * @param airportsFilePath Path to the airport.csv file.
     */
    static void readAirports(const string& airportsFilePath);

    /**
     * @brief Reads the airlines.csv file.
     * @details Time Complexity: O(n).
     * @param airlinesFilePath Path to the airlines.csv file.
     */
    static void readAirlines(const string& airlinesFilePath);

    /**
     * @brief Reads the flights.csv file.
     * @details Time Complexity: O(n).
     * @param flightsFilePath Path to the flights.csv file.
     */
    static void readFlights(const string& flightsFilePath);

    /**
     * @brief Used to get the global number of airports.
     * @details Time Complexity: O(1).
     * @return Integer representing the amount of airports.
     */
    static int getNumAirports();

    /**
     * @brief Used to get the global number of flights.
     * @details Time Complexity: O(n).
     * @return Integer representing the amount of flights.
     */
    static int getNumFlights();

    /**
     * @brief Number of flights out of an airport, and from how many
     * different airlines.
     * @details Time Complexity: O(log N + M) where N is the total amount of airports and M is the
     * maximum number of flights departing from the airport.
     * @param airportCode Code of the airport.
     * @return A pair where the first the amount of flights and second is
     * the amount of different airlines are involved.
     */
    static pair<int,int> airportFlightStats(const string& airportCode) ;

    /**
     * @brief Number of flights per city.
     * @details Time complexity: O(n).
     * @details Number of flights where the city is the source.
     * @return Map where the key is a string representing the city name
     * and the value is an integer representing the amount of flights.
     */
    static map<string, int> getNumFlightsPerCity();

    /**
     * @brief Number of flights per airline.
     * @details Time complexity: O(n^2)
     * @details Number of flights where each airline is involved.
     * @return Map where the key is a string representing the airline name
     * and the value is an integer representing the amount of flights.
     */
    static map<string, int> getNumFlightsPerAirline();

    /**
     * @brief Number of different countries you can go from an airport.
     * @details Time complexity: O(n).
     * @param airportCode String representing the airport code.
     * @return The amount of different countries you can go from an airport.
     */
    static int getNumCountriesFlyingToAirport(string& airportCode);

    /**
     * @brief Number of different countries you can go from a city.
     * @details Time complexity: O(n^2).
     * @param airportCode String representing the airport code.
     * @return The amount of different countries you can go from a city.
     */
    static int getNumCountriesFlyingToCity(string& airportCode);

    /**
     * @brief Number of destinations (airports, cities or countries) from a
     * given airport.
     * @details Time complexity: O(n).
     * @param airportCode String representing the airport code.
     * @param choice Integer that will make the function return something
     * different depending what the user wants.
     * @return Depending on the integer chosen the function returns the number of
     * airports/cities/countries available for a given airport.
     */
    static int getNumDestFromSource(const string& airportCode, int choice);

    /**
     * @brief Number of destinations (airports,cities or countries) from
     * a given airport with a maximum number of stops.
     * @details Time complexity: O(V + E), V being the amount of airports
     * and E the number of flights in the graph.
     * @param startAirport String representing the code of the source airport.
     * @param layouts Integer representing the amount of stops chosen by the user.
     * @param choice Integer that user chooses depending on what he wants.
     * @return Returns the amount of airports,cities or countries depending
     * on the number chosen by the user and the amount of stops that the user wants.
     */
    static int numReachableDestinations(const string& startAirport, int layouts, int choice);

    /**
     * @brief Maximum trip and corresponding path where the number of stops
     * is the greatest
     * @details Time complexity: O(V + E).
     * @return The path where the amount of stops is the greatest.
     */
    static vector<pair<Airport*, Airport*>> longestTrips();

    /**
     * @brief Function that gives the top-k airports with the greatest
     * number of flights.
     * @details Time complexity: O(V log V) where V is the number
     * of airports.
     * @param k The amount of airports the user wants to be shown.
     * @return The top-k airports where the number of flights is the biggest.
     */
    static vector<Airport*> topAirportsByFlights(int k);

    /**
     * @brief Function that identifies which airports are
     * articulation points.
     * @details Time complexity: O(V + E).
     * @param u Current airport being visited by dfs.
     * @param time A reference to the current time or timestamp
     * during the dfs.
     * @param disc A map to store the discovery time (timestamps) of each
     * airports.
     * @param low A map to store the lowest timestamp reachable from the current
     * airport through both tree and back edges.
     * @param parent A map to store the parent of each airport in dfs tree.
     * @param articulationPoints A set to store the discovered articulation points.
     */
    static void dfsArticulationPoints(Airport* u, int& time, unordered_map<Airport*, int>& disc, unordered_map<Airport*, int>& low, unordered_map<Airport*, Airport*>& parent, unordered_set<Airport*>& articulationPoints);

    /**
     * @brief Function that identifies what airports are essential to the graph (meaning
     * that if removed some areas of the network starts to be unreachable).
     * @details Time complexity: O(V + E), V being the number of airports
     * and E the number of flights.
     * @return A vector of airports that are essential to the network.
     */
    static vector<Airport*> essentialAirports();

    /**
     * @brief Function that gives the best flights to go from one airport
     * to another.
     * @details Time complexity: O(V + E), V being the number of airports and
     * E the number of flights.
     * @param sourceCode String representing the code of the source airport.
     * @param destinationCode String representing the code of the destination airport.
     * @return Vector with the least amount of flights in order to reach the
     * destination airport.
     */
    [[nodiscard]] static vector<Flight *> getBestFlightOption_AirportCode(const string& sourceCode, const string& destinationCode);

    /**
     * @brief
     * @details Time complexity: O(V + E), V being the number of airports
     * and E the number of flights.
     * @param sourceName String representing the code of the starting airport.
     * @param destinationName String representing the code of the destination airport.
     * @return Vector containing the least amount of flights in order to reach the
     * destination airport.
     */
    static vector<Flight*> getBestFlightOption_AirportName(const string& sourceName, const string& destinationName);

    /**
     * @brief Auxiliary function that receives an airport code in order to give
     * the airport name.
     * @detail Time complexity: O(n)
     * @param code String representing an airport code.
     * @return String representing the airport name.
     */
    static string getAirportNameByCode(const string& code);

    /**
     * @brief Auxiliary function that receives an airline code in order to give
     * the airline name.
     * @param code String representing an airline code.
     * @return String representing an airline name.
     */
    static string getAirlineNameByCode(const string& code);


    //4.2
    static vector<vector<Flight*>> getBestFlightOption_CityName(const string& sourceCity, const string& destinationCity);

    //4.3

    static vector<Airport*> findClosestAirports(double lat, double lon);
    static double haversineDistance(double lat1, double lon1, double lat2, double lon2);
    static unordered_map<Airport *, vector<Flight *>> getBestFlightOptionToClosestAirports(double lat, double lon);
    static Airport* getAirportByCoordinates(const double& lat, const double& lon);
};


#endif //PROJ_AED2_DATA_H