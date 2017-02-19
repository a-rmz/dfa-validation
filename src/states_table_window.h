
#ifndef STATES_TABLE_WINDOW_H
#define STATES_TABLE_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include "dfa.h"

class StatesTableWindow : public Gtk::Window {

  public:
    StatesTableWindow(DFA* automaton);
    virtual ~StatesTableWindow();

  protected:
    void on_done_clicked();

    Gtk::Button m_button_done;
    Gtk::Grid m_grid_top, m_grid_states;
    Gtk::Label m_label_table;
    DFA* automaton;

};

#endif // STATES_TABLE_WINDOW_H