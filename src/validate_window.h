
#ifndef VALIDATE_WINDOW_H
#define VALIDATE_WINDOW_H

#include "dfa.h"
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

class ValidateWindow : public Gtk::Window {
  
  public:
    ValidateWindow(DFA* automaton);
    virtual ~ValidateWindow();

  protected:
    void on_validate_clicked();
    void on_quit_clicked();
    
    Gtk::Button m_button_validate, m_button_quit;
    Gtk::Entry m_entry_word;
    Gtk::Grid m_grid_top;
    Gtk::Label m_label_validate;

  private:
    DFA* automaton;

};

#endif // VALIDATE_WINDOW_H