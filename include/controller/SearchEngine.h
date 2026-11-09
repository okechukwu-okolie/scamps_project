#pragma once

// Standard library headers for collection and string manipulation
#include <vector>
#include <string>

// Core domain model header for patient records
#include "model/PatientRecord.h"

namespace scapms::controller {

    /**
     * @class SearchEngine
     * @brief Provides efficient searching utilities for PatientRecord collections.
     * 
     * This controller class encapsulates different search strategies (linear, binary, 
     * and recursive) to locate patient records by ID or name within the system.
     */
    class SearchEngine {
    private:
        /**
         * @brief Recursive helper function to traverse the patient vector by index.
         * @param patients Collection of patient record pointers to search through.
         * @param name The target patient name being matched.
         * @param index Current vector index being evaluated.
         * @return Pointer to the matched PatientRecord, or nullptr if not found.
         */
        static model::PatientRecord* recursiveSearchHelper(const std::vector<model::PatientRecord*>& patients, const std::string& name, size_t index);

    public:
        /**
         * @brief Performs a linear search to locate a patient record by its unique ID.
         * @param patients Collection of patient record pointers.
         * @param id The unique patient identifier string to search for.
         * @return Pointer to the matching PatientRecord, or nullptr if not found.
         */
        static model::PatientRecord* linearSearchById(const std::vector<model::PatientRecord*>& patients, const std::string& id);

        /**
         * @brief Performs a binary search to locate a patient record by name.
         * @note Requires the input collection to be pre-sorted lexicographically by name.
         * @param patients Sorted collection of patient record pointers.
         * @param name The target patient name to search for.
         * @return Pointer to the matching PatientRecord, or nullptr if not found.
         */
        static model::PatientRecord* binarySearchByName(const std::vector<model::PatientRecord*>& patients, const std::string& name);

        /**
         * @brief Initiates a recursive search to locate a patient record by name.
         * @param patients Collection of patient record pointers.
         * @param name The target patient name to search for.
         * @return Pointer to the matching PatientRecord, or nullptr if not found.
         */
        static model::PatientRecord* recursiveSearchByName(const std::vector<model::PatientRecord*>& patients, const std::string& name);
    };

}