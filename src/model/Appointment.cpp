#include "model/Appointment.h"
#include <iostream>

namespace scapms::model {

    // Constructor: Initializes a new Appointment object with provided credentials and details
    Appointment::Appointment(const std::string& appId, const std::string& pId, const std::string& d, const std::string& t, const std::string& stat)
        : appointmentId(appId), patientId(pId), date(d), time(t), status(stat) {}

    // Getters: Retrieve individual member variables (appointment ID, patient ID, date, time, and status)
    std::string Appointment::getAppointmentId() const { return appointmentId; }
    std::string Appointment::getPatientId() const { return patientId; }
    std::string Appointment::getDate() const { return date; }
    std::string Appointment::getTime() const { return time; }
    std::string Appointment::getStatus() const { return status; }

    // Setter: Updates the current status of the appointment
    void Appointment::setStatus(const std::string& stat) { status = stat; }

    // Display Method: Outputs formatted appointment details to the console
    void Appointment::display() const {
        std::cout << "Appt ID: " << appointmentId << ", Patient ID: " << patientId 
                  << ", Date: " << date << ", Time: " << time << ", Status: " << status << "\n";
    }

} // namespace scapms::model