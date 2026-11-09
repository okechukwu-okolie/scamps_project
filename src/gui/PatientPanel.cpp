#include "gui/PatientPanel.h"
#include "utils/IDGenerator.h"
#include "utils/Exceptions.h"
#include <iostream>

namespace scapms::gui {
    void PatientPanel::render(controller::ClinicManager& manager) {
        // Display the Patient Records Management interactive menu
        std::cout << "\n--- [GUI Panel] Patient Records Management ---\n";
        std::cout << "1. View All Patients\n";
        std::cout << "2. Register New Patient\n";
        std::cout << "3. Delete Patient\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Select option: ";
        
        int choice;
        std::cin >> choice;

        // Option 1: Retrieve and display all registered patients from the database
        if (choice == 1) {
            std::cout << "\nRegistered Patients:\n";
            for (auto p : manager.getDatabase().getPatients()) {
                p->displayDetails();
            }
        } 
        // Option 2: Register a new patient with type-specific details and error validation
        else if (choice == 2) {
            try {
                std::string type, name, contact, extra;
                int age;
                
                // Prompt for patient category and automatically generate a unique ID
                std::cout << "Enter Type (General / Emergency / FollowUp): ";
                std::cin >> type;
                std::string id = utils::IDGenerator::generatePatientId();
                std::cout << "Generated Patient ID: " << id << "\n";
                
                // Collect core demographic details
                std::cout << "Enter Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter Age: ";
                std::cin >> age;
                std::cout << "Enter Contact Info: ";
                std::cin >> contact;
                
                // Handle polymorphic/extended attributes based on patient type
                if (type == "Emergency") {
                    std::cout << "Enter Triage Level (Low/Medium/High): ";
                    std::cin >> extra;
                } else if (type == "FollowUp") {
                    std::cout << "Enter Previous Visit Count: ";
                    std::cin >> extra;
                }
                
                // Pass collected data to the controller manager
                manager.registerPatient(type, id, name, age, contact, extra);
                std::cout << "Success: Patient registered successfully!\n";
            } catch (const std::exception& e) {
                // Catch and display validation or registration exceptions
                std::cout << "[Validation Error] " << e.what() << "\n";
            }
        } 
        // Option 3: Delete an existing patient record by ID
        else if (choice == 3) {
            try {
                std::string id;
                std::cout << "Enter Patient ID to delete: ";
                std::cin >> id;
                
                manager.deletePatient(id);
                std::cout << "Success: Patient deleted successfully!\n";
            } catch (const std::exception& e) {
                // Catch and display exceptions if deletion fails (e.g., ID not found)
                std::cout << "[Exception] " << e.what() << "\n";
            }
        }
        // Option 4 (or any other input): Falls through and returns to the parent menu loop
    }
}