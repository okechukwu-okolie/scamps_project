#pragma once // Ensures this header file is included only once during compilation
#include "controller/ClinicManager.h" // Includes the backend controller responsible for clinic business logic

namespace scapms::gui { // Groups GUI-related classes under the scapms project namespace to avoid naming conflicts
    class MainWindow {
    private:
        controller::ClinicManager manager; // Instance of the clinic manager handling core operations and data

    public:
        MainWindow(); // Constructor responsible for initializing the main window and its UI components
        void run();   // Method to start the main application execution loop or display the window
    };
}