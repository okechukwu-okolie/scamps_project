#include "controller/ClinicManager.h"
#include "model/GeneralPatient.h"
#include "model/EmergencyPatient.h"
#include "model/FollowUpPatient.h"
#include "utils/Exceptions.h"
#include <iostream>
#include <sstream>

namespace scapms::controller {

    // Constructor initializes the ClinicManager
    ClinicManager::ClinicManager() {}

    // Getter method to provide access to the underlying clinic database reference
    model::ClinicDatabase& ClinicManager::getDatabase() { return db; }

    // Registers a new patient into the system based on their specific type (General, Emergency, or FollowUp)
    void ClinicManager::registerPatient(const std::string& type, const std::string& id, const std::string& name, int age, const std::string& contact, const std::string& extra) {
        // Validation: Ensure age is within realistic human bounds
        if (age < 0 || age > 120) {
            throw utils::ClinicException("Error: Patient age must be between 0 and 120.");
        }
        // Validation: Ensure patient ID is unique
        if (db.findPatientById(id) != nullptr) {
            throw utils::ClinicException("Error: Patient ID already exists.");
        }

        model::PatientRecord* newPatient = nullptr;
        
        // Polymorphic instantiation depending on the requested patient category
        if (type == "General") {
            newPatient = new model::GeneralPatient(id, name, age, contact);
        } else if (type == "Emergency") {
            newPatient = new model::EmergencyPatient(id, name, age, contact, extra.empty() ? "High" : extra);
        } else if (type == "FollowUp") {
            int visits = 1;
            try { visits = std::stoi(extra); } catch(...) { visits = 1; }
            newPatient = new model::FollowUpPatient(id, name, age, contact, visits);
        } else {
            throw utils::ClinicException("Error: Invalid patient type specified.");
        }

        // Add patient to the database and record the action on the undo stack for administrative rollbacks
        db.addPatient(newPatient);
        model::AdminAction act{"ADD", id, newPatient};
        db.pushUndoAction(act);
    }

    // Deletes an existing patient from the clinic database by ID
    bool ClinicManager::deletePatient(const std::string& id) {
        bool success = db.deletePatient(id);
        if (!success) {
            throw utils::ClinicException("Error: Patient ID not found for deletion.");
        }
        return true;
    }

    // Schedules an appointment for a patient if their patient type supports appointable behavior
    void ClinicManager::scheduleAppointment(const std::string& patientId, const std::string& date, const std::string& time) {
        model::PatientRecord* p = db.findPatientById(patientId);
        if (!p) {
            throw utils::ClinicException("Error: Patient ID not found for appointment scheduling.");
        }
        // Downcast or interface check to ensure the patient supports appointments
        model::Appointable* app = dynamic_cast<model::Appointable*>(p);
        if (!app) {
            throw utils::ClinicException("Error: Patient type is not appointable.");
        }
        app->scheduleAppointment(date, time);
        
        // Generate a unique appointment ID and register it in the database
        static int apptCounter = 1000;
        std::string apptId = "APT" + std::to_string(apptCounter++);
        model::Appointment appointment(apptId, patientId, date, time, "Scheduled");
        db.addAppointment(appointment);
    }

    // Cancels an existing appointment for an appointable patient
    void ClinicManager::cancelAppointment(const std::string& patientId) {
        model::PatientRecord* p = db.findPatientById(patientId);
        if (!p) {
            throw utils::ClinicException("Error: Patient ID not found.");
        }
        model::Appointable* app = dynamic_cast<model::Appointable*>(p);
        if (app) {
            app->cancelAppointment();
        }
    }

    // Sorts the patient records collection using the Selection Sort algorithm based on a chosen field criteria
    void ClinicManager::sortPatientsBySelection(int sortByField) {
        auto& pats = db.getPatients();
        size_t n = pats.size();
        for (size_t i = 0; i < n; ++i) {
            size_t minIdx = i;
            for (size_t j = i + 1; j < n; ++j) {
                bool condition = false;
                if (sortByField == 1) {
                    condition = pats[j]->getName() < pats[minIdx]->getName();
                } else if (sortByField == 2) {
                    condition = pats[j]->getPatientId() < pats[minIdx]->getPatientId();
                } else if (sortByField == 3) {
                    condition = pats[j]->getAge() < pats[minIdx]->getAge();
                }
                if (condition) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                std::swap(pats[i], pats[minIdx]);
            }
        }
    }

