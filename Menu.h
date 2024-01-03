#ifndef PROJ_AED2_MENU_H
#define PROJ_AED2_MENU_H


#include "Data.h"


class Menu {
public:

    /**
     * @brief Starts the main menu.
     * @details Time complexity: O(1).
     */
    static void run();

    /**
     * @brief Mini menu preset used whenever the user can choose between something.
     * @details Time complexity: O(1).
     * @param choice Integer that represents the user's choice.
     */
    static void getUserChoice(int& choice);

    /**
     * @brief Mini menu preset used whenever we want to ask the user for an airport code.
     * @details Time complexity: O(1).
     * @param airportCode String representing an airport code.
     */
    static void getUserAirportCode(string& airportCode);
    /**
     * @brief Mini menu preset used whenever we want to ask the user for an airport name.
     * @details Time complexity: O(1).
     * @param airportName String representing an airport name.
     */
    static void getUserAirportName(string& airportName);

    /**
     * @brief Mini menu preset used whenever we want to ask the user for a city name.
     * @details Time complexity: O(1).
     * @param cityName String representing a city name.
     */
    static void getUserCityName(string& cityName);

    /**
     * @details Mini menu preset used whenever we want to ask the user for coordinates.
     * @details Time complexity: O(1).
     * @param lat Integer representing the latitude.
     * @param lon Integer representing the longitude.
     */
    static void getUserCoordinates(double& lat, double& lon);

    /**
     * @brief Main menu
     * @details Time complexity: O(1).
     */
    static void displayMainMenu();

    /**
     * @brief Consultation menu.
     * @details Time complexity: O(1).
     */
    static void displayConsultationMenu();

    /**
     * @brief Best flight option menu.
     * @details Time complexity: O(1).
     */
    static void displayFlightOptionMenu();

    /**
     * @brief Mini menu preset used to ask the user about the number of flights of something.
     * @details Time complexity: O(1).
     */
    static void displayNumOfFlightsMenu();

    /**
     * @brief Mini menu preset to ask "Number of different countries a" to the user.
     * @details Time complexity: O(1).
     */
    static void displayToCountriesMenu();

    /**
     * @brief Mini menu preset to ask the global number of something to the user.
     * @details Time complexity: O(1).
     */
    static void displayGlobalNumMenu();

    /**
     * @brief Mini menu preset to ask what kind of destination the user wants.
     * @details Time complexity: O(1).
     */
    static void displayDestOptions();

    /**
     * @brief Menu part that let's the user choose what kind of consultation he wants to do.
     * @details Time complexity: O(1).
     * @param choice Integer to handle the user's choice.
     */
    static void processConsultationChoice(int choice);

    /**
     * @brief Menu part that let's the user choose what kind of best flight option he wants.
     * @details Time complexity: O(1).
     * @param choice Integer to handle the user's choice.
     */
    static void processFlightOptionChoice(int choice);

    /**
     * @brief Mini menu preset to either get the number of flights per city or airline.
     * @details Time complexity: O(1).
     * @param choice Integer to handle the user's choice.
     */
    static void processNumOfFlightsChoice(int choice);

    /**
     * @details Print preset.
     * @details Time complexity: O(1).
     * @param choice Intenger to handle the user's choice.
     */
    static void processToCountriesChoice(int choice);

    /**
     * @brief Preset to ask the user the global number of something.
     * @details Time complexity: O(1).
     * @param choice Integer to handle the user's choice.
     */
    static void processGlobalNum(int choice);

    /**
     * @details Print preset.
     * @details Time complexity: O(1).
     * @param choice Integer to handle the user's choice.
     * @param airportCode String that represents the airport code.
     */
    static void processDestChoice(int choice, const string& airportCode);

    /**
     * @details Print preset.
     * @details Time complexity: O(1).
     * @param choice Integer to handle the user's choice.
     * @param airportCode String that represents the airport code.
     * @param x Integer to represent a limit.
     */
    static void processDestChoice(int choice, const string& airportCode, int x);
};


#endif //PROJ_AED2_MENU_H
