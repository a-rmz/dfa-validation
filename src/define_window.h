
#ifndef FINAL_STATES_WINDOW_H
#define FINAL_STATES_WINDOW_H

#include "final_states_window.h"
#include "states_table_window.h"
#include "validate_window.h"
#include "dfa.h"
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <vector>
#include <string>

class DefineWindow : public Gtk::Window {

public:
  DefineWindow();
  virtual ~DefineWindow();
  bool lang_is_valid();
  bool states_are_valid();
  std::vector<std::string> get_states();

protected:
  //Signal handlers:
  void on_quit_clicked();
  void on_final_states_clicked();
  void on_states_table_clicked();
  void on_validate_clicked();
  void on_add_clicked();
  void add_state();

  //Member widgets:
  Gtk::Label m_label_lang, m_label_states;
  Gtk::Grid m_grid_top, m_grid_states;
  Gtk::Entry m_entry_lang;
  Gtk::Button m_button_add, m_button_final_states, m_button_states_table, m_button_validate, m_button_quit;
  FinalStatesWindow* final_states_window;
  StatesTableWindow* states_table_window;
  ValidateWindow* validate_window;
  
  // Original reference to the automaton
  DFA automaton;
};

#endif // FINAL_STATES_WINDOW_H