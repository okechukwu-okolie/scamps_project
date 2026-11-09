#pragma once // Ensures this header file is included only once during compilation

#include "controller/ClinicManager.h" // Includes the ClinicManager controller to handle business logic and data access

namespace scapms::gui {
    // Namespace grouping the graphical user interface (GUI) components of the application
    class AppointmentPanel {
    public:
        // Renders the appointment management UI elements,
        // taking a reference to the ClinicManager to fetch, display, and modify appointment data
        static void render(controller::ClinicManager& manager);
    };
}