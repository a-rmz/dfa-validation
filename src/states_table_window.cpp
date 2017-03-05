
#include "dfa.h"
#include "state_cell.h"
#include "states_table_window.h"
#include <gtkmm/messagedialog.h>

/**
  * Constructor
  */
StatesTableWindow::StatesTableWindow(DFA* automaton) : 
  // Initialize the buttons and labels
  m_button_done("Done"),
  m_label_table("Select the states for the transition table") {

  // Set the reference of the automaton to the received
  this->automaton = automaton;

  // Initialize the window
  set_title("Transition table");
  // Sets the border width of the window.
  set_border_width(25);
  // This allows autoscaling
  set_resizable(false);

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_states.set_row_spacing(10);
  m_grid_states.set_column_spacing(10);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up the widgets of the top level grid
  add(m_grid_top);
  m_grid_top.add(m_label_table);
  m_grid_top.add(m_grid_states);
  m_grid_top.add(m_button_done);

  // Connect the signals
  // Done button
  m_button_done.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &StatesTableWindow::on_done_clicked
    )
  );

  // Fill the states grid
  // Add the leteter labels
  std::vector<std::string> alphabet = this->automaton->get_alphabet();
  for (int i = 1; i <= alphabet.size(); i++) {
    Gtk::Label* label = Gtk::manage(new Gtk::Label(alphabet.at(i-1)));
    m_grid_states.attach(*label, i, 0, 1, 1);
  }

  // Add the state labels
  std::vector<std::string> states = this->automaton->get_states();
  for (int i = 1; i <= states.size(); i++) {
    Gtk::Label* label = Gtk::manage(new Gtk::Label(states.at(i-1)));
    m_grid_states.attach(*label, 0, i, 1, 1);
  }

  // Fill the grid with cells
  StateCell* cell;
  for (int i = 1; i <= alphabet.size(); i++) {
    for (int j = 1; j <= states.size(); j++) {
      cell = Gtk::manage(new StateCell(states, j-1, alphabet.at(i-1))); 
      m_grid_states.attach(*cell, i, j, 1, 1);
    }
  }

  // Show everything
  show_all_children();
}

/**
  * Destructor
  */
StatesTableWindow::~StatesTableWindow() {}

/**
  * Callback executed when the done button is clicked
  * 
  * Checks that no transition is left empty and adds
  * the transitions to the DFA transition table
  */
void StatesTableWindow::on_done_clicked() {
  // Get the DFA alphabet
  std::vector<std::string> alphabet = this->automaton->get_alphabet();
  // Get the DFA states
  std::vector<std::string> states = this->automaton->get_states();
  // Create an empty transition table
  this->automaton->reset_transition_table();

  // Temporary variables
  StateCell* cell;
  std::string state;
  std::string letter;
  std::string next_state;
  // Empty transition flag
  bool something_wrong = false;

  // Iterate through the grid
  for (int i = 1; i <= alphabet.size(); i++) {
    for (int j = 1; j <= states.size(); j++) {
      cell = (StateCell*) m_grid_states.get_child_at(i, j);
      // Get the selected state
      next_state = cell->get_active_text();
      // If the state is empty turns the flag and breaks the cycle
      if (next_state.empty()) {
        something_wrong = true;
        break;
      }

      // Get the values from the current cell
      state = cell->get_state();
      letter = cell->get_letter();
      
      // Add the transition to the DFA
      this->automaton->add_transition(state, letter, next_state);
    }
  }

  // If the flag is on, sends an alert
  if (something_wrong) {
    Gtk::MessageDialog dialog(*this, "Error");
    dialog.set_secondary_text("Please fix the missing transitions");
    dialog.run();
  } else {
  // Otherwise, 
    hide();
  }
}