/**
 * @file main.cpp
 * @brief Application entry point for the Smart Clinic Appointment & Patient Management System (SCAPMS).
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "gui/MainWindow.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    try {
        scapms::gui::MainWindow mainWindow;
        mainWindow.run();
    } catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "SCAPMS - Fatal Error", MB_OK | MB_ICONERROR);
        return 1;
    } catch (...) {
        MessageBoxA(nullptr, "An unknown fatal error occurred.", "SCAPMS - Fatal Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    return 0;
}