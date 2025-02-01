

#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>
#include <string>
#include <chrono>

namespace seneca {

    class Event {
    private:
        std::string m_name;                              // Event name
        std::chrono::nanoseconds m_duration{};          // Duration of the event

    public:
        // Default constructor
        Event() = default;

        // Parameterized constructor
        Event(const char* name, const std::chrono::nanoseconds& duration)
            : m_name(name), m_duration(duration) {}

        // Friend function to format and display event details
        friend std::ostream& operator<<(std::ostream& out, const Event& event);
    };

}  // namespace seneca

#endif // SENECA_EVENT_H
