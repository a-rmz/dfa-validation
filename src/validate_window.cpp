
#include "validate_window.h"
#include <string>
#include <gtkmm/messagedialog.h>

ValidateWindow::ValidateWindow(DFA* automaton) :
  m_label_validate("Enter the word to validate"),
  m_button_validate("Validate"),
  m_button_quit("Close") {
  this->automaton = automaton;

  set_title("Validate words");
  // Sets the border width of the window.
  set_border_width(25);
  set_resizable(false);

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up top level grid
  add(m_grid_top);
  m_grid_top.add(m_label_validate);
  m_grid_top.add(m_entry_word);
  m_grid_top.add(m_button_validate);
  m_grid_top.add(m_button_quit);
  

  m_button_validate.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &ValidateWindow::on_validate_clicked
    )
  );

  m_button_quit.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &ValidateWindow::on_quit_clicked
    )
  );

  show_all_children();
}

ValidateWindow::~ValidateWindow() {};

void ValidateWindow::on_validate_clicked() {
  std::string word = m_entry_word.get_text();

  if (word.empty()) {
    Gtk::MessageDialog dialog(*this, "Error");
    dialog.set_secondary_text("Please enter a word");
    dialog.run();
  } else {
    std::string message = (this->automaton->is_word_valid(word)) ? "valid" : "not valid";
    Gtk::MessageDialog dialog(*this, "The automaton says:");
    dialog.set_secondary_text("The enterd word is " + message);
    dialog.run();
  }

}

void ValidateWindow::on_quit_clicked() {
  hide();
}