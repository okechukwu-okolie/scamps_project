#pragma once // Ensures this header file is included only once during compilation

#include <exception> // Required for std::exception, the base class for standard exceptions
#include <string>    // Required for std::string to store and manage the error message

namespace scapms::utils {
    
    // Custom exception class tailored for handling domain-specific errors 
    // within the Smart Clinic Appointment & Patient Management System (SCAPMS)
    class ClinicException : public std::exception {
    private:
        std::string message; // Internal storage for the detailed error message

    public:
        // Explicit constructor that initializes the exception with a custom error string
        explicit ClinicException(const std::string& msg) : message(msg) {}

        // Overrides the standard what() method to provide a C-style string of the error message.
        // Marked 'noexcept' and 'override' for safety and correct polymorphism.
        const char* what() const noexcept override {
            return message.c_str();
        }
    };
}