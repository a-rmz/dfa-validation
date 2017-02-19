
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
  m_button_final_states("Select Final states"),
  m_button_states_table("Add transition table"),
  m_button_validate("Validate words"),
  m_button_quit("Close") {
  
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
  
  // Set up top level grid
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

  add_state();
  add_state();

  // Connect the signals
  m_button_add.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::add_state
    )
  );

  m_button_final_states.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_final_states_clicked
    )
  );
  
  m_button_states_table.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_states_table_clicked
    )
  );

  m_button_validate.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &DefineWindow::on_validate_clicked
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

void DefineWindow::on_final_states_clicked() {
  auto children = this->m_grid_states.get_children();
  Gtk::MessageDialog dialog(*this, "Error");

  if (children.size() <= 1) {
    dialog.set_secondary_text("Please add at least two states");
    dialog.run();
  } else if (!states_are_valid()) {
    dialog.set_secondary_text("Please fix the empty state(s)");
    dialog.run();
  } else {
    // Set the states
    this->automaton.set_states(get_states());

    final_states_window = new FinalStatesWindow(&this->automaton);    
    final_states_window->show();
  }
}

void DefineWindow::on_states_table_clicked() {
  auto children = this->m_grid_states.get_children();
  Gtk::MessageDialog dialog(*this, "Error");

  if (children.size() <= 1) {
    dialog.set_secondary_text("Please add at least two states");
    dialog.run();
  } else if (!states_are_valid()) {
    dialog.set_secondary_text("Please fix the empty state(s)");
    dialog.run();
  } else if (this->automaton.get_final_states().size() < 1) {
    dialog.set_secondary_text("Please select at least one final state");
    dialog.run();
  } else if (split(this->m_entry_lang.get_text(), ',').size() < 2) {
    dialog.set_secondary_text("Please insert at least two letters to the alphabet");
    dialog.run();
  } else {
    // Get the alphabet
    std::vector<std::string> alphabet = split(this->m_entry_lang.get_text(), ',');
    this->automaton.set_alphabet(alphabet);

    // Set the states
    this->automaton.set_states(get_states());

    states_table_window = new StatesTableWindow(&this->automaton);    
    states_table_window->show();
  }
}

void DefineWindow::on_validate_clicked() {
  // Validate transition table not empty
  validate_window = new ValidateWindow(&this->automaton);    
  validate_window->show();
}

void DefineWindow::on_quit_clicked() {
  hide();
}
