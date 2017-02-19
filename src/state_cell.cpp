
#include "state_cell.h"

StateCell::StateCell(std::vector<std::string> states, int current_state, std::string letter) {
  set_state(states.at(current_state));
  set_letter(letter);
  
  for (std::string state : states) {
    append(state);
  }
};

StateCell::~StateCell() {};

void StateCell::set_state(std::string state) {
  this->state = state;
}

void StateCell::set_letter(std::string letter) {
  this->letter = letter;
}

std::string StateCell::get_state() {
  return this->state;
}

std::string StateCell::get_letter() {
  return this->letter;
}

std::string StateCell::get_key() {
  return this->state + this->letter;
}