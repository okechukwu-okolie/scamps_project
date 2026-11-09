#include "model/FollowUpPatient.h"
#include <iostream>

namespace scapms::model {

    // Constructor: Initializes the FollowUpPatient object by invoking the base PatientRecord 
    // constructor and setting follow-up specific fields (visit count and default appointment state).
    FollowUpPatient::FollowUpPatient(const std::string& id, const std::string& n, int a, const std::string& contact, int visits)
        : PatientRecord(id, n, a, contact), previousVisitCount(visits), appointmentDate("None"), hasAppointment(false) {}

    // Returns the specific patient category type string
    std::string FollowUpPatient::getPatientType() const { return "FollowUp"; }

    // Outputs formatted details of the follow-up patient to the console
    void FollowUpPatient::displayDetails() const {
        std::cout << "[Follow-Up Patient - Visits: " << previousVisitCount << "] ID: " << patientId << ", Name: " << name 
                  << ", Age: " << age << ", Contact: " << contactInfo 
                  << ", Appointment: " << appointmentDate << "\n";
    }

    // Schedules a new appointment by concatenating date and time and updating the appointment status flag
    void FollowUpPatient::scheduleAppointment(const std::string& date, const std::string& time) {
        appointmentDate = date + " " + time;
        hasAppointment = true;
    }

    // Cancels the existing appointment, resetting the date string and appointment flag
    void FollowUpPatient::cancelAppointment() {
        appointmentDate = "None";
        hasAppointment = false;
    }

    // Getter methods for accessing private member variables
    int FollowUpPatient::getPreviousVisitCount() const { return previousVisitCount; }
    bool FollowUpPatient::getHasAppointment() const { return hasAppointment; }
    std::string FollowUpPatient::getAppointmentDate() const { return appointmentDate; }

}