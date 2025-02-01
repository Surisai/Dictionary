# Dictionary
a dictionary application -practice searching word on dictionary file to handle -in csv format
Dictionary Application Overview

This application is designed to load a list of words from a CSV file (comma-separated values), store them in memory, and perform various operations on them. It also measures the time taken for specific operations, allowing users to compare their performance across different tasks. While the operation times will vary depending on the hardware the application is run on, the relative differences in performance between different operations should remain consistent across systems.

The input CSV file will contain a large number of records, each represented on a single line with the following format:

arduino
Copy
word,pos,definition
Where:

word: The word being defined (may contain spaces).
pos: The part of speech (such as noun, verb, etc.).
definition: The word's definition.
Global Variables, Functions, and Types

All global variables, functions, operators, and types should be encapsulated within the seneca namespace.

Modules Overview

tester_1 Module (Provided):

This module should not be modified! Study and understand its code to grasp the expected behavior.
settings Module:

This module handles the application configuration.
Create a Settings structure that contains public data members and no member functions. Declare a global variable g_settings of this type in the header and define it in the implementation file.
Public Members:

m_show_all: A boolean flag. If true, the application will display all definitions for a word; otherwise, only the first definition will be shown (default: false).
m_verbose: A boolean flag. If true, the application will display the part of speech for a word (default: false).
m_time_units: A string attribute that stores the time units to be used when displaying operation durations. Possible values include seconds, milliseconds, microseconds, or nanoseconds (default: nanoseconds).
event Module:

The Event class stores information about a single event during the program’s execution. It should store the event name (as a string) and its duration (as a std::chrono::nanoseconds object).
Public Members:

Default constructor.
Event(const char* name, const std::chrono::nanoseconds& duration): Initializes the event with the given name and duration.
Friend Helpers:

operator<<: This operator outputs the event in the following format:
makefile
Copy
COUNTER: EVENT_NAME -> DURATION TIME_UNITS
Where:
COUNTER is a right-aligned field of size 2, representing the number of times this operator has been called (tracked locally within the function).
EVENT_NAME is the right-aligned event name with a width of 40 characters.
DURATION is a right-aligned field representing the event's duration.
TIME_UNITS is the string representing the chosen time units.
logger Module:

The Logger class manages a dynamically allocated collection of events, stored as an array.
Public Members:

Default constructor.
Destructor.
Move operations for handling ownership of the event array.
void addEvent(const Event& event): Adds a copy of the provided event to the array, resizing it if necessary.
Friend Helpers:

operator<<: This operator outputs all events stored in the logger in the following format:
python-repl
Copy
EVENT
EVENT
...
timeMonitor Module:

The TimeMonitor class helps measure the duration of various operations or events using the chrono library.
Public Members:

void startEvent(const char* name): Starts a new event, recording the current time and associating it with the event name.
Event stopEvent(): Stops the current event, calculates its duration, and returns an Event object.
dictionary Module:

This module handles the dictionary of words.
Types:

enum class PartOfSpeech: Defines various parts of speech such as Noun, Verb, Adjective, etc.
struct Word: Stores word information, including the word itself, its part of speech, and its definition.
Dictionary Class:

The Dictionary class manages a dynamically allocated array of Word objects.
Public Members:

Default constructor.
Dictionary(const char* filename): Loads words from the specified CSV file, allocating memory for them and parsing the entries. If the file can't be opened, the dictionary remains empty.
void searchWord(const char* word): Searches for a word in the dictionary. If found, the definitions are displayed based on the settings in g_settings. If the word is not found, an error message is shown.
Part of Speech Parsing:

Only the following values are considered valid parts of speech:
n. or n. pl. → Noun
adv. → Adverb
a. → Adjective
v. or v. i. or v. t. or v. t. & i. → Verb
prep. → Preposition
pron. → Pronoun
conj. → Conjunction
interj. → Interjection
Any other value is considered PartOfSpeech::Unknown.
Sample Output:

The input files english_large.csv and english_small.csv are provided.
When the program is run with the following command:
nginx
Copy
asgn english_large.csv english_small.csv
The output should resemble the sample output, which includes performance timing comparisons.
Important Notes:

The execution times will vary depending on when and where the program is run, but the relative differences in times between operations should be noticeable (e.g., move operations being much faster than copy operations).
Additional Information:

The application will produce different timing results on different systems, but the relative performance should be consistent.
The goal is to achieve significantly faster performance with move operations compared to copy operations.
