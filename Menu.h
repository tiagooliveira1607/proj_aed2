#ifndef PROJ_AED2_MENU_H
#define PROJ_AED2_MENU_H

#include "Graph.h"
#include "Data.h"


class Menu {
public:

    static void run();
    static void displayMainMenu();
    static void displayConsultationMenu();
    static void getUserChoice(int& choice);
    static void processConsultationChoice(int choice);
    static void displayNumOfFlightsMenu();
    static void processNumOfFlightsChoice(int choice);
    static void displayToCountriesMenu();
    static void processToCountriesChoice(int choice);
    static void displayGlobalNumMenu();
    static void processGlobalNum(int choice);


    static void displayDestOptions();
    static void processDestChoice(int choice, string airportCode);
};


#endif //PROJ_AED2_MENU_H
