
#include "event.h"
#include "settings.h"

#include <iomanip>


namespace seneca {

std::ostream& operator<< (std::ostream& out, const Event& event) {
    static int count = 0;  // Counter for the number of times operator<< is called
    out << std::setw(2) << ++count << ": "
        << std::setw(40) << event.m_name << " -> ";

    std::string u = g_settings.m_time_units;
    int width = 0;

    if (u == "seconds") {
        const std::chrono::seconds duration =
            std::chrono::duration_cast<std::chrono::seconds>(event.m_duration);
        width = 2;
        out << std::setw(width) << duration.count() << " " << u;
    }
    else if (u == "milliseconds") {
        const std::chrono::milliseconds duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(event.m_duration);
        width = 5;
        out << std::setw(width) << duration.count() << " " << u;
    }
    else if (u == "microseconds") {
        const std::chrono::microseconds duration =
            std::chrono::duration_cast<std::chrono::microseconds>(event.m_duration);
        width = 8;
        out << std::setw(width) << duration.count() << " " << u;
    }
    else {
        width = 11;
        out << std::setw(width) << event.m_duration.count() << " nanoseconds";
    }

    return out;
}
}