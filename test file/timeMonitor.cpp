
#include "timeMonitor.h"


namespace seneca{
    //start an event by recording its name and start time
  void TimeMonitor::startEvent(const char* name){
    m_eventName = name;
    m_start = std::chrono::steady_clock::now(); //record the time
  }  

  //stop the event and result an event object with its name and duration
 Event TimeMonitor::stopEvent() {
    auto end = std::chrono::steady_clock::now();                                // Record the end time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_start); // Calculate the duration
    return Event(m_eventName.c_str(), duration);                                // Return the event
}

}
