#include "model/EmergencyPatient.h"
#include <iostream>

namespace scapms::model {

    // Constructor: Initializes the EmergencyPatient, invokes the base PatientRecord constructor,
    // and sets default emergency-specific attributes (immediate priority/urgent status and an active appointment state).
    EmergencyPatient::EmergencyPatient(const std::string& id, const std::string& n, int a, const std::string& contact, const std::string& triage)
        : PatientRecord(id, n, a, contact), triageLevel(triage), appointmentDate("Immediate/Urgent"), hasAppointment(true) {}

    // Returns a string identifier classifying the patient type as "Emergency".
    std::string EmergencyPatient::getPatientType() const { 
        return "Emergency"; 
    }

    // Prints formatted details of the emergency patient to the standard output, highlighting their triage priority level.
    void EmergencyPatient::displayDetails() const {
        std::cout << "[Emergency Patient - Priority: " << triageLevel << "] ID: " << patientId << ", Name: " << name 
                  << ", Age: " << age << ", Contact: " << contactInfo 
                  << ", Appointment: " << appointmentDate << "\n";
    }

    // Schedules or updates the appointment date and time for the emergency patient and marks the appointment flag as true.
    void EmergencyPatient::scheduleAppointment(const std::string& date, const std::string& time) {
        appointmentDate = date + " " + time;
        hasAppointment = true;
    }

    // Cancels the current appointment by resetting the appointment date/time string and setting the appointment flag to false.
    void EmergencyPatient::cancelAppointment() {
        appointmentDate = "None";
        hasAppointment = false;
    }

    // Getter methods for retrieving private/protected member variables safely from outside the class.
    std::string EmergencyPatient::getTriageLevel() const { 
        return triageLevel; 
    }
    
    bool EmergencyPatient::getHasAppointment() const { 
        return hasAppointment; 
    }
    
    std::string EmergencyPatient::getAppointmentDate() const { 
        return appointmentDate; 
    }

}