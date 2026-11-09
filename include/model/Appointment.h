#pragma once

#include <string>

/**
 * @file Appointment.h
 * @brief Defines the Appointment model class within the Smart Clinic Appointment & Patient Management System.
 */

namespace scapms::model {

    /**
     * @class Appointment
     * @brief Represents an appointment entity, managing patient associations, scheduling timestamps, and lifecycle status.
     */
    class Appointment {
    private:
        std::string appointmentId; // Unique identifier for the appointment record
        std::string patientId;     // Unique identifier for the patient booked for the appointment
        std::string date;          // Scheduled date for the appointment (e.g., "YYYY-MM-DD")
        std::string time;          // Scheduled time for the appointment (e.g., "HH:MM")
        std::string status;        // Current state of the appointment (e.g., "Scheduled", "Completed", "Cancelled")

    public:
        /**
         * @brief Constructs a new Appointment instance.
         * @param appId Unique identifier for the appointment.
         * @param pId Unique identifier for the patient.
         * @param d Date of the appointment.
         * @param t Time of the appointment.
         * @param stat Initial status of the appointment (defaults to "Scheduled" if omitted).
         */
        Appointment(const std::string& appId, const std::string& pId, const std::string& d, const std::string& t, const std::string& stat = "Scheduled");
        
        // ==========================================
        // Accessor Methods (Getters)
        // ==========================================
        
        /** @brief Retrieves the unique appointment ID. */
        std::string getAppointmentId() const;

        /** @brief Retrieves the unique patient ID associated with this appointment. */
        std::string getPatientId() const;

        /** @brief Retrieves the scheduled date of the appointment. */
        std::string getDate() const;

        /** @brief Retrieves the scheduled time of the appointment. */
        std::string getTime() const;

        /** @brief Retrieves the current status of the appointment. */
        std::string getStatus() const;

        // ==========================================
        // Modifier & Utility Methods
        // ==========================================

        /**
         * @brief Updates the status of the appointment.
         * @param stat The new status string to assign.
         */
        void setStatus(const std::string& stat);

        /**
         * @brief Prints a formatted summary of the appointment details to standard output.
         */
        void display() const;
    };

} // namespace scapms::model