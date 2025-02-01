
#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include <chrono>
#include <string>
#include "event.h"

namespace seneca{
    class TimeMonitor {
        std::string m_eventName;
        std::chrono::steady_clock::time_point m_start;// Start time of the current event
    public:
    //Start an event by recording its name and records the time when the event started and the name of the event.
        void startEvent(const char* name);
    //Stop the event by recording the time when the event stopped and the name of the event.
        Event stopEvent();
    };
}
#endif//SENECA_TIMEMONITOR_H