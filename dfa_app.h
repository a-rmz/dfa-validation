
#ifndef DFA_APP_H
#define DFA_APP_H

#include "grid_entry.h"
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <glibmm/ustring.h>
#include <vector>

class DFA_app : public Gtk::Window {

public:
  DFA_app();
  virtual ~DFA_app();
  int state_count;

protected:
  //Signal handlers:
  void on_quit_clicked();
  void on_add_clicked();
  void add_state();

  //Member widgets:
  Gtk::Grid m_grid_top, m_grid_states;
  std::vector<GridEntry> state;
  Gtk::Button m_button_add, m_button_quit;
};

#endif // DFA_APP_H