    // Sorts the patient records collection using the Insertion Sort algorithm based on a chosen field criteria
    void ClinicManager::sortPatientsByInsertion(int sortByField) {
        auto& pats = db.getPatients();
        size_t n = pats.size();
        for (size_t i = 1; i < n; ++i) {
            model::PatientRecord* key = pats[i];
            int j = static_cast<int>(i) - 1;

            while (j >= 0) {
                bool condition = false;
                if (sortByField == 1) {
                    condition = pats[j]->getName() > key->getName();
                } else if (sortByField == 2) {
                    condition = pats[j]->getPatientId() > key->getPatientId();
                } else if (sortByField == 3) {
                    condition = pats[j]->getAge() > key->getAge();
                }
                if (condition) {
                    pats[j + 1] = pats[j];
                    j--;
                } else {
                    break;
                }
            }
            pats[j + 1] = key;
        }
    }

    // Generates and prints a breakdown report of patient categories (General, Emergency, FollowUp)
    void ClinicManager::generateReportCategoryDistribution() const {
        int general = 0, emergency = 0, followUp = 0;
        for (auto p : db.getPatients()) {
            std::string t = p->getPatientType();
            if (t == "General") general++;
            else if (t == "Emergency") emergency++;
            else if (t == "FollowUp") followUp++;
        }
        std::cout << "\n=== REPORT: Patient Category Distribution ===\n";
        std::cout << "General Patients: " << general << "\n";
        std::cout << "Emergency Patients: " << emergency << "\n";
        std::cout << "Follow-Up Patients: " << followUp << "\n";
        std::cout << "Total Patients: " << (general + emergency + followUp) << "\n";
    }

    // Generates a report displaying all currently pending/scheduled appointments
    void ClinicManager::generateReportPendingAppointments() const {
        std::cout << "\n=== REPORT: Patients with Pending Appointments ===\n";
        for (auto& appt : db.getAppointments()) {
            if (appt.getStatus() == "Scheduled") {
                appt.display();
            }
        }
    }

    // Generates a report listing patients and their visitation info/types
    void ClinicManager::generateReportFrequentlyAttended() const {
        std::cout << "\n=== REPORT: Most Frequently Attended Patients ===\n";
        for (auto p : db.getPatients()) {
            std::cout << "Patient ID: " << p->getPatientId() << ", Name: " << p->getName() 
                      << " (" << p->getPatientType() << ")\n";
        }
    }

    // Generates a comprehensive daily summary report of appointment statuses (Completed, Pending, Cancelled)
    void ClinicManager::generateReportDailySummary() const {
        int total = static_cast<int>(db.getAppointments().size());
        int completed = 0, pending = 0, cancelled = 0;
        for (auto& appt : db.getAppointments()) {
            if (appt.getStatus() == "Completed") completed++;
            else if (appt.getStatus() == "Scheduled") pending++;
            else if (appt.getStatus() == "Cancelled") cancelled++;
        }
        std::cout << "\n=== REPORT: Daily Appointment Summary ===\n";
        std::cout << "Total Appointments: " << total << "\n";
        std::cout << "Completed: " << completed << "\n";
        std::cout << "Pending: " << pending << "\n";
        std::cout << "Cancelled: " << cancelled << "\n";
    }

    // Saves clinic patient data to persistent storage via file handling utilities
    void ClinicManager::saveData(const std::string& filename) {
        utils::FileHandler::savePatientsToFile(filename, db.getPatients());
    }

    // Loads clinic patient data from persistent storage into the database
    void ClinicManager::loadData(const std::string& filename) {
        utils::FileHandler::loadPatientsFromFile(filename, db);
    }

    // Reverts the last administrative action performed (undo feature)
    bool ClinicManager::undoLastOperation() {
        if (db.isUndoStackEmpty()) return false;
        model::AdminAction act;
        db.popUndoAction(act);
        
        if (act.actionType == "ADD") {
            db.deletePatient(act.patientId);
            std::cout << "Undo successful: Removed recently added patient " << act.patientId << "\n";
        } else if (act.actionType == "DELETE") {
            if (act.backupRecord) {
                db.addPatient(act.backupRecord);
                std::cout << "Undo successful: Restored deleted patient " << act.patientId << "\n";
            }
        }
        return true;
    }
}