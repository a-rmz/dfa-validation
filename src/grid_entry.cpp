
#include "grid_entry.h"

GridEntry::GridEntry(Gtk::Grid* parent) : m_button_remove("Remove state") {
  this->parent = parent;
  this->set_spacing(8);
  this->pack_start(m_entry_state);
  this->pack_end(m_button_remove);

  m_button_remove.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &GridEntry::on_remove_clicked
    )
  );

  // Display everything
  show_all_children();
};

GridEntry::~GridEntry() { }

void GridEntry::on_remove_clicked() {
  this->parent->remove(*this);
  this->parent->show_all_children();
}

std::string GridEntry::get_entry_text() {
  return std::string(m_entry_state.get_text()); 
};