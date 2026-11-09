#pragma once
#include <string>

namespace scapms::model {
    /**
     * @brief An interface representing entities that can have appointments scheduled and canceled.
     */
    class Appointable {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived classes.
         */
        virtual ~Appointable() = default;

        /**
         * @brief Schedules an appointment for a specific date and time.
         * @param date The date for the appointment (e.g., "YYYY-MM-DD").
         * @param time The time for the appointment (e.g., "HH:MM").
         */
        virtual void scheduleAppointment(const std::string& date, const std::string& time) = 0;

        /**
         * @brief Cancels an existing appointment.
         */
        virtual void cancelAppointment() = 0;
    };
}