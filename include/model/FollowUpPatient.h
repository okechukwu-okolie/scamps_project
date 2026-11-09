#pragma once

// Include base classes for patient records and appointment management capabilities
#include "model/PatientRecord.h"
#include "model/Appointable.h"

namespace scapms::model {

    /**
     * @class FollowUpPatient
     * @brief Represents a returning patient who requires follow-up care.
     * 
     * This class inherits from PatientRecord (for general patient information) 
     * and Appointable (for managing appointment schedules).
     */
    class FollowUpPatient : public PatientRecord, public Appointable {
    private:
        int previousVisitCount;        // Tracks the total number of past visits for this patient
        std::string appointmentDate;   // Stores the date and time of the upcoming scheduled appointment
        bool hasAppointment;           // Flag indicating whether the patient currently has an active appointment

    public:
        /**
         * @brief Construct a new FollowUpPatient object.
         * 
         * @param id Unique identifier for the patient
         * @param n Patient's name
         * @param a Patient's age
         * @param contact Patient's contact information
         * @param visits Initial count of previous visits
         */
        FollowUpPatient(const std::string& id, const std::string& n, int a, const std::string& contact, int visits);

        // --- Polymorphic / Overridden Methods ---
        
        // Returns the specific classification type of the patient
        std::string getPatientType() const override;

        // Displays detailed information about the patient and their follow-up history
        void displayDetails() const override;

        // Schedules a new appointment with the specified date and time
        void scheduleAppointment(const std::string& date, const std::string& time) override;

        // Cancels the patient's currently scheduled appointment
        void cancelAppointment() override;

        // --- Getter Methods ---
        
        // Returns the number of previous visits
        int getPreviousVisitCount() const;

        // Checks if an appointment is currently scheduled
        bool getHasAppointment() const;

        // Returns the currently scheduled appointment date string
        std::string getAppointmentDate() const;
    };

}