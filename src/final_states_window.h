
#ifndef DEFINE_WINDOW_H
#define DEFINE_WINDOW_H

#include "grid_entry.h"
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>
#include <vector>
#include <string>

class FinalStatesWindow : public Gtk::Window {

public:
  FinalStatesWindow();
  virtual ~FinalStatesWindow();
  void set_states(std::vector<std::string> states);

protected:
  //Signal handlers:
  void on_quit_clicked();

  // Internal:
  std::vector<std::string> states;

  //Member widgets:
  Gtk::Label m_label_final_states;
  Gtk::Grid m_grid_top, m_grid_checks;
  Gtk::Button m_button_quit;
};

#endif // DEFINE_WINDOW_H