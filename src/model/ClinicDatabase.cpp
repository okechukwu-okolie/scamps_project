#include "model/ClinicDatabase.h"
#include <algorithm>

namespace scapms::model {

    // Constructor: Initializes cache count to zero and clears the recent patients cache array
    ClinicDatabase::ClinicDatabase() : cacheCount(0) {
        for (int i = 0; i < CACHE_SIZE; ++i) {
            recentPatients[i] = nullptr;
        }
    }

    // Destructor: Cleans up dynamically allocated patient records to prevent memory leaks
    ClinicDatabase::~ClinicDatabase() {
        for (auto p : patients) {
            delete p;
        }
    }

    // Adds a new patient record to the database and updates the recent access cache
    void ClinicDatabase::addPatient(PatientRecord* record) {
        patients.push_back(record);
        updateRecentCache(record);
    }

    // Deletes a patient by ID, logs the action to the undo stack, and removes them from the database
    bool ClinicDatabase::deletePatient(const std::string& id) {
        for (auto it = patients.begin(); it != patients.end(); ++it) {
            if ((*it)->getPatientId() == id) {
                AdminAction act{"DELETE", id, *it};
                pushUndoAction(act);
                patients.erase(it);
                return true;
            }
        }
        return false;
    }

    // Finds and returns a patient record by ID, updating the recent cache upon a successful match
    PatientRecord* ClinicDatabase::findPatientById(const std::string& id) {
        for (auto p : patients) {
            if (p->getPatientId() == id) {
                updateRecentCache(p);
                return p;
            }
        }
        return nullptr;
    }

    // Returns a reference to the complete list of patient records
    std::vector<PatientRecord*>& ClinicDatabase::getPatients() { return patients; }

    // Adds a patient to the clinic's waiting queue
    void ClinicDatabase::enqueuePatient(PatientRecord* record) {
        waitingQueue.push(record);
    }

    // Removes and returns the next patient from the front of the waiting queue
    PatientRecord* ClinicDatabase::dequeuePatient() {
        if (waitingQueue.empty()) return nullptr;
        PatientRecord* p = waitingQueue.front();
        waitingQueue.pop();
        return p;
    }

    // Checks whether the waiting queue is currently empty
    bool ClinicDatabase::isQueueEmpty() const { return waitingQueue.empty(); }

    // Returns a copy of the current waiting queue
    std::queue<PatientRecord*> ClinicDatabase::getWaitingQueueCopy() const {
        return waitingQueue;
    }

    // Pushes an administrative action onto the undo stack for tracking/reversal
    void ClinicDatabase::pushUndoAction(const AdminAction& action) {
        undoStack.push(action);
    }

    // Pops the latest administrative action from the undo stack
    bool ClinicDatabase::popUndoAction(AdminAction& action) {
        if (undoStack.empty()) return false;
        action = undoStack.top();
        undoStack.pop();
        return true;
    }

    // Checks whether the undo stack is currently empty
    bool ClinicDatabase::isUndoStackEmpty() const { return undoStack.empty(); }

    // Adds a new appointment to the clinic's appointment schedule
    void ClinicDatabase::addAppointment(const Appointment& appt) {
        appointments.push_back(appt);
    }

    // Returns a reference to the list of scheduled appointments
    std::vector<Appointment>& ClinicDatabase::getAppointments() { return appointments; }

    // Updates the recent patient cache using a FIFO/sliding window approach
    void ClinicDatabase::updateRecentCache(PatientRecord* record) {
        for (int i = 0; i < cacheCount; ++i) {
            if (recentPatients[i] == record) return; // Record already cached
        }
        if (cacheCount < CACHE_SIZE) {
            recentPatients[cacheCount++] = record;
        } else {
            // Shift elements to make room for the newest accessed patient
            for (int i = 0; i < CACHE_SIZE - 1; ++i) {
                recentPatients[i] = recentPatients[i + 1];
            }
            recentPatients[CACHE_SIZE - 1] = record;
        }
    }

    // Returns the array of recently accessed patients
    PatientRecord** ClinicDatabase::getRecentPatients() { return recentPatients; }

    // Returns the current number of items stored in the recent patients cache
    int ClinicDatabase::getCacheCount() const { return cacheCount; }

}