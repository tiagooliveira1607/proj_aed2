#ifndef PROJ_AED2_MENU_H
#define PROJ_AED2_MENU_H


#include "Data.h"


class Menu {
public:

    static void run();
    static void getUserChoice(int& choice);
    static void getUserAirportCode(string& airportCode);
    static void displayMainMenu();
    static void displayConsultationMenu();
    static void displayFlightOptionMenu();
    static void displayNumOfFlightsMenu();
    static void displayToCountriesMenu();
    static void displayGlobalNumMenu();
    static void displayDestOptions();
    static void processConsultationChoice(int choice);
    static void processFlightOptionChoice(int choice);
    static void processNumOfFlightsChoice(int choice);
    static void processToCountriesChoice(int choice);
    static void processGlobalNum(int choice);


    static void processDestChoice(int choice, string airportCode);
    static void processDestChoice(int choice, const string& airportCode, int x);
};


#endif //PROJ_AED2_MENU_H
