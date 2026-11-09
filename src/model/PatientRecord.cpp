#include "model/PatientRecord.h"

namespace scapms::model {

    // ==========================================
    // Constructor
    // ==========================================
    // Initializes a new PatientRecord object with the provided ID, name, age, and contact info 
    // using a member initializer list.
    PatientRecord::PatientRecord(const std::string& id, const std::string& n, int a, const std::string& contact)
        : patientId(id), name(n), age(a), contactInfo(contact) {}

    // ==========================================
    // Getter Methods (Accessors)
    // ==========================================
    
    // Returns the unique patient identification number/string
    std::string PatientRecord::getPatientId() const { return patientId; }

    // Returns the full name of the patient
    std::string PatientRecord::getName() const { return name; }

    // Returns the age of the patient
    int PatientRecord::getAge() const { return age; }

    // Returns the contact information (e.g., phone/email) of the patient
    std::string PatientRecord::getContactInfo() const { return contactInfo; }

    // ==========================================
    // Setter Methods (Mutators)
    // ==========================================
    
    // Updates the unique patient identification number/string
    void PatientRecord::setPatientId(const std::string& id) { patientId = id; }

    // Updates the full name of the patient
    void PatientRecord::setName(const std::string& n) { name = n; }

    // Updates the age of the patient
    void PatientRecord::setAge(int a) { age = a; }

    // Updates the contact information of the patient
    void PatientRecord::setContactInfo(const std::string& contact) { contactInfo = contact; }
    
}