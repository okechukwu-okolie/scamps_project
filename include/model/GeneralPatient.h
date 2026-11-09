#pragma once

// Include required base class and interface headers
#include "model/PatientRecord.h"
#include "model/Appointable.h"

namespace scapms::model {
    
    // Represents a general patient, inheriting core patient details from PatientRecord 
    // and appointment capabilities from the Appointable interface.
    class GeneralPatient : public PatientRecord, public Appointable {
    private:
        std::string appointmentDate; // Stores the date and time of the scheduled appointment
        bool hasAppointment;         // Tracks whether the patient currently holds an active appointment

    public:
        // Constructor to initialize a general patient with identification, name, age, and contact info
        GeneralPatient(const std::string& id, const std::string& n, int a, const std::string& contact);

        // Returns the specific classification type of the patient
        std::string getPatientType() const override;

        // Outputs/displays the detailed information of the patient
        void displayDetails() const override;

        // Schedules an appointment for the patient given a specific date and time
        void scheduleAppointment(const std::string& date, const std::string& time) override;

        // Cancels any currently active appointment for the patient
        void cancelAppointment() override;

        // Getter to check if the patient has an active appointment
        bool getHasAppointment() const;

        // Getter to retrieve the scheduled appointment date string
        std::string getAppointmentDate() const;
    };
}