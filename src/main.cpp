/**
 * @file main.cpp
 * @brief Application entry point for the Smart Clinic Appointment & Patient Management System (SCAPMS).
 */

#include "gui/MainWindow.h"
#include <iostream>

int main() {
    try {
        // Initialize the main application window and start the GUI event loop
        scapms::gui::MainWindow mainWindow;
        mainWindow.run();
        
    } catch (const std::exception& e) {
        // Catch and log standard runtime or logic errors to standard error
        std::cerr << "Fatal Exception: " << e.what() << "\n";
        return 1;
        
    } catch (...) {
        // Catch any unhandled, non-standard exceptions to prevent abrupt crashes
        std::cerr << "Unknown fatal exception occurred.\n";
        return 1;
    }
    
    // Return a success exit code upon normal application termination
    return 0;
}