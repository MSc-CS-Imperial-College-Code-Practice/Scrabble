enum ScoreModifier { 
    NONE, 
    DOUBLE_LETTER_SCORE, 
    TRIPLE_LETTER_SCORE, 
    DOUBLE_WORD_SCORE, 
    TRIPLE_WORD_SCORE
};

/* insert your function prototypes here */

// I) MAIN PROBLEM FUNCTIONS
int tile_score(char tile);
bool can_form_word_from_tiles(const char* word, const char* tiles, 
    char* played_tiles);
int compute_score(const char* played_tiles, 
    const ScoreModifier* score_modifiers);
int highest_scoring_word_from_tiles(const char* tiles, 
    const ScoreModifier* score_modifiers, char* word);


// II) AUXILIAR FUNCTIONS
bool word_exist_in_dictionary(const char *word);
bool word_solver(const char* word, char* tiles_in_hand, char* played_tiles, 
    int used_letters);
bool is_match(const char* word, const char* played_tiles);
void remove_letter_at_index(char* string, int index);
void get_back_letter_at_index(char* string, int index, char letter);
void clean_char_array(char *array);