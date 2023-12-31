#include "Menu.h"

using namespace std;


void Menu::run() {
    int choice = 0;
    while (choice != 3) {
        displayMainMenu();
        getUserChoice(choice);

        switch (choice) {
            case 1:
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
                            cout << "Returning to Main Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid option." << endl;
                            break;
                    }
                } while (consultationChoice != 4);

                break;

            case 2:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    }

}


void Menu::displayMainMenu() {
    cout << "===== Main Menu =====" << endl;
    cout << "1. Consultation" << endl;
    cout << "2. Exit" << endl;
    cout << "=====================" << endl << endl;
}

void Menu::displayConsultationMenu() {
    cout << "===== Consultation Menu =====" << endl;
    cout << "1. Global number of airports/flights" << endl;
    cout << "3. Number of flights going out of an airport" << endl;
    cout << "4. Number of flights per city/airline" << endl;
    cout << "5. Number of different countries that a given Airport/City flies to." << endl;
    cout << "6. Number of destinations of an Airport." << endl;
    cout << "7. Number of reachable destinations from a given airport in a maximum number of X stops" << endl;
    cout << "=============================" << endl << endl;
}


void Menu::getUserChoice(int& choice) {
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl << endl;
}



void Menu::processConsultationChoice(int choice) {
    switch (choice) {
        case 1:
            int globalChoice;
            displayGlobalNumMenu();
            getUserChoice(globalChoice);
            processGlobalNum(globalChoice);

            break;
        case 2: {
            string airportCode;
            while (true) {
                cout << "Enter Airport Code: ";
                cin >> airportCode;
                pair<int, int> flightstats = Data::airportFlightStats(airportCode);
                if (flightstats.first != 0 && flightstats.second != 0) {
                    cout << "Number of flights from " << airportCode << ": " << flightstats.first << " from "
                    << flightstats.second << " different airlines" << endl;
                    return;
                } else {
                    cout << "Invalid airport code. Please enter a valid airport code." << endl << endl;
                }
            }
        }
        case 3:
            int numOfFlightsChoice;
            do {
                displayNumOfFlightsMenu();
                getUserChoice(numOfFlightsChoice);
                processNumOfFlightsChoice(numOfFlightsChoice);
            } while(numOfFlightsChoice != 3);
            break;

        case 4: {
            int countriesChoice;
            do {
                displayToCountriesMenu();
                getUserChoice(countriesChoice);
                processToCountriesChoice(countriesChoice);
            } while (countriesChoice != 3);
            break; }

        case 5: {
            string airportCode;
            cout << endl << "Enter Airport code: ";
            cin >> airportCode;
            cout << endl;
            int destChoice;
            displayDestOptions();
            getUserChoice(destChoice);
            processDestChoice(destChoice, airportCode);

            break;
        }

        default:
            cout << "Invalid choice. Please Enter a valid choice." << endl;
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
            cout << "Global number of Airports: " << Data::getNumAirports() << endl << endl;
            break;

        case 2:
            cout << "Global number of Flights: " << Data::getNumFlights() << endl << endl;
            break;
        case 3:
            return;
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
            return;
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
            string codeOfAirport;
            cout << "Enter the code of the Airport: ";
            cin >> codeOfAirport;
            cout << "============================" << endl;
            cout << endl << endl << "Number of countries "<< codeOfAirport << " flies to: " <<
            Data::getNumCountriesFlyingToAirport(codeOfAirport) << endl << endl;
            cout << "============================" << endl;
            break; }
        case 2: {
            string city;
            cout << "Enter the city name: ";
            cin >> city;
            cout << "============================" << endl;
            cout << endl << endl << "Number of countries " << city << " flies to: " <<
                 Data::getNumCountriesFlyingToCity(city) << endl << endl;
            cout << "============================" << endl;
            break;}
        case 3:
            return;
    }
}

void Menu::displayDestOptions() {
    cout << "============================" << endl;
    cout << "1. Airports" << endl;
    cout << "2. Cities" << endl;
    cout << "3. Countries" << endl;
    cout << "=============================" << endl << endl;
}

void Menu::processDestChoice(int choice, string airportCode) {
    switch (choice) {
        case 1:
            cout << "Number of airports available for " << airportCode << ": " << Data::getNumAirportsFromAirport(airportCode) << endl << endl;
            break;

        case 2:
            cout << "Number of cities available for " << airportCode << ": " << Data::getNumCitiesFromAirport(airportCode) << endl << endl;
            break;

        case 3:
            cout << "Number of countries available for " << airportCode << ": " << Data::getNumCountriesFromAirport(airportCode) << endl << endl;
            break;
    }
}

