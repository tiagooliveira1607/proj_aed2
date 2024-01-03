#ifndef PROJ_AED2_AIRLINE_H
#define PROJ_AED2_AIRLINE_H

#include <string>
using namespace std;
/**
 * @brief Class that represents an Airline of a flight.
 */

class Airline {
    string name, callsign, country;

public:
    /**
     * @brief Constructor of the Airline class.
     * @details This constructs an Airline object, that has a name, a callsign and a country. The parameters represent
     * information about an airline including, it's name, callsign and country which it belong to.
     *
     * @param name The fullname of the airline.
     * @param callsign Airline's callsign.
     * @param country Country which the airline belongs to.
     */
    Airline(string& name, string& callsign, string& country);

    /**
     * @brief Gets the name of the airline.
     * @details Time Complexity: O(1).
     * @return String that represents the fullname of the airline.
     */
    const string& getName() const;
    /**
     * @brief Gets the callsign of the airline.
     * @details Time Complexity: O(1).
     * @return String that represents the callsign of the airline.
     */
    const string& getCallsign() const;
    /**
     * @brief Gets the country where the airline belongs to.
     * @details Time Complexity: O(1).
     * @return String that represents the country where the airline belongs to.
     */
    const string& getCountry() const;

};


#endif //PROJ_AED2_AIRLINE_H