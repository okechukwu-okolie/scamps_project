#pragma once

// Standard Library headers for underlying data structures
#include <vector>
#include <queue>
#include <stack>

// Custom domain model headers
#include "model/PatientRecord.h"
#include "model/Appointment.h"

namespace scapms::model {

    /**
     * @brief Represents an administrative action performed in the system,
     * designed to support the undo/rollback mechanism.
     */
    struct AdminAction {
        std::string actionType;          // The category/type of action performed (e.g., "DELETE", "UPDATE")
        std::string patientId;           // The unique identifier of the patient affected
        PatientRecord* backupRecord;     // Pointer to the previous state/record for restoration during an undo
    };

    /**
     * @brief Core database and management class for the clinic system.
     * Handles patient records, waiting queues, undo operations, appointments, and a recent cache.
     */
    class ClinicDatabase {
    private:
        // --- Core Data Storage & Structures ---
        std::vector<PatientRecord*> patients;        // Dynamic list storing pointers to all registered patients
        std::queue<PatientRecord*> waitingQueue;     // FIFO queue managing patients currently waiting to be seen
        std::stack<AdminAction> undoStack;           // LIFO stack tracking administrative changes for undo functionality
        std::vector<Appointment> appointments;       // Dynamic list storing all scheduled appointments

        // --- Recent Patient Cache Configuration ---
        static const int CACHE_SIZE = 10;            // Maximum capacity for the recently accessed patients cache
        PatientRecord* recentPatients[CACHE_SIZE];   // Fixed-size array holding pointers to recently viewed/modified patients
        int cacheCount;                              // Tracks the current number of active entries in the cache

    public:
        // --- Constructors and Destructors ---
        ClinicDatabase();
        ~ClinicDatabase();

        // --- Patient Record Management ---
        void addPatient(PatientRecord* record);
        bool deletePatient(const std::string& id);
        PatientRecord* findPatientById(const std::string& id);
        std::vector<PatientRecord*>& getPatients();

        // --- Waiting Queue Operations (FIFO) ---
        void enqueuePatient(PatientRecord* record);
        PatientRecord* dequeuePatient();
        bool isQueueEmpty() const;
        std::queue<PatientRecord*> getWaitingQueueCopy() const;

        // --- Undo Stack Operations (LIFO) ---
        void pushUndoAction(const AdminAction& action);
        bool popUndoAction(AdminAction& action);
        bool isUndoStackEmpty() const;

        // --- Appointment Management ---
        void addAppointment(const Appointment& appt);
        std::vector<Appointment>& getAppointments();

        // --- Recent Patient Cache Management ---
        void updateRecentCache(PatientRecord* record);
        PatientRecord** getRecentPatients();
        int getCacheCount() const;
    };
}