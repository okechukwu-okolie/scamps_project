#pragma once

#include <string>
#include <iostream>

namespace scapms::model {

    /**
     * @brief Abstract base class representing a general patient record in the system.
     * 
     * This class encapsulates shared demographic and contact details, and defines 
     * a polymorphic interface for specialized patient types.
     */
    class PatientRecord {
    protected:
        // --- Core Patient Attributes ---
        std::string patientId;    // Unique identifier for the patient
        std::string name;         // Full name of the patient
        int age;                  // Age of the patient in years
        std::string contactInfo;  // Patient's phone number, email, or address

    public:
        /**
         * @brief Construct a new Patient Record object.
         * 
         * @param id Unique patient identifier
         * @param n Patient's full name
         * @param a Patient's age
         * @param contact Patient's contact information
         */
        PatientRecord(const std::string& id, const std::string& n, int a, const std::string& contact);
        
        /**
         * @brief Virtual destructor to ensure proper resource cleanup in derived classes.
         */
        virtual ~PatientRecord() = default;

        // --- Accessor (Getter) Methods ---
        std::string getPatientId() const;
        std::string getName() const;
        int getAge() const;
        std::string getContactInfo() const;

        // --- Mutator (Setter) Methods ---
        void setPatientId(const std::string& id);
        void setName(const std::string& n);
        void setAge(int a);
        void setContactInfo(const std::string& contact);

        // --- Pure Virtual Methods (Interface for Derived Classes) ---
        
        /**
         * @brief Returns the classification type of the patient (e.g., Inpatient, Outpatient).
         * @return std::string Patient type descriptor
         */
        virtual std::string getPatientType() const = 0;

        /**
         * @brief Outputs or prints detailed patient information.
         */
        virtual void displayDetails() const = 0;
    };

} // namespace scapms::model