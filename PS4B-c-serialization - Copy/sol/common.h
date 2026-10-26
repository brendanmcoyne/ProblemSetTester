#ifndef WORD_DEFINED
#define WORD_DEFINED

struct word {
    char word[100]; // BUG: purposefully make this too small
    char* definition;
    char* thesaurus; // will need to add this field
    struct word* next_word;
};

#endif