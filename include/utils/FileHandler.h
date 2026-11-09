#pragma once

#include <vector>
#include <string>
#include "model/PatientRecord.h"
#include "model/ClinicDatabase.h"

/**
 * @namespace scapms::utils
 * @brief Contains utility and helper classes for system-wide operations 
 *        such as file persistence, data formatting, and input validation.
 */
namespace scapms::utils {

    /**
     * @class FileHandler
     * @brief Manages disk I/O and persistence operations for saving and 
     *        loading patient records and clinic database states.
     */
    class FileHandler {
    public:
        /**
         * @brief Serializes and writes a collection of patient records to disk.
         * 
         * @param filename The destination file path or name where records will be saved.
         * @param patients A constant vector containing pointers to the PatientRecord objects to be persisted.
         */
        static void savePatientsToFile(const std::string& filename, const std::vector<model::PatientRecord*>& patients);

        /**
         * @brief Reads persistent data from disk, deserializes it, and populates the clinic database.
         * 
         * @param filename The source file path or name to read patient records from.
         * @param db A reference to the ClinicDatabase instance where the loaded patient records will be populated.
         */
        static void loadPatientsFromFile(const std::string& filename, model::ClinicDatabase& db);
    };
}