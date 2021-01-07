#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"

using namespace std;

/* insert your function definitions here */

// I) MAIN FUNCTIONS
int tile_score(char tile){
    char letter = toupper(tile);
    int score;
    switch (letter){
        // Letters with score 1
        case 'A':
        case 'E':
        case 'I':
        case 'L':
        case 'N':
        case 'O':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
            score = 1;
            break;
        // Letters with score 2
        case 'D':
        case 'G':
            score = 2;
            break;
        // Letters with score 3
        case 'B':
        case 'C':
        case 'M':
        case 'P':
            score = 3;
            break;
        // Letters with score 4
        case 'F':
        case 'H':
        case 'V':
        case 'W':
        case 'Y':
            score = 4;
            break;
        // Letters with score 5
        case 'K':
            score = 5;
            break;
        // Letters with score 8
        case 'J':
        case 'X':
            score = 8;
            break;
        // Letters with score 10
        case 'Q':
        case 'Z':
            score = 10;
            break;
        // Blank tiles
        case '?':
        case ' ':
            score = 0;
            break;
        // Other
        default:
            score = -1;
            break;
    }
    return score;
}

bool can_form_word_from_tiles(const char* word, const char* tiles, 
    char* played_tiles){
    
    // Cleaning
    clean_char_array(played_tiles);
    
    // Auxiliar Variable and Initialization
    int available_tiles = strlen(tiles);
    int used_letters = 0;
    char* tiles_in_hand = new char[available_tiles];
    strcpy(tiles_in_hand, tiles);
    
    // Look is there is a possible word to form
    if(word_solver(word, tiles_in_hand, played_tiles, used_letters))
        return true;
    return false;

}

int compute_score(const char* played_tiles, 
    const ScoreModifier* score_modifiers){
    
    int score = 0;
    int bonus = (strlen(played_tiles)==7) ? 50 : 0;
    int letter_multipliyer;
    int word_multipliyer=1;
    for(int i=0; played_tiles[i] != '\0'; i++){
        
        if(score_modifiers[i] == NONE)
            letter_multipliyer = 1;
        else if(score_modifiers[i] == DOUBLE_LETTER_SCORE)
            letter_multipliyer = 2;
        else if(score_modifiers[i] == TRIPLE_LETTER_SCORE)
            letter_multipliyer = 3;
        else if(score_modifiers[i] == DOUBLE_WORD_SCORE)
            word_multipliyer *= 2;
        else if(score_modifiers[i] == TRIPLE_WORD_SCORE)
            word_multipliyer *= 3;
        
        // Get Score considering letter multipliyers
        score += tile_score(played_tiles[i])*letter_multipliyer;
        
    }
    // Update Score considering word multipliyers
    score = score*word_multipliyer;
    // Update Score considering bonus (7 letters used)
    score += bonus;

    return score;

}

int highest_scoring_word_from_tiles(const char* tiles, 
    const ScoreModifier* score_modifiers, char* word){

    int max_score = -1;
    
    int current_score = 0;
    char word_with_highest_score[512];
    std::ifstream in;
    char reader[512];
    
    in.open("words.txt");
    if (!in)
        return max_score;

    while(!in.eof()){
        in >> reader;
        if(can_form_word_from_tiles(reader,tiles,word)){
            current_score = compute_score(word,score_modifiers);
            if(max_score < current_score){
                max_score = current_score;
                strcpy(word_with_highest_score,reader);
            }
        }
    }
    in.close();
  
    strcpy(word,word_with_highest_score);
    return max_score;

}


// II) AUXILIOAR FUNCTIONS
bool word_solver(const char* word, char* tiles_in_hand, char* played_tiles, 
    int used_letters){
    
    // Auxilair variables
    char temp;
    
    // Base Case -> All available tiles were used
    if(used_letters == strlen(word))
        return false;
    
    // Recursive case -> Backtracking Solution
    for(int i = 0; tiles_in_hand[i] != '\0'; i++){
        
        // Temp variable for saving tile which is going to be tried
        temp = tiles_in_hand[i];
        
        // Try a tile in our hand and save that in our played_tiles array
        played_tiles[used_letters] = tiles_in_hand[i];
        
        // Update used_letters and titles_in_hand
        used_letters++;
        remove_letter_at_index(tiles_in_hand,i);
        
        // Check if a solution is found
        if(is_match(word,played_tiles))
            return true;

        // Use backtracking algorithm to find a valid solution (recursion).
        if(word_solver(word, tiles_in_hand, played_tiles, used_letters)){
            return true;
        }
        
        // If solution is not founded with previuos asumptions, reverse changes
        get_back_letter_at_index(tiles_in_hand,i,temp);
        used_letters--;
    
   }
   
   // If no solution is found. Return false
   return false;
}

bool is_match(const char* word, const char* played_tiles){
    
    if(strlen(word) != strlen(played_tiles))
        return false;
    for (int i = 0; word[i]!='\0'; i++){
        if(word[i] != played_tiles[i]){
            if(played_tiles[i] != '?' && played_tiles[i] != ' ')
                return false;
        }
    }
    return true;
}

void remove_letter_at_index(char* string, int index){
    int i = index;
    while(i < strlen(string)){
        string[i] = string[i+1];
        i++;
    }
    string[i]='\0';
}

void get_back_letter_at_index(char* string, int index, char letter){
    int i = strlen(string)+1;
    string[i]='\0';
    while(i >= index){
        string[i] = string[i-1];
        i--;
    }
    string[index] = letter;
}

bool word_exist_in_dictionary(const char *word){

  std::ifstream in;
  char reader[512];
  in.open("words.txt");
  if (!in)
    return false;
  while(!in.eof()){
    in >> reader;
    if(strcmp(reader,word)==0){
      return true;
    }
  }
  in.close();
  return false;

}

// void get_array_possible_words(const char* tiles, char* possible_words[]){

// }


// void permute(char* string, int starting_index, int ending_index) 
// { 

// } 
 

// int get_number_possible_permutations(const char* tiles){
    
//     int number_of_letters = strlen(tiles);
//     int number_of_permutations = 0;
    
//     // Permutation formula -> n!/(n!-k!)
//     int n_fact = factorial(number_of_letters);
//     int n_k_fact;
//     for (int i = 1; i < number_of_letters; i++){
//         n_k_fact = factorial(number_of_letters-i);
//         number_of_permutations += n_fact/(n_k_fact);
//     }

//     return number_of_permutations;
// }

// int factorial(int n){
    
//     if(n == 0)
//         return 1;
//     else
//         return n*factorial(n-1);
// }

void clean_char_array(char *array){
  for(int i=0; array[i]!='\0'; i++){
    array[i] = '\0';
  }
}