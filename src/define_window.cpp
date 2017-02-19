
#include "define_window.h"
#include "grid_entry.h"
#include "str_utils.h"
#include <iostream>
#include <gtkmm/messagedialog.h>
#include <gtkmm/orientable.h>


DefineWindow::DefineWindow() :
  m_label_lang("Insert the symbols of the language (separted by ' , ')"),
  m_label_states("Insert the states of the DFA"),
  m_button_add("Add another state"),
  m_button_done("Done"),
  m_button_quit("Close") {
  
  set_title("DFA Validation app");;
  // Sets the border width of the window.
  set_border_width(25);
  set_resizable(false);

  this->final_states_window = NULL;

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_states.set_row_spacing(10);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  m_grid_states.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up top level grid
  add(m_grid_top);
  m_grid_top.add(m_label_lang);
  m_grid_top.add(m_entry_lang);
  m_grid_top.add(m_label_states);
  m_grid_top.add(m_grid_states);
  m_grid_top.add(m_button_add);
  m_grid_top.add(m_button_done);
  m_grid_top.add(m_button_quit);

  add_state();
  add_state();

  // Connect the signals
  m_button_add.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::add_state
    )
  );

  m_button_done.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_done_clicked
    )
  );

  m_button_quit.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_quit_clicked
    )
  );

  // Display everything
  show_all_children();
}

DefineWindow::~DefineWindow() { }

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

std::vector<std::string> DefineWindow::get_states() {
  auto children = this->m_grid_states.get_children();
  std::vector<std::string> states;

  for (Gtk::Widget* elem : children) {
    GridEntry* state = (GridEntry*) elem;
    states.push_back(state->get_entry_text());
  }

  return states;
}

void DefineWindow::add_state() {
  GridEntry* entry = Gtk::manage(new GridEntry(&m_grid_states));
  this->m_grid_states.add(*entry);
  this->m_grid_states.show_all_children();
}

void DefineWindow::on_done_clicked() {
  auto children = this->m_grid_states.get_children();
  Gtk::MessageDialog dialog(*this, "Error");

  if (children.size() <= 1) {
    dialog.set_secondary_text("Please add at least two states");
    dialog.run();
  } else if(!states_are_valid()) {
    dialog.set_secondary_text("Please fix the empty state(s)");
    dialog.run();
  } else {
    final_states_window = new FinalStatesWindow();
    final_states_window->set_states(get_states());
    final_states_window->show();
    // hide();
  }
}

void DefineWindow::on_quit_clicked() {
  hide();
}
