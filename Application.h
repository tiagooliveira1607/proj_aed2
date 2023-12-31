#ifndef PROJ_AED2_APPLICATION_H
#define PROJ_AED2_APPLICATION_H

#include <iostream>
#include "Menu.h"
#include "Data.h"

class Application {

    static Data data;
    static Menu menu;

public:

    void static run();

};


#endif //PROJ_AED2_APPLICATION_H
