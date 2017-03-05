
#ifndef DEFINE_WINDOW_H
#define DEFINE_WINDOW_H

#include "dfa.h"
#include "grid_entry.h"
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <string>
#include <vector>

class FinalStatesWindow : public Gtk::Window {

public:
  FinalStatesWindow(DFA* automaton);
  virtual ~FinalStatesWindow();

protected:
  //Signal handlers:
  void on_quit_clicked();
  void set_states(std::vector<std::string> states);

  //Member widgets:
  Gtk::Label m_label_final_states;
  Gtk::Grid m_grid_top, m_grid_checks;
  Gtk::Button m_button_quit;

  // Reference to the DFA
  DFA* automaton;  
};

#endif // DEFINE_WINDOW_H