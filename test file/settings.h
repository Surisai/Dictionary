
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <string>

namespace seneca {

    struct Settings {
        bool m_show_all = false;        // Show all definitions if true
        bool m_verbose = false;         // Print part of speech if true
        std::string m_time_units = "nanoseconds"; // Time unit for durations
    };

    // Global settings variable
    extern Settings g_settings;

} // namespace seneca

#endif // SENECA_SETTINGS_H
