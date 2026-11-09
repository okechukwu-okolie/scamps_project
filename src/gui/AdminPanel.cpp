#include "gui/AdminPanel.h"
#include "controller/SearchEngine.h"
#include <iostream>

namespace scapms::gui {
    void AdminPanel::render(controller::ClinicManager& manager) {
        // ==========================================
        // 1. Display Admin Dashboard Menu Options
        // ==========================================
        std::cout << "\n--- [GUI Panel] Waiting Queue, Search, Sort & Reports ---\n";
        std::cout << "1. Add Patient to Waiting Queue\n";
        std::cout << "2. Call Next Patient from Queue\n";
        std::cout << "3. Search Patient (Linear ID / Binary Name / Recursive Name)\n";
        std::cout << "4. Sort Patients (Selection Sort / Insertion Sort)\n";
        std::cout << "5. Undo Last Admin Operation (Stack)\n";
        std::cout << "6. Generate Reports\n";
        std::cout << "7. Save / Load Data\n";
        std::cout << "8. Back to Main Menu\n";
        std::cout << "Select option: ";
        
        int choice;
        std::cin >> choice;

        // ==========================================
        // 2. Process Admin Menu Selection
        // ==========================================
        if (choice == 1) {
            // Option 1: Add a patient to the queue
            std::string id;
            std::cout << "Enter Patient ID to add to queue: ";
            std::cin >> id;
            auto p = manager.getDatabase().findPatientById(id);
            if (p) {
                manager.getDatabase().enqueuePatient(p);
                std::cout << "Patient added to waiting queue.\n";
            } else {
                std::cout << "Patient not found.\n";
            }
        } 
        else if (choice == 2) {
            // Option 2: Call/Dequeue the next patient in line
            auto p = manager.getDatabase().dequeuePatient();
            if (p) {
                std::cout << "Calling next patient: ";
                p->displayDetails();
            } else {
                std::cout << "Waiting queue is empty.\n";
            }
        } 
        else if (choice == 3) {
            // Option 3: Search Patients using various search algorithms
            std::cout << "Search Methods:\n"
                      << "1. Linear Search (by ID)\n"
                      << "2. Binary Search (by Name)\n"
                      << "3. Recursive Search (by Name)\n"
                      << "Select: ";
            int sChoice;
            std::cin >> sChoice;

            if (sChoice == 1) {
                // Linear Search by Patient ID
                std::string id;
                std::cout << "Enter ID: ";
                std::cin >> id;
                auto p = controller::SearchEngine::linearSearchById(manager.getDatabase().getPatients(), id);
                if (p) p->displayDetails(); else std::cout << "Not found.\n";
            } 
            else if (sChoice == 2) {
                // Binary Search by Patient Name (Requires pre-sorted collection)
                std::string name;
                std::cout << "Enter Exact Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                auto p = controller::SearchEngine::binarySearchByName(manager.getDatabase().getPatients(), name);
                if (p) p->displayDetails(); else std::cout << "Not found (ensure sorted by name first).\n";
            } 
            else if (sChoice == 3) {
                // Recursive Search by Patient Name
                std::string name;
                std::cout << "Enter Exact Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                auto p = controller::SearchEngine::recursiveSearchByName(manager.getDatabase().getPatients(), name);
                if (p) p->displayDetails(); else std::cout << "Not found.\n";
            }
        } 
        else if (choice == 4) {
            // Option 4: Sort Patient records using sorting algorithms and specified fields
            std::cout << "Sort Algorithms:\n"
                      << "1. Selection Sort\n"
                      << "2. Insertion Sort\n"
                      << "Select Algorithm: ";
            int algChoice;
            std::cin >> algChoice;

            std::cout << "Sort By Field:\n"
                      << "1. Name\n"
                      << "2. ID\n"
                      << "3. Age\n"
                      << "Select Field: ";
            int fieldChoice;
            std::cin >> fieldChoice;

            if (algChoice == 1) {
                // Execute Selection Sort based on user field choice
                manager.sortPatientsBySelection(fieldChoice);
                std::cout << "Sorted using Selection Sort successfully.\n";
            } 
            else if (algChoice == 2) {
                // Execute Insertion Sort based on user field choice
                manager.sortPatientsByInsertion(fieldChoice);
                std::cout << "Sorted using Insertion Sort successfully.\n";
            }
        } 
        else if (choice == 5) {
            // Option 5: Undo the last administrative operation using stack history
            manager.undoLastOperation();
        } 
        else if (choice == 6) {
            // Option 6: Generate and output comprehensive clinic reports
            manager.generateReportCategoryDistribution();
            manager.generateReportPendingAppointments();
            manager.generateReportFrequentlyAttended();
            manager.generateReportDailySummary();
        } 
        else if (choice == 7) {
            // Option 7: Persistent storage management (Save / Load data)
            std::cout << "1. Save Data\n2. Load Data\nSelect: ";
            int ioChoice;
            std::cin >> ioChoice;
            std::string filename = "clinic_data.txt";
            
            if (ioChoice == 1) {
                manager.saveData(filename);
                std::cout << "Data saved successfully to " << filename << "\n";
            } else {
                manager.loadData(filename);
                std::cout << "Data loaded successfully from " << filename << "\n";
            }
        }
    }
}