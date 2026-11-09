#pragma once // Ensures the header file is included only once during compilation
#include <string> // Required for std::string used in ID generation

namespace scapms::utils {
    
    // Utility class responsible for generating unique system identifiers
    class IDGenerator {
    private:
        static int counter; // Internal tracking counter to ensure uniqueness across generated IDs

    public:
        // Generates and returns a unique, formatted string identifier for a patient record
        static std::string generatePatientId();
    };

}