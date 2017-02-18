
#ifndef GRID_ENTRY_H
#define GRID_ENTRY_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <string>

class GridEntry : public Gtk::Box {
  
  public:
    GridEntry(Gtk::Grid* parent);
    virtual ~GridEntry();
    std::string get_entry_text();

  protected:
    void on_remove_clicked();

    Gtk::Grid* parent;
    Gtk::Entry m_entry_state;
    Gtk::Button m_button_remove;
};

#endif // GRID_ENTRY_H