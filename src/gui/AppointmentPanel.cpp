#include "gui/AppointmentPanel.h"
#include <iostream>

namespace scapms::gui {
    void AppointmentPanel::render(controller::ClinicManager& manager) {
        // Render the Appointment Management menu and capture the user's menu selection
        std::cout << "\n--- [GUI Panel] Appointment Management ---\n";
        std::cout << "1. Schedule Appointment\n";
        std::cout << "2. Cancel Appointment\n";
        std::cout << "3. View Appointments\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Select option: ";
        int choice;
        std::cin >> choice;

        // Option 1: Collect appointment details and delegate scheduling to the ClinicManager
        if (choice == 1) {
            try {
                std::string pId, date, time;
                std::cout << "Enter Patient ID: ";
                std::cin >> pId;
                std::cout << "Enter Appointment Date (YYYY-MM-DD): ";
                std::cin >> date;
                std::cout << "Enter Appointment Time (HH:MM): ";
                std::cin >> time;
                
                // Trigger the controller method to schedule the appointment
                manager.scheduleAppointment(pId, date, time);
                std::cout << "Success: Appointment scheduled successfully!\n";
            } catch (const std::exception& e) {
                // Catch and gracefully display any runtime exceptions (e.g., validation failures or invalid IDs)
                std::cout << "[Exception] " << e.what() << "\n";
            }
        } 
        // Option 2: Collect patient identifier and process appointment cancellation
        else if (choice == 2) {
            std::string pId;
            std::cout << "Enter Patient ID to cancel appointment: ";
            std::cin >> pId;
            
            // Delegate cancellation handling to the manager
            manager.cancelAppointment(pId);
            std::cout << "Success: Appointment cancelled!\n";
        } 
        // Option 3: Retrieve and display all currently scheduled appointments from the database
        else if (choice == 3) {
            std::cout << "\nScheduled Appointments:\n";
            for (auto& appt : manager.getDatabase().getAppointments()) {
                appt.display();
            }
        }
    }
}