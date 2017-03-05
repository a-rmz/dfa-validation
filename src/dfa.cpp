
#include "dfa.h"
#include <algorithm>
#include <unordered_map>

/**
  * Constructor
  */
DFA::DFA() {}

/**
  * Destructor
  */
DFA::~DFA() {}

/**
  * Getter: States
  */
std::vector<std::string> DFA::get_states() {
  return this->states;
};

/**
  * Getter: Final states
  */
std::vector<std::string> DFA::get_final_states() {
  return this->final_states;
};

/**
  * Getter: alphabet
  */
std::vector<std::string> DFA::get_alphabet() {
  return this->alphabet;
};

/**
  * Getter: Transition table
  */
std::unordered_map<std::string, std::string> DFA::get_transitions() {
  return this->state_transition_table;
}

/**
  * Setter: States
  */
void DFA::set_states(std::vector<std::string> states) {
  this->states = states;
};

/**
  * Setter: Final states
  */
void DFA::set_final_states(std::vector<std::string> final_states) {
  this->final_states = final_states;
};

/**
  * Setter: alphabet
  */
void DFA::set_alphabet(std::vector<std::string> alphabet) {
  this->alphabet = alphabet;
};

/**
  * Check if a given state is a final state
  */
bool DFA::is_final_state(std::string state) {
  // If the iterator returned is different to the end,
  // a final state was found
  return std::find(
    this->final_states.begin(),
    this->final_states.end(),
    state
  ) != this->final_states.end();
};

/**
  * Add a new transition to the transition table. This is the most important
  * part of the DFA, this is what creates the transition table which determines
  * the value of a word.
  *
  */
void DFA::add_transition(std::string state, std::string letter, std::string next) {
  // Create the key concatenating the current state and the current letter
  std::string key = state + letter;
  // Add the key to the table with the next state as value
  this->state_transition_table[key] = next;
}

/**
  * Clears the content of the transition table
  */
void DFA::reset_transition_table() {
  this->state_transition_table.clear();
}

/**
  * Determines if a given word is valid for the DFA.
  * Iterates through the characters of the word, and swipes
  * the transition table going from one state to the next concatenating
  * the consumed char with the state retreived from the transition table.
  *
  * Lastly, checks if the last retreived state is a final state.
  */
bool DFA::is_word_valid(std::string word) {
  // Gets the first state
  std::string current_state = this->states.at(0);
  
  // Iterate through the word
  for(int i = 0; i < word.length(); i++) {
    // Get the current char (as string)
    std::string current_char = std::string(1, word.at(i));
    // Create the key of the current state
    std::string current_key = current_state + current_char;
    // Retreive the next state from the transition table
    current_state = this->state_transition_table[current_key];
  }

  // Return the value of the last state
  return is_final_state(current_state);
}