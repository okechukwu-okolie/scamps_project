#include "utils/FileHandler.h"
#include "model/GeneralPatient.h"
#include "model/EmergencyPatient.h"
#include "model/FollowUpPatient.h"
#include "utils/Exceptions.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace scapms::utils {

    /**
     * @brief Serializes and saves a collection of patient records to disk in CSV format.
     * @param filename Path to the output file.
     * @param patients Vector of polymorphic PatientRecord pointers to be saved.
     */
    void FileHandler::savePatientsToFile(const std::string& filename, const std::vector<model::PatientRecord*>& patients) {
        // Open file stream for writing
        std::ofstream file(filename);
        
        // Ensure the file was opened successfully; throw custom exception if it fails
        if (!file.is_open()) {
            throw ClinicException("Error: Failed to open file for saving patient data.");
        }

        // Iterate through each patient record and write comma-separated attributes
        for (auto p : patients) {
            file << p->getPatientType() << ","
                 << p->getPatientId() << ","
                 << p->getName() << ","
                 << p->getAge() << ","
                 << p->getContactInfo() << "\n";
        }

        // Close the file stream
        file.close();
    }

    /**
     * @brief Loads and parses patient records from a CSV file, populating the clinic database.
     * @param filename Path to the input file.
     * @param db Reference to the ClinicDatabase where instantiated patients will be added.
     */
    void FileHandler::loadPatientsFromFile(const std::string& filename, model::ClinicDatabase& db) {
        // Open file stream for reading
        std::ifstream file(filename);
        
        // Ensure the file exists and is accessible; throw custom exception if it fails
        if (!file.is_open()) {
            throw ClinicException("Error: Failed to open file for loading patient data.");
        }

        std::string line;
        
        // Read the file line by line
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type, id, name, ageStr, contact;

            // Parse comma-delimited fields from the current line
            if (std::getline(ss, type, ',') &&
                std::getline(ss, id, ',') &&
                std::getline(ss, name, ',') &&
                std::getline(ss, ageStr, ',') &&
                std::getline(ss, contact, ',')) {
                
                // Convert age string representation to integer
                int age = std::stoi(ageStr);
                model::PatientRecord* p = nullptr;

                // Factory logic: Instantiate the correct derived patient class based on the type flag
                if (type == "General") {
                    p = new model::GeneralPatient(id, name, age, contact);
                } else if (type == "Emergency") {
                    p = new model::EmergencyPatient(id, name, age, contact, "High");
                } else if (type == "FollowUp") {
                    p = new model::FollowUpPatient(id, name, age, contact, 1);
                }

                // If instantiation succeeded, add the patient record to the database
                if (p) {
                    db.addPatient(p);
                }
            }
        }

        // Close the file stream
        file.close();
    }
}