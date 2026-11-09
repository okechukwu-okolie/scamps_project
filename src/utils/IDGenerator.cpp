#include "utils/IDGenerator.h"

namespace scapms::utils {

    // Initialize the static counter member with a starting sequence value of 101
    int IDGenerator::counter = 101;

    // Generates a sequential, unique patient identifier string (e.g., "P101", "P102")
    std::string IDGenerator::generatePatientId() {
        // Concatenate the prefix "P" with the current counter value, then post-increment the counter
        return "P" + std::to_string(counter++);
    }

}