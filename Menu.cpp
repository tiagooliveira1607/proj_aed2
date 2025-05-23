#include "Menu.h"

using namespace std;


void Menu::getUserChoice(int& choice) {
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl << endl;
}
void Menu::getUserAirportCode(string& airportCode) {
    bool validAirport = false;

    while (!validAirport) {
        cout << "Enter Airport Code: ";
        cin >> airportCode;
        cout << endl << endl;

        validAirport = Data::isValidAirportCode(airportCode);

        if (!validAirport) {
            cout << "Invalid Airport Code. Reenter an Airport Code that exists." << endl;
        }
    }
}

void Menu::getUserCityName(string &cityName) {
    bool validCity = false;

    while (!validCity) {
        cout << "Enter City Name: ";
        cin >> cityName;
        cout << endl << endl;

        validCity = Data::isValidCityName(cityName);

        if (!validCity) {
            cout << "Invalid City Name. Reenter a City Name that exists." << endl;
        }
    }
}

void Menu::getUserAirportName(string &airportName) {
    bool validAirportName = false;

    while (!validAirportName) {
        cout << "Enter Airport Name: ";
        cin >> airportName;
        cout << endl << endl;

        validAirportName = Data::isValidAirportName(airportName);

        if (!validAirportName) {
            cout << "Invalid Airport Name. Reenter an Airport Name that exists." << endl;
        }
    }
}


void Menu::getUserCoordinates(double& lat, double& lon) {
    cout << "Enter latitude: ";
    cin >> lat;
    cout << endl << "Enter longitude: ";
    cin >> lon;
    cout << endl << endl;
}



