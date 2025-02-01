

#include "logger.h"
#include "settings.h"
#include <iostream>

namespace seneca {

    // Default constructor
    Logger::Logger() : m_events(nullptr), m_size(0), m_capacity(0) {}

    // Destructor
    Logger::~Logger() {
        delete[] m_events;
    }

    // Move constructor
    Logger::Logger(Logger&& other) noexcept 
        : m_events(other.m_events), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.m_events = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move assignment
    Logger& Logger::operator=(Logger&& other) noexcept {
        if (this != &other) {
            delete[] m_events;

            m_events = other.m_events;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_events = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    // Resize the dynamic array
    void Logger::resize(size_t new_capacity) {
        Event* new_array = new Event[new_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            new_array[i] = m_events[i];
        }
        delete[] m_events;
        m_events = new_array;
        m_capacity = new_capacity;
    }

    // Add an event to the log
    void Logger::addEvent(const Event& event) {
        if (m_size == m_capacity) {
            resize((m_capacity == 0) ? 2 : m_capacity * 2);
        }
        m_events[m_size++] = event;
    }

    // Output all logged events
    std::ostream& operator<<(std::ostream& out, const Logger& logger) {
        for (size_t i = 0; i < logger.m_size; ++i) {
            out << logger.m_events[i] << std::endl;
        }
        return out;
    }

} // namespace seneca
