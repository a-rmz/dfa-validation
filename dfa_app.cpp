
#include "dfa_app.h"
#include "grid_entry.h"
#include <iostream>
#include <gtkmm/orientable.h>

// creates a new button with label "Hello World".
DFA_app::DFA_app() :
  m_button_add("Add another state"),
  m_button_quit("Close") {
  state_count = 0;
  
  set_title("DFA Validation app");
  // Sets the border width of the window.
  set_border_width(25);
  set_resizable(false);

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_states.set_row_spacing(10);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  m_grid_states.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up top level grid
  add(m_grid_top);
  m_grid_top.add(m_grid_states);
  m_grid_top.add(m_button_add);
  m_grid_top.add(m_button_quit);

  // add_state();

  // Connect the signals
  m_button_add.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DFA_app::add_state
    )
  );

  m_button_quit.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DFA_app::on_quit_clicked
    )
  );

  // Display everything
  show_all_children();
}

DFA_app::~DFA_app() { }

void DFA_app::add_state() {
  GridEntry* entry = Gtk::manage(new GridEntry(&m_grid_states));
  this->m_grid_states.add(*entry);
  this->m_grid_states.show_all_children();
  this->state_count += 1;
}

void DFA_app::on_quit_clicked() {
  auto children = this->m_grid_states.get_children();
  for(auto elem : children) {
    GridEntry* child = (GridEntry*) elem;
    std::cout << child->get_entry_text() << std::endl;
  }
  hide();
}
