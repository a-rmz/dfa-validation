
#include "final_states_window.h"
#include <gtkmm/messagedialog.h>
#include <gtkmm/orientable.h>
#include <gtkmm/checkbutton.h>

#include <iostream>

FinalStatesWindow::FinalStatesWindow(DFA* automaton) :
  m_label_final_states("Select the final states"),
  m_button_quit("Close") {

  this->automaton = automaton;
  set_states(automaton->get_states());
  
  set_title("Select final steps");;
  // Sets the border width of the window.
  set_border_width(25);
  set_resizable(false);

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  m_grid_checks.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up top level grid
  add(m_grid_top);
  m_grid_top.add(m_label_final_states);
  m_grid_top.add(m_grid_checks);
  m_grid_top.add(m_button_quit);

  // Connect the signals
  m_button_quit.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &FinalStatesWindow::on_quit_clicked
    )
  );

  // Display everything
  show_all_children();
}

FinalStatesWindow::~FinalStatesWindow() { }

void FinalStatesWindow::set_states(std::vector<std::string> states) {
  for (std::string state : states) {
    this->m_grid_checks.add(*Gtk::manage(new Gtk::CheckButton(state)));
  }
}

void FinalStatesWindow::on_quit_clicked() {
  std::vector<std::string> final_states;

  for (Gtk::Widget* child : m_grid_checks.get_children()) {
    Gtk::CheckButton* button = (Gtk::CheckButton*) child;
    
    if (button->get_active()) {
      final_states.push_back(button->get_label());
    }
  }

  this->automaton->set_final_states(final_states);
  hide();
}
