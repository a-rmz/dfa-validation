
#include "grid_entry.h"

/**
  * Constructor
  */
GridEntry::GridEntry(Gtk::Grid* parent) :
  // Initialize the button
  m_button_remove("Remove state") {
  
  // Set the parent widget
  this->parent = parent;

  // Add spacing
  this->set_spacing(8);
  // Add the widgets to the box
  this->pack_start(m_entry_state);
  this->pack_end(m_button_remove);

  // Connect the signals
  // Remove button
  m_button_remove.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &GridEntry::on_remove_clicked
    )
  );

  // Display everything
  show_all_children();
};

/**
  * Destructor
  */
GridEntry::~GridEntry() { }

/**
  * Callback executed when the remove button is clicked
  * 
  * Removes itself from the parent grid
  */
void GridEntry::on_remove_clicked() {
  // Remove the self reference
  this->parent->remove(*this);
  // Updates the view on parent
  this->parent->show_all_children();
}

/**
  * Getter: Entry text casted to std::string
  */
std::string GridEntry::get_entry_text() {
  return std::string(m_entry_state.get_text()); 
};