#include "controller/SearchEngine.h"
#include <algorithm>

namespace scapms::controller {

    /**
     * @brief Performs a linear search to find a patient record by their unique ID.
     * Iterates through the entire vector sequentially.
     */
    model::PatientRecord* SearchEngine::linearSearchById(const std::vector<model::PatientRecord*>& patients, const std::string& id) {
        // Traverse through each patient record in the collection
        for (auto p : patients) {
            // Check if the current patient's ID matches the target ID
            if (p->getPatientId() == id) {
                return p; // Found match, return pointer to the record
            }
        }
        return nullptr; // Return nullptr if no match is found after full traversal
    }

    /**
     * @brief Performs an iterative binary search to find a patient record by name.
     * Note: Assumes that the input vector 'patients' is already sorted alphabetically by name.
     */
    model::PatientRecord* SearchEngine::binarySearchByName(const std::vector<model::PatientRecord*>& patients, const std::string& name) {
        // Initialize pointers for the search window boundaries
        int left = 0;
        int right = static_cast<int>(patients.size()) - 1;

        // Continue searching while the search space is valid
        while (left <= right) {
            // Calculate the middle index, avoiding potential integer overflow
            int mid = left + (right - left) / 2;
            std::string midName = patients[mid]->getName();

            // Check if the middle element matches the target name
            if (midName == name) {
                return patients[mid]; // Match found
            }
            
            // If target name is alphabetically greater, discard the left half
            if (midName < name) {
                left = mid + 1;
            } 
            // If target name is alphabetically smaller, discard the right half
            else {
                right = mid - 1;
            }
        }
        
        return nullptr; // Target name not found in the collection
    }

    /**
     * @brief Recursive helper function for linear search by name.
     * Checks the current index and recursively calls for the next index.
     */
    model::PatientRecord* SearchEngine::recursiveSearchHelper(const std::vector<model::PatientRecord*>& patients, const std::string& name, size_t index) {
        // Base case 1: Reached the end of the vector without finding a match
        if (index >= patients.size()) {
            return nullptr;
        }
        
        // Base case 2: Current element matches the target name
        if (patients[index]->getName() == name) {
            return patients[index];
        }
        
        // Recursive step: Increment index and check the next patient record
        return recursiveSearchHelper(patients, name, index + 1);
    }

    /**
     * @brief Public interface to initiate a recursive search by patient name.
     * Starts the recursion from index 0.
     */
    model::PatientRecord* SearchEngine::recursiveSearchByName(const std::vector<model::PatientRecord*>& patients, const std::string& name) {
        return recursiveSearchHelper(patients, name, 0);
    }
}