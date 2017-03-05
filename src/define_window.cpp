
#include "define_window.h"
#include "grid_entry.h"
#include "str_utils.h"
#include <algorithm>
#include <iostream>
#include <gtkmm/messagedialog.h>
#include <gtkmm/orientable.h>

/**
  * Constructor
  */
DefineWindow::DefineWindow() :
  // Initialize the buttons
  m_label_lang("Insert the symbols of the language (separted by ' , ')"),
  m_label_states("Insert the states of the DFA"),
  m_button_add("Add another state"),
  m_button_final_states("Select Final states"),
  m_button_states_table("Add transition table"),
  m_button_validate("Validate words"),
  m_button_quit("Close") {
  
  // Initialize the window
  set_title("DFA Validation app");
  // Sets the border width of the window.
  set_border_width(25);
  set_resizable(false);

  this->final_states_window = NULL;
  this->states_table_window = NULL;
  this->validate_window = NULL;

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_states.set_row_spacing(10);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  m_grid_states.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up the widgets of the top level grid
  add(m_grid_top);
  m_grid_top.add(m_label_lang);
  m_grid_top.add(m_entry_lang);
  m_grid_top.add(m_label_states);
  m_grid_top.add(m_grid_states);
  m_grid_top.add(m_button_add);
  m_grid_top.add(m_button_final_states);
  m_grid_top.add(m_button_states_table);
  m_grid_top.add(m_button_validate);
  m_grid_top.add(m_button_quit);

  // Add two empty states
  add_state();
  add_state();

  // Connect the signals
  // Add new state
  m_button_add.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::add_state
    )
  );

  // Final states
  m_button_final_states.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_final_states_clicked
    )
  );
  
  // State transition table
  m_button_states_table.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_states_table_clicked
    )
  );


  // Validate word
  m_button_validate.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_validate_clicked
    )
  );

  // Quit
  m_button_quit.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_quit_clicked
    )
  );

  // Display everything
  show_all_children();
}

/**
  * Destructor
  */
DefineWindow::~DefineWindow() { }

/**
  * Validate that there are no empty states within
  * the entries (text inputs)
  */
bool DefineWindow::states_are_valid() {
  auto states = get_states();
  
  return std::any_of(
    states.begin(),
    states.end(),
    [](std::string state) {
      return (state.length() != 0);
    }
  );
}

/**
  * Get the string values of the states entered by the user.
  * Returns a string vector.
  */
std::vector<std::string> DefineWindow::get_states() {
  auto children = this->m_grid_states.get_children();
  std::vector<std::string> states;

   for (Gtk::Widget* elem : children) {
    GridEntry* state = (GridEntry*) elem;
    states.push_back(state->get_entry_text());
  }

  // Because of the way Gtk retreives the child elements, the last
  // widget added is the first retreived.
  // Therefore, to have the states in correct order, the list has to
  // be reversed
  std::reverse(states.begin(), states.end());

  return states;
}

/**
  * Adds a new entry to create a new empty state
  */
void DefineWindow::add_state() {
  GridEntry* entry = Gtk::manage(new GridEntry(&m_grid_states));
  this->m_grid_states.add(*entry);
  this->m_grid_states.show_all_children();
}

/**
  * Callback executed when the final states button is clicked
  * Validates that there are at least two states and that all of
  * them are valid.
  * 
  * If all is good, shows the final states window; otherwise,
  * shows an error dialog.
  */
void DefineWindow::on_final_states_clicked() {
  auto children = this->m_grid_states.get_children();
  Gtk::MessageDialog dialog(*this, "Error");

  // Check the number of states
  if (children.size() <= 1) {
    dialog.set_secondary_text("Please add at least two states");
    dialog.run();
  // Check that the states are valid
  } else if (!states_are_valid()) {
    dialog.set_secondary_text("Please fix the empty state(s)");
    dialog.run();
  } else {
    // Set the automaton states
    this->automaton.set_states(get_states());
    
    // Create and show the FS window
    final_states_window = new FinalStatesWindow(&this->automaton);    
    final_states_window->show();
  }
}

/**
  * Callback executed when the transition table button is clicked
  * Validates that there are at least two states and that all of
  * them are valid. Also, checks that the DFA has at least one
  * final state and two letters on the alphabet.
  * 
  * If all is good, shows the transition table window; otherwise,
  * shows an error dialog.
  */
void DefineWindow::on_states_table_clicked() {
  auto children = this->m_grid_states.get_children();
  Gtk::MessageDialog dialog(*this, "Error");

  // Check the number of states
  if (children.size() <= 1) {
    dialog.set_secondary_text("Please add at least two states");
    dialog.run();
  // Check that the states are valid
  } else if (!states_are_valid()) {
    dialog.set_secondary_text("Please fix the empty state(s)");
    dialog.run();
  // Check that the DFA has at least one final state
  } else if (this->automaton.get_final_states().size() < 1) {
    dialog.set_secondary_text("Please select at least one final state");
    dialog.run();
  // Check that the alphabet has at least two letters
  } else if (split(this->m_entry_lang.get_text(), ',').size() < 2) {
    dialog.set_secondary_text("Please insert at least two letters to the alphabet");
    dialog.run();
  } else {
    // Get the alphabet
    std::vector<std::string> alphabet = split(this->m_entry_lang.get_text(), ',');
    this->automaton.set_alphabet(alphabet);

    // Create and shwo the TT window
    states_table_window = new StatesTableWindow(&this->automaton);    
    states_table_window->show();
  }
}

/**
  * Callback executed when the validate button is clicked
  * Validates that there are at least two states and that all of
  * them are valid. Checks that the DFA has at least one
  * final state and two letters on the alphabet, and, also, that
  * the transition table is not empty
  * 
  * If all is good, shows the transition table window; otherwise,
  * shows an error dialog.
  */
void DefineWindow::on_validate_clicked() {
  auto children = this->m_grid_states.get_children();
  Gtk::MessageDialog dialog(*this, "Error");

  // Check the number of states
  if (children.size() <= 1) {
    dialog.set_secondary_text("Please add at least two states");
    dialog.run();
  // Check that the states are valid
  } else if (!states_are_valid()) {
    dialog.set_secondary_text("Please fix the empty state(s)");
    dialog.run();
  // Check that the DFA has at least one final state
  } else if (this->automaton.get_final_states().size() < 1) {
    dialog.set_secondary_text("Please select at least one final state");
    dialog.run();
  // Check that the alphabet has at least two letters
  } else if (split(this->m_entry_lang.get_text(), ',').size() < 2) {
    dialog.set_secondary_text("Please insert at least two letters to the alphabet");
    dialog.run();
  // Check that the transition table is not empty
  } else if (this->automaton.get_transitions().empty()) {
    dialog.set_secondary_text("Please fill the transition table");
    dialog.run();
  } else {
    // Create and show the VW window
    validate_window = new ValidateWindow(&this->automaton);    
    validate_window->show();
  }
}

/**
  * Callback executed when the quit button is clicked
  * 
  * Exits the program
  */
void DefineWindow::on_quit_clicked() {
  hide();
}