void Menu::run() {
    int choice = 0;
    while (choice != 3) {
        displayMainMenu();
        getUserChoice(choice);

        switch (choice) {
            case 1: {
                // Consultation Menu
                int consultationChoice;
                do {
                    displayConsultationMenu();
                    getUserChoice(consultationChoice);

                    switch (consultationChoice) {
                        case 1:
                            processConsultationChoice(1);
                            break;
                        case 2:
                            processConsultationChoice(2);
                            break;
                        case 3:
                            processConsultationChoice(3);
                            break;
                        case 4:
                            processConsultationChoice(4);
                            break;
                        case 5:
                            processConsultationChoice(5);
                            break;
                        case 6:
                            processConsultationChoice(6);
                            break;
                        case 7:
                            processConsultationChoice(7);
                            break;
                        case 8:
                            processConsultationChoice(8);
                            break;
                        case 9:
                            processConsultationChoice(9);
                            break;
                        case 10:
                            cout << "Returning to Main Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid option." << endl;
                            break;
                    }

                    if (consultationChoice != 10) {
                    cout << "Press Enter to Consultation Menu...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();}
                } while (consultationChoice != 10);

                break;}

            case 2: {
                int flightOptionChoice;
                do {
                    displayFlightOptionMenu();
                    getUserChoice(flightOptionChoice);

                    switch (flightOptionChoice) {
                        case 1:
                            processFlightOptionChoice(1);
                            break;

                        case 2:
                            processFlightOptionChoice(2);
                            break;

                        case 3:
                            processFlightOptionChoice(3);
                            break;


                        case 4:
                            break;

                        default:
                            cout << "Invalid choice. Please enter a valid option" << endl;
                            break;
                    }
                } while (flightOptionChoice != 4);

            }

            case 3:{
                break;}

            default:{
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;}
        }
    }

}


void Menu::displayMainMenu() {
    cout << "===== Main Menu =====" << endl;
    cout << "1. Consultation" << endl;
    cout << "2. Best Flight suggestion" << endl;
    cout << "3. Exit" << endl;
    cout << "=====================" << endl << endl;
}

void Menu::displayConsultationMenu() {
    cout << "========== Consultation Menu ==========" << endl;
    cout << "1. Global number of airports/flights" << endl;
    cout << "2. Number of flights going out of an airport" << endl;
    cout << "3. Number of flights per city/airline" << endl;
    cout << "4. Number of different countries that a given Airport/City flies to." << endl;
    cout << "5. Number of destinations of an Airport." << endl;
    cout << "6. Number of reachable destinations from a given airport in a maximum number of X stops" << endl;
    cout << "7. Pair(s) of source and destination Airport(s) that represent the longest trips possible." << endl;
    cout << "8. Top k Airports with the greatest air traffic capacity" << endl;
    cout << "9. Essential Airports" << endl;
    cout << "10. Return" << endl;
    cout << "========================================" << endl << endl;
}


void Menu::processConsultationChoice(int choice) {
    switch (choice) {
        case 1: {
            int globalChoice;
            do {
                displayGlobalNumMenu();
                getUserChoice(globalChoice);
                processGlobalNum(globalChoice);
            } while (globalChoice != 3 && globalChoice != 2 && globalChoice != 1);
            break;}

        case 2: {
            string airportCode;
            while (true) {
                getUserAirportCode(airportCode);
                pair<int, int> flightstats = Data::airportFlightStats(airportCode);
                if (flightstats.first != 0 && flightstats.second != 0) {
                    cout << "================================" << endl;
                    cout << "Number of flights from " << airportCode << ": " << flightstats.first << " from "
                    << flightstats.second << " different airlines" << endl;
                    cout << "================================" << endl << endl;
                    break;
                } else {
                    cout << "Invalid airport code. Please enter a valid airport code." << endl << endl;
                }
            }
            break;
        }
        case 3: {
            int numOfFlightsChoice;
            do {
                displayNumOfFlightsMenu();
                getUserChoice(numOfFlightsChoice);
                processNumOfFlightsChoice(numOfFlightsChoice);
            } while(numOfFlightsChoice != 3 && numOfFlightsChoice != 2 && numOfFlightsChoice != 1);
            break;}

        case 4: {
            int countriesChoice;
            do {
                displayToCountriesMenu();
                getUserChoice(countriesChoice);
                processToCountriesChoice(countriesChoice);
            } while (countriesChoice != 3 && countriesChoice != 2 && countriesChoice != 1);
            break; }

        case 5: {
            string airportCode;
            getUserAirportCode(airportCode);
            int destChoice;
            displayDestOptions();
            getUserChoice(destChoice);
            processDestChoice(destChoice, airportCode);
            break;}

        case 6: {
            string airportCode;
            int x;
            getUserAirportCode(airportCode);
            cout << endl << "Enter the maximum number of layouts(stops): ";
            cin >> x;
            cout << endl << endl;
            int destChoice;
            displayDestOptions();
            getUserChoice(destChoice);
            processDestChoice(destChoice,airportCode, x);
            break;
        }
        case 7: {
            cout << "=========================================" << endl;
            for (pair<Airport *, Airport *> pair: Data::longestTrips()) {
                cout << "<  " << pair.first->getAirportInfo().getName() << "  --->  "
                     << pair.second->getAirportInfo().getName() << "  >" << endl;
            }
            cout << "=========================================" << endl << endl;
            break;
        }

        case 8: {
            int k;
            cout << "Enter k: ";
            cin >> k;
            cout << endl << endl;
            cout << "Top " << k << " Airports:" << endl;
            for (Airport* airport : Data::topAirportsByFlights(k)) {
                cout << "- " << airport->getAirportInfo().getName() << endl;
            }
            cout << endl << endl;
            break;
        }
        case 9: {
            for (Airport* airport : Data::essentialAirports()) {
                cout << "- " << airport->getAirportInfo().getName() << endl;
            }
            break;
        }
        case 10:
            return;

        default:
            cout << "Invalid choice. Please Enter a valid option." << endl;
    }

}


void Menu::displayGlobalNumMenu() {
    cout << "===== Global number of =====" << endl;
    cout << "1. Airports " << endl;
    cout << "2. Flights" << endl;
    cout << "3. Return" << endl;
    cout << "============================" << endl << endl;
}

void Menu::processGlobalNum(int choice) {
    switch (choice) {
        case 1:
            cout << "================================" << endl;
            cout << "Global number of Airports: " << Data::getNumAirports() << endl;
            cout << "================================" << endl << endl;
            break;

        case 2:
            cout << "================================" << endl;
            cout << "Global number of Flights: " << Data::getNumFlights() << endl;
            cout << "================================" << endl << endl;
            break;

        case 3:
            break;

        default:
            cout << "Invalid choice. Please Enter a valid option." << endl;
            break;
    }
}

void Menu::displayNumOfFlightsMenu() {
    cout << "===== Number of Flights =====" << endl;
    cout << "1. per City" << endl;
    cout << "2. per Airline" << endl;
    cout << "3. Return" << endl;
    cout << "=============================" << endl << endl;
}

void Menu::processNumOfFlightsChoice(int choice) {
    switch (choice) {
        case 1:
            cout << "============================" << endl;
            cout << "Number of flights per city:" << endl;
            cout << "============================" << endl << endl;
            for (const pair<const string, int>& pair : Data::getNumFlightsPerCity()) {
                cout << pair.first << ": " << pair.second << endl << endl;
            }
            break;

        case 2:
            cout << "==============================" << endl;
            cout << "Number of flights per Airline:" << endl;
            cout << "==============================" << endl << endl;
            for (const pair<const string, int>& pair : Data::getNumFlightsPerAirline()) {
                cout << pair.first << ": " << pair.second << endl;
            }
            break;
        case 3:
            break;

        default:
            cout << "Invalid choice. Please Enter a valid option." << endl;
            break;
    }
}

void Menu::displayToCountriesMenu() {
    cout << "===== Number of different countries a =====" << endl;
    cout << "1. Airport flies to" << endl;
    cout << "2. City flies to" << endl;
    cout << "3. Return" << endl;
    cout << "=============================" << endl << endl;

}

void Menu::processToCountriesChoice(int choice) {
    switch (choice) {
        case 1: {
            string airportCode;
            getUserAirportCode(airportCode);
            cout << "====================================" << endl;
            cout << "Number of countries "<< Data::getAirportNameByCode(airportCode) << " flies to: " <<
            Data::getNumCountriesFlyingToAirport(airportCode) << endl;
            cout << "====================================" << endl << endl;
            break; }
        case 2: {
            string cityName;
            getUserCityName(cityName);
            cout << "====================================" << endl;

            cout << "Number of countries " << cityName << " flies to: " <<
                 Data::getNumCountriesFlyingToCity(cityName) << endl;
            cout << "====================================" << endl << endl;
            break;}
        case 3:
            return;

        default:
            cout << "Invalid choice. Please Enter a valid option." << endl;
    }
}

void Menu::displayDestOptions() {
    cout << "============================" << endl;
    cout << "1. Airports" << endl;
    cout << "2. Cities" << endl;
    cout << "3. Countries" << endl;
    cout << "=============================" << endl << endl;
}

void Menu::processDestChoice(int choice, const string& airportCode) {
    switch (choice) {
        case 1:
            cout << "=========================================" << endl;
            cout << "Number of airports available for " << Data::getAirportNameByCode(airportCode) << ": " << Data::getNumDestFromSource(airportCode, choice) << endl;
            cout << "=========================================" << endl << endl;
            break;

        case 2:
            cout << "=========================================" << endl;
            cout << "Number of cities available for " << Data::getAirportNameByCode(airportCode) << ": " << Data::getNumDestFromSource(airportCode, choice) << endl;
            cout << "=========================================" << endl << endl;
            break;

        case 3:
            cout << "=========================================" << endl;
            cout << "Number of countries available for " << Data::getAirportNameByCode(airportCode) << ": " << Data::getNumDestFromSource(airportCode, choice) << endl;
            cout << "=========================================" << endl << endl;
            break;

        default:
            cout << "Invalid choice. Please Enter a valid option." << endl;
    }
}

void Menu::processDestChoice(int choice,const string& airportCode, int x) {
switch (choice) {
    case 1:
        cout << "=========================================" << endl;
        cout << "Number of airports available for " << airportCode << " in a maximum of " << x <<
        " stops: "<< Data::numReachableDestinations(airportCode,x,1) << endl;
        cout << "=========================================" << endl << endl;
        break;

    case 2:
        cout << "=========================================" << endl;
        cout << "Number of cities available for " << airportCode << " in a maximum of " << x <<
        " stops: " << Data::numReachableDestinations(airportCode, x, 2) << endl;
        cout << "=========================================" << endl << endl;
        break;

    case 3:
        cout << "=========================================" << endl;
        cout << "Number of countries available for " << airportCode << "ina a maximum of " << x <<
        " stops: " << Data::numReachableDestinations(airportCode, x, 3) << endl;
        cout << "=========================================" << endl << endl;
        break;

    default:
        cout << "Invalid choice. Please Enter a valid option." << endl;
    }
}

void Menu::displayFlightOptionMenu() {
    cout << "============================" << endl;
    cout << "1. By Airport Code or Name" << endl;
    cout << "2. By City" << endl;
    cout << "3. By Geographical Coordinates (closest Airport)" << endl;
    cout << "4. Return" << endl;
    cout << "=============================" << endl << endl;
}

void Menu::processFlightOptionChoice(int choice) {
    switch (choice) {
        case 1: {
            int choice1;
            do {
                cout << "============================" << endl;
                cout << "1. By Airport Code" << endl;
                cout << "2. By Airport Name" << endl;
                cout << "3. Return" << endl;
                cout << "=============================" << endl << endl;
                getUserChoice(choice1);

                switch (choice1) {
                    case 1: {
                        string airportSourceCode;
                        string airportDestCode;

                        cout << "Source" << endl;
                        getUserAirportCode(airportSourceCode);
                        cout << "Destination" << endl;
                        getUserAirportCode(airportDestCode);

                        cout << "This is the path you should follow in order to reach your destination!" << endl << endl;
                        vector<Flight *> bestFlightOption = Data::getBestFlightOption_AirportCode(airportSourceCode,airportDestCode);

                        cout << "<" << Data::getAirportNameByCode(airportSourceCode);
                        for (Flight *flight: bestFlightOption) {
                            cout << " using " << Data::getAirlineNameByCode(flight->getAirlineCode()) << " to " <<
                                 Data::getAirportNameByCode(flight->getDest()->getAirportInfo().getCode());
                        }
                        cout << " >" << endl << endl;

                        break;
                    }


                    case 2: {
                        string airportSourceName;
                        string airportDestName;

                        cout << "Source" << endl;
                        getUserAirportName(airportSourceName);
                        cout << "Destination" << endl;
                        getUserAirportName(airportDestName);

                        vector<Flight *> bestFlightOption = Data::getBestFlightOption_AirportName(airportSourceName,
                                                                                                  airportDestName);
                        cout << "<   " << airportSourceName;
                        for (Flight *flight: bestFlightOption) {
                            cout << " using " << Data::getAirlineNameByCode(flight->getAirlineCode()) << " to " <<
                                 airportDestName << " ";
                        }
                        cout << "   >" << endl << endl;
                        break;
                    }
                    case 3:
                        break;
                    default:
                        cout << "Invalid choice. Please Enter a valid option." << endl;
                        break;
                }

            } while (choice1 != 3 && choice1 != 2 && choice1 != 1);
            break;
        }

        case 2: {
            string citySourceName;
            string cityDestName;

            cout << "Source" << endl;
            getUserCityName(citySourceName);
            cout << "Destination" << endl;
            getUserCityName(cityDestName);

            vector<vector<Flight*>> bestFlightOption = Data::getBestFlightOption_CityName(citySourceName, cityDestName);

            for (const auto& flightSet : bestFlightOption) {
                cout << "<   " << citySourceName;
                for (Flight* flight : flightSet) {
                    cout << " using " << Data::getAirlineNameByCode(flight->getAirlineCode()) << " to " <<
                    cityDestName << " ";
                }
                cout << "   >" <<  endl;
            }
            break;

        }

        case 3: {
            double sourceLat, sourceLon;
            cout << "Source" << endl;
            getUserCoordinates(sourceLat,sourceLon);

            auto bestFlightOption = Data::getBestFlightOptionToClosestAirports(sourceLat,sourceLon);


            for (auto pair : bestFlightOption) {
                cout << pair.first->getAirportInfo().getName() << ": " << Data::getAirportByCoordinates(sourceLat,sourceLon)->getAirportInfo().getName();
                for (Flight* flight : pair.second) {
                    cout << " using " << Data::getAirlineNameByCode(flight->getAirlineCode()) << " to " << flight->getDest()->getAirportInfo().getName();
                }
                cout << endl;
            }
            break;
        }

        case 4:
            break;

        default:
            cout << "Invalid choice. Please Enter a valid option." << endl;
            break;
    }
}
