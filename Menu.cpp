#include "Menu.h"

using namespace std;

Menu::Menu() {display();}

void Menu::displayMainMenu() {
    cout << "===== Main Menu =====" << endl;
    cout << "1. Consultation" << endl;
    cout << "2. Exit" << endl;
    cout << "=====================" << endl;
}

void Menu::displayConsultationMenu() {
    cout << "===== Consultation Menu =====" << endl;
    cout << "1. Global number of airports" << endl;
    cout << "2. Number of available flights" << endl;
    cout << "3. Back to Main Menu" << endl;
    cout << "=============================" << endl;
}

void Menu::display() {
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
                            cout << "Global number of airports: "; processConsultationChoice(1);
                            break;
                        case 2:
                            cout << "Number of available flights: "; processConsultationChoice(2);
                            break;
                        case 3:
                            cout << "Returning to Main Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid option." << endl;
                            break;
                    }
                } while (consultationChoice != 3);

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

void Menu::getUserChoice(int& choice) {
    cout << "Enter your choice: ";
    cin >> choice;
}



void Menu::processConsultationChoice(int choice) {
    switch (choice) {
        case 1:
            cout << Data::getNumAirports() << endl;
            break;
        case 2:
            cout << Data::getNumFlights() << endl;
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
    }
}
