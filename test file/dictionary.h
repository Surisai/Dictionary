f SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>

namespace seneca {

    // Enum for PartOfSpeech
    enum class PartOfSpeech {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection
    };

    // Structure to store word details (word, part of speech, and definition)
    struct Word {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary {
    private:
        Word* m_words = nullptr;  // Array to hold the words in the dictionary
        size_t m_size = 0;        // The current size (number of words)
        size_t m_count = 0;       // The number of words in the dictionary

        // Private helper functions
        PartOfSpeech parsePartOfSpeech(const std::string& pos) const;
        void printPartOfSpeech(const PartOfSpeech& pos) const;

    public:
        // Constructors and Destructor
        Dictionary();
        Dictionary(const char* filename);
        Dictionary(const Dictionary& other);  // Copy constructor
        Dictionary(Dictionary&& other) noexcept;  // Move constructor
        ~Dictionary();

        // Assignment operators
        Dictionary& operator=(const Dictionary& other);  // Copy assignment
        Dictionary& operator=(Dictionary&& other) noexcept;  // Move assignment

        // Public methods
        void searchWord(const char* word) const;
        size_t size() const { return m_size; }  // Get the number of words in the dictionary
    };

    // Function to print part of speech (e.g., Noun, Verb, etc.)
    void printPartOfSpeech(const PartOfSpeech& pos);

} // namespace seneca

#endif // SENECA_DICTIONARY_H
