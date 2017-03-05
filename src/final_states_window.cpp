
#include "final_states_window.h"
#include <gtkmm/checkbutton.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/orientable.h>

/**
  * Constructor
  */
FinalStatesWindow::FinalStatesWindow(DFA* automaton) :
  // Initialize the buttons and labels
  m_label_final_states("Select the final states"),
  m_button_quit("Close") {

  // Set the reference of the automaton to the received
  this->automaton = automaton;
  // Set the states to those of the DFA
  set_states(automaton->get_states());
  
  // Initialize the window
  set_title("Select final steps");;
  // Sets the border width of the window.
  set_border_width(25);
  // This allows autoscaling
  set_resizable(false);

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  m_grid_checks.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up the widgets of the top level grid
  add(m_grid_top);
  m_grid_top.add(m_label_final_states);
  m_grid_top.add(m_grid_checks);
  m_grid_top.add(m_button_quit);

  // Connect the signals
  // Close button
  m_button_quit.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &FinalStatesWindow::on_quit_clicked
    )
  );

  // Display everything
  show_all_children();
}

/**
  * Destructor
  */
FinalStatesWindow::~FinalStatesWindow() { }

/**
  * Sets the CheckBoxes of the states with the states of the DFA
  */
void FinalStatesWindow::set_states(std::vector<std::string> states) {
  // For each state
  for (std::string state : states) {
    // Add a new CheckBox to the grid
    this->m_grid_checks.add(*Gtk::manage(new Gtk::CheckButton(state)));
  }
}

/**
  * Callback executed when the close button is clicked
  * 
  * Sets the final states of the DFA
  */
void FinalStatesWindow::on_quit_clicked() {
  // Temporal storage for the retreived final states
  std::vector<std::string> final_states;

  // For each CheckBox in the grid
  for (Gtk::Widget* child : m_grid_checks.get_children()) {
    Gtk::CheckButton* button = (Gtk::CheckButton*) child;
    
    // If the button is active, is a final state
    if (button->get_active()) {
      final_states.push_back(button->get_label());
    }
  }

  // Set the DFA final states
  this->automaton->set_final_states(final_states);
  // Close the window
  hide();
}
