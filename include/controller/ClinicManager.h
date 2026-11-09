#pragma once

// Model and utility dependencies
#include "model/ClinicDatabase.h"
#include "utils/FileHandler.h"
#include <string>

namespace scapms::controller {

    /**
     * @brief Manages the core business logic, data flow, and operations 
     * for patients, appointments, sorting, reporting, and file persistence.
     */
    class ClinicManager {
    private:
        // Core database instance housing patient records and appointment data
        model::ClinicDatabase db;

    public:
        // ==========================================
        // Lifecycle & Accessor
        // ==========================================
        ClinicManager();
        
        /**
         * @brief Provides access to the underlying clinic database model.
         * @return Reference to the ClinicDatabase instance.
         */
        model::ClinicDatabase& getDatabase();

        // ==========================================
        // Patient & Appointment Management
        // ==========================================
        
        /**
         * @brief Registers a new patient into the system with specific demographic and contact details.
         */
        void registerPatient(const std::string& type, const std::string& id, const std::string& name, int age, const std::string& contact, const std::string& extra = "");
        
        /**
         * @brief Removes a patient record from the database by their unique ID.
         */
        bool deletePatient(const std::string& id);
        
        /**
         * @brief Schedules an appointment for a specific patient.
         */
        void scheduleAppointment(const std::string& patientId, const std::string& date, const std::string& time);
        
        /**
         * @brief Cancels an existing patient appointment.
         */
        void cancelAppointment(const std::string& patientId);

        // ==========================================
        // Sorting Algorithms
        // ==========================================
        
        /**
         * @brief Sorts patient records using Selection Sort based on the specified field identifier.
         */
        void sortPatientsBySelection(int sortByField);
        
        /**
         * @brief Sorts patient records using Insertion Sort based on the specified field identifier.
         */
        void sortPatientsByInsertion(int sortByField);

        // ==========================================
        // Reporting & Analytics Engine
        // ==========================================
        
        /** @brief Generates a report showing the distribution of patient categories. */
        void generateReportCategoryDistribution() const;
        
        /** @brief Generates a report listing all currently pending appointments. */
        void generateReportPendingAppointments() const;
        
        /** @brief Generates a report identifying frequently attended patients. */
        void generateReportFrequentlyAttended() const;
        
        /** @brief Generates a comprehensive daily summary report. */
        void generateReportDailySummary() const;

        // ==========================================
        // Data Persistence (File I/O)
        // ==========================================
        
        /** @brief Serializes and saves current clinic data to disk. */
        void saveData(const std::string& filename);
        
        /** @brief Loads and deserializes clinic data from disk. */
        void loadData(const std::string& filename);

        // ==========================================
        // State Management
        // ==========================================
        
        /**
         * @brief Reverts the last performed operation to support undo functionality.
         * @return True if the operation was successfully undone, false otherwise.
         */
        bool undoLastOperation();
    };
}