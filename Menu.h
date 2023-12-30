#ifndef PROJ_AED2_MENU_H
#define PROJ_AED2_MENU_H

#include <iostream>
#include "Graph.h"
#include "Data.h"


class Menu {
public:
    Menu();

    static void display();
    static void displayMainMenu();
    static void displayConsultationMenu();
    static void getUserChoice(int& choice);
    static void processConsultationChoice(int choice);
};


#endif //PROJ_AED2_MENU_H
