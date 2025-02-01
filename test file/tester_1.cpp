#include <iostream>
#include <iomanip>
#include <fstream>  // For writing to a file
#include "dictionary.h"
#include "dictionary.h"      // intentional
#include "settings.h"
#include "settings.h"        // intentional
#include "timeMonitor.h"
#include "timeMonitor.h"     // intentional
#include "logger.h"
#include "logger.h"          // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_DICTIONARY_H
    #error "The header guard for 'dictionary.h' doesn't follow the convention!"
#endif
#ifndef SENECA_SETTINGS_H
    #error "The header guard for 'settings.h' doesn't follow the convention!"
#endif
#ifndef SENECA_TIMEMONITOR_H
    #error "The header guard for 'timeMonitor.h' doesn't follow the convention!"
#endif
#ifndef SENECA_EVENT_H
    #error "The header guard for 'event.h' doesn't follow the convention!"
#endif
#ifndef SENECA_LOGGER_H
    #error "The header guard for 'logger.h' doesn't follow the convention!"
#endif


int main(int argc, char** argv)
{
    // Open the output file for writing
    std::ofstream outputFile("output.txt");
    if (!outputFile) {
        std::cerr << "Error: Could not open output file for writing!" << std::endl;
        return 1;  // Exit with error if the file can't be opened
    }

    // Write the command line arguments to the output file
    outputFile << "Command Line:\n";
    outputFile << "------------------------------------------------------\n";
    for (int i = 0; i < argc; ++i)
        outputFile << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    outputFile << "------------------------------------------------------\n\n";

    seneca::Logger log;
    seneca::TimeMonitor timer;

    // TEST: Default Constructor
    {
        timer.startEvent("Default Constructor");
        seneca::Dictionary dict;
        log.addEvent(timer.stopEvent());
    }

    // TEST: Custom Constructor
    timer.startEvent("Custom Constructor");
    seneca::Dictionary dict(argv[1]);
    log.addEvent(timer.stopEvent());

    seneca::g_settings.m_verbose = true;
    seneca::g_settings.m_show_all = true;

    // TEST: Search functionality
    outputFile << "T1: Search for some words\n";
    outputFile << "==========:==========:==========:==========:==========\n";
    dict.searchWord("Computer", outputFile);
    dict.searchWord("Zigzag", outputFile);
    dict.searchWord("Apple", outputFile);
    dict.searchWord("Germanize", outputFile);
    dict.searchWord("Passport", outputFile);
    dict.searchWord("Gone", outputFile);
    dict.searchWord("Laptop", outputFile);
    outputFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    seneca::g_settings.m_show_all = false;
    seneca::g_settings.m_verbose = false;

    // TEST: Copy Constructor
    outputFile << "T2: Copy Constructor\n";
    outputFile << "==========:==========:==========:==========:==========\n";
    timer.startEvent("Copy Constructor");
    seneca::Dictionary dict2 = dict;
    log.addEvent(timer.stopEvent());

    dict.searchWord("Apple", outputFile);
    dict2.searchWord("Ywis", outputFile);
    outputFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    // TEST: Copy Assignment Operator
    outputFile << "T3: Copy Assignment Operator\n";
    outputFile << "==========:==========:==========:==========:==========\n";
    {
        // check for self assignment
        seneca::Dictionary& alias = dict;
        dict = alias; // crash here if copy assignment is incorrectly implemented
    }

    seneca::Dictionary dict3(argv[2]);
    dict3.searchWord("Efficience", outputFile);

    timer.startEvent("Copy Assignment Operator");
    dict3 = dict;
    log.addEvent(timer.stopEvent());

    dict.searchWord("Apple", outputFile);
    dict3.searchWord("Ywis", outputFile);
    outputFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    // TEST: Move Constructor
    outputFile << "T4: Move Constructor\n";
    outputFile << "==========:==========:==========:==========:==========\n";

    seneca::Dictionary dict1 = dict;  // make a copy of the big dictionary
    timer.startEvent("Move Constructor");
    seneca::Dictionary dict4 = std::move(dict1);
    log.addEvent(timer.stopEvent());

    dict1.searchWord("Apple", outputFile);
    dict4.searchWord("Ywis", outputFile);
    outputFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    // TEST: Move Assignment Operator
    outputFile << "T5: Move Assignment Operator\n";
    outputFile << "==========:==========:==========:==========:==========\n";

    {
        // check for self assignment
        seneca::Dictionary& alias = dict;
        dict = std::move(alias);  // crash here if move assignment is incorrectly implemented
    }

    seneca::Dictionary dict5(dict);
    seneca::Dictionary dict6(argv[2]);
    dict6.searchWord("Efficience", outputFile);

    timer.startEvent("Move Assignment Operator");
    dict6 = std::move(dict5);
    log.addEvent(timer.stopEvent());

    dict5.searchWord("Apple", outputFile);
    dict6.searchWord("Ywis", outputFile);
    outputFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    // Measure time for destructor
    timer.startEvent("Destructor");
    log.addEvent(timer.stopEvent());

    // TEST: Search time measurements
    outputFile << "T6: Search Time Measurements\n";
    outputFile << "==========:==========:==========:==========:==========\n";

    seneca::g_settings.m_show_all = false;
    timer.startEvent("Search for a word (first occurence)");
    dict.searchWord("Apple", outputFile);
    log.addEvent(timer.stopEvent());

    seneca::g_settings.m_show_all = true;
    timer.startEvent("Search for a word (all occurences)");
    dict.searchWord("Apple", outputFile);
    log.addEvent(timer.stopEvent());

    outputFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    // Output final log information
    outputFile << '\n' << log;
    seneca::g_settings.m_time_units = "microseconds";
    outputFile << '\n' << log;
    seneca::g_settings.m_time_units = "milliseconds";
    outputFile << '\n' << log;
    seneca::g_settings.m_time_units = "seconds";
    outputFile << '\n' << log;

    // Close the output file
    outputFile.close();

    return 0;
}
