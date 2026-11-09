#include "model/GeneralPatient.h"
#include <iostream>

namespace scapms::model {

    // Constructor: Initializes the GeneralPatient by delegating to the base PatientRecord 
    // and setting default appointment values (no appointment scheduled yet).
    GeneralPatient::GeneralPatient(const std::string& id, const std::string& n, int a, const std::string& contact)
        : PatientRecord(id, n, a, contact), appointmentDate("None"), hasAppointment(false) {}

    // Returns the specific patient type identifier as a string.
    std::string GeneralPatient::getPatientType() const { return "General"; }

    // Outputs the general patient's complete information (ID, name, age, contact, and appointment status) to the console.
    void GeneralPatient::displayDetails() const {
        std::cout << "[General Patient] ID: " << patientId << ", Name: " << name 
                  << ", Age: " << age << ", Contact: " << contactInfo 
                  << ", Appointment: " << appointmentDate << "\n";
    }

    // Combines the provided date and time strings into a single appointment timestamp and marks the appointment as active.
    void GeneralPatient::scheduleAppointment(const std::string& date, const std::string& time) {
        appointmentDate = date + " " + time;
        hasAppointment = true;
    }

    // Clears the scheduled appointment details, resetting the status to inactive and date to "None".
    void GeneralPatient::cancelAppointment() {
        appointmentDate = "None";
        hasAppointment = false;
    }

    // Getter: Returns a boolean indicating whether an appointment is currently booked.
    bool GeneralPatient::getHasAppointment() const { return hasAppointment; }

    // Getter: Returns the string representation of the appointment date and time.
    std::string GeneralPatient::getAppointmentDate() const { return appointmentDate; }

}