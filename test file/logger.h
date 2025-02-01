
#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"

namespace seneca {

    class Logger {
    private:
        Event* m_events;       // Pointer to dynamic array of events
        size_t m_size;         // Number of events currently stored
        size_t m_capacity;     // Total capacity of the dynamic array

        void resize(size_t new_capacity); // Resizes the dynamic array

    public:
        Logger();                  // Default constructor
        ~Logger();                 // Destructor

        Logger(const Logger&) = delete;            // Disable copy constructor
        Logger& operator=(const Logger&) = delete; // Disable copy assignment

        Logger(Logger&& other) noexcept;            // Move constructor
        Logger& operator=(Logger&& other) noexcept; // Move assignment

        void addEvent(const Event& event);          // Add an event to the log

        friend std::ostream& operator<<(std::ostream& out, const Logger& logger);
    };

} // namespace seneca
#endif