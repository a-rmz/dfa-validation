
#include "dfa.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>
DFA::DFA() {
  
}

DFA::~DFA() {}

std::vector<std::string> DFA::get_states() {
  return this->states;
};

std::vector<std::string> DFA::get_final_states() {
  return this->final_states;
};

std::vector<std::string> DFA::get_alphabet() {
  return this->alphabet;
};

void DFA::set_states(std::vector<std::string> states) {
  this->states = states;
};

void DFA::set_final_states(std::vector<std::string> final_states) {
  this->final_states = final_states;
};

void DFA::set_alphabet(std::vector<std::string> alphabet) {
  this->alphabet = alphabet;
};

bool DFA::is_final_state(std::string state) {
  return std::find(
    this->final_states.begin(),
    this->final_states.end(),
    state
  ) != this->final_states.end();
};

void DFA::create_keys() {
  std::vector<std::string> keys;
  for(std::string state : this->states) {
    for(std::string letter : this->alphabet) {
      keys.push_back(state + letter);
    }
  }
  this->keys = keys;
}

void DFA::add_transition(std::string state, std::string letter, std::string next) {
  std::string key = state + letter;
  this->state_transition_table[key] = next;
}

bool DFA::is_word_valid(std::string word) {
  std::string current_state = this->states.at(0);
  
  for(int i = 0; i < word.length(); i++) {
    std::string current_char = std::string(1, word.at(i));
    std::string current_key = current_state + current_char;
    current_state = this->state_transition_table[current_key];
  }

  return is_final_state(current_state);
}