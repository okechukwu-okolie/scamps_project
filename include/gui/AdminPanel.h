#pragma once // Ensures this header file is included only once during compilation to prevent redefinition errors

#include "controller/ClinicManager.h" // Includes the ClinicManager controller dependency for handling clinic business logic and data

namespace scapms::gui {
    // Namespace enclosing the Graphical User Interface (GUI) components of the SCAPMS application
    class AdminPanel {
    public:
        // Renders the administrative dashboard/panel UI elements, 
        // interacting with the provided ClinicManager instance to display and manage system data
        static void render(controller::ClinicManager& manager);
    };
}