#ifndef PROJ_AED2_APPLICATION_H
#define PROJ_AED2_APPLICATION_H

#include <iostream>
#include "Menu.h"
#include "Data.h"

class Application {

    static Data data;
    static Menu menu;

public:

    /**
     * @brief Reads the csv files and initializes the menu.
     * @details Time complexity: O(1).
     */
    void static run();

};


#endif //PROJ_AED2_APPLICATION_H
