#include "gui/MainWindow.h"
#include "gui/PatientPanel.h"
#include "gui/AppointmentPanel.h"
#include "gui/AdminPanel.h"
#include <iostream>

namespace scapms::gui {

    // Default constructor for the MainWindow class
    MainWindow::MainWindow() {}

    // Main execution loop that controls the console interface, user input, and navigation
    void MainWindow::run() {
        int choice = 0;
        
        // Core application loop: keeps running until the user selects option 4 to exit
        do {
            // Display the main navigation menu banner
            std::cout << "\n=========================================\n";
            std::cout << "  Smart Clinic Appointment & Patient Mgmt  \n";
            std::cout << "             (SCAPMS) GUI              \n";
            std::cout << "=========================================\n";
            std::cout << "1. Patient Records Management (Panel)\n";
            std::cout << "2. Appointment Management (Panel)\n";
            std::cout << "3. Waiting Queue, Search, Sort & Reports (Panel)\n";
            std::cout << "4. Exit Application\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            // Switch statement to route the user selection to the appropriate subsystem panel
            switch (choice) {
                case 1:
                    // Delegate control to the Patient Records Management panel
                    PatientPanel::render(manager);
                    break;
                case 2:
                    // Delegate control to the Appointment Management panel
                    AppointmentPanel::render(manager);
                    break;
                case 3:
                    // Delegate control to the Admin / Waiting Queue, Search, Sort & Reports panel
                    AdminPanel::render(manager);
                    break;
                case 4:
                    // Exit notification message
                    std::cout << "Exiting application. Thank you!\n";
                    break;
                default:
                    // Handle invalid inputs gracefully and prompt the user again
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }
}