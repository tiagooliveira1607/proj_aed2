#ifndef PROJ_AED2_MENU_H
#define PROJ_AED2_MENU_H

#include <iostream>
#include "Graph.h"
#include "Data.h"


class Menu {
public:
    Menu();

    void display();
    void displayMainMenu();
    void displayConsultationMenu();
    void getUserChoice(int choice);
    void processConsultationChoice(int choice);
};


#endif //PROJ_AED2_MENU_H
