

#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>

namespace seneca {

    // Helper function to parse PartOfSpeech from a string
    PartOfSpeech Dictionary::parsePartOfSpeech(const std::string& pos) const {
        std::string lower_pos = pos;
        std::transform(lower_pos.begin(), lower_pos.end(), lower_pos.begin(), ::tolower);

        if (lower_pos == "n." || lower_pos == "n. pl.") return PartOfSpeech::Noun;
        if (lower_pos == "adv.") return PartOfSpeech::Adverb;
        if (lower_pos == "a.") return PartOfSpeech::Adjective;
        if (lower_pos == "prep.") return PartOfSpeech::Preposition;
        if (lower_pos == "pron.") return PartOfSpeech::Pronoun;
        if (lower_pos == "conj.") return PartOfSpeech::Conjunction;
        if (lower_pos == "interj.") return PartOfSpeech::Interjection;
        if (lower_pos == "v." || lower_pos == "v. i." || lower_pos == "v. t." || lower_pos == "v. t. & i.") {
            return PartOfSpeech::Verb;
        }

        return PartOfSpeech::Unknown;
    }

    // Default constructor
    Dictionary::Dictionary() = default;

    // Constructor to load dictionary from file
    Dictionary::Dictionary(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << '\n';
            return;
        }

        std::string line;
        size_t count = 0;

        // First, count the number of valid lines (words)
        while (std::getline(file, line)) {
            if (!line.empty()) ++count;
        }

        // Allocate exact memory needed
        m_size = count;
        m_words = new Word[m_size];

        file.clear();
        file.seekg(0);

        // Populate the array
        size_t index = 0;
        while (std::getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            if (pos1 == std::string::npos || pos2 == std::string::npos) {
                continue; // Skip malformed lines
            }

            m_words[index].m_word = line.substr(0, pos1);
            m_words[index].m_pos = parsePartOfSpeech(line.substr(pos1 + 1, pos2 - pos1 - 1));
            m_words[index].m_definition = line.substr(pos2 + 1);
            ++index;
        }
    }

    // Copy constructor
    Dictionary::Dictionary(const Dictionary& other) {
        m_size = other.m_size;
        m_words = new Word[m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_words[i] = other.m_words[i];
        }
    }

    // Move constructor
    Dictionary::Dictionary(Dictionary&& other) noexcept {
        m_size = other.m_size;
        m_words = other.m_words;
        other.m_size = 0;
        other.m_words = nullptr;
    }

    // Copy assignment operator
    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            delete[] m_words;
            m_size = other.m_size;
            m_words = new Word[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_words[i] = other.m_words[i];
            }
        }
        return *this;
    }

    // Move assignment operator
    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            delete[] m_words;
            m_size = other.m_size;
            m_words = other.m_words;
            other.m_size = 0;
            other.m_words = nullptr;
        }
        return *this;
    }

    // Destructor
    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    // SearchWord for defining the type.
    void Dictionary::searchWord(const char* word) const {
        bool found = false;

        for (size_t i = 0; i < m_size; i++) {
            if (m_words[i].m_word == word) { 
                if (!found) {
                    std::cout << m_words[i].m_word << " - ";
                    found = true;
                } else {
                    std::cout << std::setw(m_words[i].m_word.length() + 3) << " - ";
                }

                // Print part of speech if verbose is enabled
                if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    std::cout << "(";
                    printPartOfSpeech(m_words[i].m_pos);  // Print the part of speech
                    std::cout << ") ";
                }

                // Print the definition
                std::cout << m_words[i].m_definition << std::endl;

                // If we're only showing the first definition, return after printing
                if (!g_settings.m_show_all) return;
            }
        }

        // If the word wasn't found, print an error message
        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }

    // Function to print part of speech
    void Dictionary::printPartOfSpeech(const PartOfSpeech& pos) const {
        switch (pos) {
        case PartOfSpeech::Noun: std::cout << "noun"; break;
        case PartOfSpeech::Adjective: std::cout << "adjective"; break;
        case PartOfSpeech::Adverb: std::cout << "adverb"; break;
        case PartOfSpeech::Verb: std::cout << "verb"; break;
        case PartOfSpeech::Preposition: std::cout << "preposition"; break;
        case PartOfSpeech::Pronoun: std::cout << "pronoun"; break;
        case PartOfSpeech::Conjunction: std::cout << "conjunction"; break;
        case PartOfSpeech::Interjection: std::cout << "interjection"; break;
        default: std::cout << "unknown"; break;
        }
    }

} // namespace seneca
