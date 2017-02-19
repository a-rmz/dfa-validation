
#include <gtkmm/label.h>
#include <gtkmm/messagedialog.h>
#include "states_table_window.h"
#include "state_cell.h"
#include "dfa.h"

StatesTableWindow::StatesTableWindow(DFA* automaton) : 
  m_button_done("Done"),
  m_label_table("Select the states for the transition table") {
  this->automaton = automaton;

  set_title("Transition table");
  // Sets the border width of the window.
  set_border_width(25);
  set_resizable(false);

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_states.set_row_spacing(10);
  m_grid_states.set_column_spacing(10);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  // m_grid_states.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up top level grid
  add(m_grid_top);
  m_grid_top.add(m_label_table);
  m_grid_top.add(m_grid_states);
  m_grid_top.add(m_button_done);

  // Listeners
  m_button_done.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &StatesTableWindow::on_done_clicked
    )
  );

  // Fill the states grid
  std::vector<std::string> alphabet = this->automaton->get_alphabet();
  for (int i = 1; i <= alphabet.size(); i++) {
    Gtk::Label* label = Gtk::manage(new Gtk::Label(alphabet.at(i-1)));
    m_grid_states.attach(*label, i, 0, 1, 1);
  }

  std::vector<std::string> states = this->automaton->get_states();
  for (int i = 1; i <= states.size(); i++) {
    Gtk::Label* label = Gtk::manage(new Gtk::Label(states.at(i-1)));
    m_grid_states.attach(*label, 0, i, 1, 1);
  }

  // Fill the cells
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

StatesTableWindow::~StatesTableWindow() {}

void StatesTableWindow::on_done_clicked() {
  std::vector<std::string> alphabet = this->automaton->get_alphabet();
  std::vector<std::string> states = this->automaton->get_states();
  StateCell* cell;
  std::string state;
  std::string letter;
  std::string next_state;
  bool something_wrong = false;

  for (int i = 1; i <= alphabet.size(); i++) {
    for (int j = 1; j <= states.size(); j++) {
      cell = (StateCell*) m_grid_states.get_child_at(i, j);
      next_state = cell->get_active_text();
      if (next_state.empty()) {
        something_wrong = true;
        break;
      }

      state = cell->get_state();
      letter = cell->get_letter();
      this->automaton->add_transition(state, letter, next_state);
    }
  }

  if (something_wrong) {
    Gtk::MessageDialog dialog(*this, "Error");
    dialog.set_secondary_text("Please fix the missing transitions");
    dialog.run();
  } else {
    hide();
  }
}