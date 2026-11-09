#pragma once // Ensures this header file is included only once during compilation
#include "controller/ClinicManager.h" // Includes the backend controller responsible for clinic business logic

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <vector>

namespace scapms::gui { // Groups GUI-related classes under the scapms project namespace to avoid naming conflicts
    class MainWindow {
    private:
        enum class Page {
            Home,
            Patients,
            Appointments,
            Administration
        };

        HWND window;
        HWND output;
        controller::ClinicManager manager; // Instance of the clinic manager handling core operations and data
        Page page;
        std::vector<HWND> controls;

        static LRESULT CALLBACK windowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
        HWND addControl(const char* type, const char* text, DWORD style, int x, int y, int width, int height, int id);
        void clearControls();
        void render();
        void renderPatients();
        void renderAppointments();
        void renderAdministration();
        void createOutput(int x, int y, int width, int height);
        void handleCommand(int commandId);
        std::string getText(int id) const;
        void setOutput(const std::string& text);
        std::string patientList();
        std::string appointmentList();
        std::string dashboardText();
        std::string reportText();

    public:
        MainWindow(); // Constructor responsible for initializing the main window and its UI components
        void run();   // Method to start the main application execution loop or display the window
    };
}