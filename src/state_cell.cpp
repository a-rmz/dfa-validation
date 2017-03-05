
#include "state_cell.h"

/**
  * Constuctor
  */
StateCell::StateCell(std::vector<std::string> states, int current_state, std::string letter) {
  // Set the current state to the matching
  set_state(states.at(current_state));
  // Set the current letter
  set_letter(letter);
  
  // Append all the states to the ComboBox list
  for (std::string state : states) {
    append(state);
  }
};

/**
  * Destuctor
  */
StateCell::~StateCell() {};

/**
  * Getter: Current state
  */
std::string StateCell::get_state() {
  return this->state;
}

/**
  * Getter: Current letter
  */
std::string StateCell::get_letter() {
  return this->letter;
}

/**
  * Getter: Current key
  */
std::string StateCell::get_key() {
  return this->state + this->letter;
}

/**
  * Setter: Current state
  */
void StateCell::set_state(std::string state) {
  this->state = state;
}

/**
  * Setter: Current letter
  */
void StateCell::set_letter(std::string letter) {
  this->letter = letter;
}
