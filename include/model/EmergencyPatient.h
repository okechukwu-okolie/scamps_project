#pragma once // Ensure the header file is compiled only once during a build

// Include necessary base class and interface headers
#include "model/PatientRecord.h"
#include "model/Appointable.h"

namespace scapms::model {
    /**
     * @brief Represents an emergency patient in the system.
     * Inherits from PatientRecord for general patient info and Appointable for scheduling capabilities.
     */
    class EmergencyPatient : public PatientRecord, public Appointable {
    private:
        // Private member variables to store specific emergency patient state
        std::string triageLevel;      // Severity level of the emergency (e.g., Critical, Urgent)
        std::string appointmentDate;  // Scheduled appointment date and time, if applicable
        bool hasAppointment;          // Flag indicating if an appointment is currently active

    public:
        /**
         * @brief Constructs a new EmergencyPatient object.
         * @param id Unique patient identifier
         * @param n Patient name
         * @param a Patient age
         * @param contact Patient contact information
         * @param triage Initial triage severity level
         */
        EmergencyPatient(const std::string& id, const std::string& n, int a, const std::string& contact, const std::string& triage);

        // --- Overridden Methods from Base Classes and Interfaces ---

        /** @brief Returns the specific type of the patient ("Emergency"). */
        std::string getPatientType() const override;

        /** @brief Displays detailed information about the emergency patient. */
        void displayDetails() const override;

        /** @brief Schedules an appointment for the emergency patient. */
        void scheduleAppointment(const std::string& date, const std::string& time) override;

        /** @brief Cancels the currently scheduled appointment. */
        void cancelAppointment() override;

        // --- Accessors (Getters) ---

        /** @brief Gets the triage level assigned to the patient. */
        std::string getTriageLevel() const;

        /** @brief Checks whether the patient currently has a scheduled appointment. */
        bool getHasAppointment() const;

        /** @brief Gets the date of the scheduled appointment. */
        std::string getAppointmentDate() const;
    };
}