#pragma once // Ensures this header file is included only once during a single compilation

#include "controller/ClinicManager.h" // Includes the controller dependency responsible for clinic business logic and data management

namespace scapms::gui {
    // Represents the user interface panel dedicated to patient management and visualization
    class PatientPanel {
    public:
        // Renders the patient panel UI components, passing the ClinicManager reference to handle data operations
        static void render(controller::ClinicManager& manager);
    };
}