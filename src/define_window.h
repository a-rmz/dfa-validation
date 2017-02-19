
#ifndef FINAL_STATES_WINDOW_H
#define FINAL_STATES_WINDOW_H

#include "grid_entry.h"
#include "final_states_window.h"
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>
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
  void on_done_clicked();
  void on_add_clicked();
  void add_state();

  //Member widgets:
  Gtk::Label m_label_lang, m_label_states;
  Gtk::Grid m_grid_top, m_grid_states;
  Gtk::Entry m_entry_lang;
  Gtk::Button m_button_add, m_button_done, m_button_quit;
  FinalStatesWindow* final_states_window;
};

#endif // FINAL_STATES_WINDOW_H