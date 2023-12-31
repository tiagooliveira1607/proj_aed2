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
    cout << "1. Global number of airports" << endl;
    cout << "2. Number of available flights" << endl;
    cout << "3. Number of flights going out of an airport" << endl;
    cout << "4. Number of flights per city/airline" << endl;
    cout << "=============================" << endl << endl;
}


void Menu::getUserChoice(int& choice) {
    cout << "Enter your choice: ";
    cin >> choice;
}



void Menu::processConsultationChoice(int choice) {
    switch (choice) {
        case 1:
            cout << "Number of available airports: " << Data::getNumAirports() << endl << endl;
            break;
        case 2:
            cout << "Global number of airports: " << Data::getNumFlights() << endl << endl;
            break;
        case 3:
            string airportCode;
            while (true) {
                cout << "Enter Airport Code: ";
                cin >> airportCode;

                if (Data::isValidAirportCode(airportCode)) {
                    pair<int, int> flightstats = Data::airportFlightStats(airportCode);
                    cout << "Number of flights from " << airportCode << ": " << flightstats.first << " from "
                         << flightstats.second << " different airlines" << endl;
                        return;
                } else {
                    cout << "Invalid airport code. Please enter a valid airport code." << endl << endl;
                }
            }
        

    }
}

