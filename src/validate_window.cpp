
#include "validate_window.h"
#include <gtkmm/messagedialog.h>
#include <string>

/**
  * Constructor
  */
ValidateWindow::ValidateWindow(DFA* automaton) :
  // Initialize the buttons and labels
  m_label_validate("Enter the word to validate"),
  m_button_validate("Validate"),
  m_button_quit("Close") {

  // Set the reference of the automaton to the received
  this->automaton = automaton;

  // Initialize the window
  set_title("Validate words");
  // Sets the border width of the window.
  set_border_width(25);
  // This allows autoscaling
  set_resizable(false);

  // Grids setup
  m_grid_top.set_row_spacing(5);
  m_grid_top.set_orientation(Gtk::ORIENTATION_VERTICAL);
  
  // Set up the widgets of the top level grid
  add(m_grid_top);
  m_grid_top.add(m_label_validate);
  m_grid_top.add(m_entry_word);
  m_grid_top.add(m_button_validate);
  m_grid_top.add(m_button_quit);
  
  // Connect the signals
  // Validate
  m_button_validate.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &ValidateWindow::on_validate_clicked
    )
  );

  // Close
  m_button_quit.signal_clicked().connect(
    sigc::mem_fun(
      *this,
      &ValidateWindow::on_quit_clicked
    )
  );

  // Display everything
  show_all_children();
}

/**
  * Destructor
  */
ValidateWindow::~ValidateWindow() {};

/**
  * Callback executed when the validate button is clicked
  * 
  * Validates that the word is not empty. Then, calls the DFA validation method.
  * Depending on the result, shows a message saying that the word is either valid
  * or not valid.
  */
void ValidateWindow::on_validate_clicked() {
  // Retreive the word
  std::string word = m_entry_word.get_text();

  // Check if the word is empty
  if (word.empty()) {
    // Send an alert
    Gtk::MessageDialog dialog(*this, "Error");
    dialog.set_secondary_text("Please enter a word");
    dialog.run();
  } else {
    // Call the DFA validation method and set the message
    std::string message = (this->automaton->is_word_valid(word)) ? "valid" : "not valid";
    // Create a dialog
    Gtk::MessageDialog dialog(*this, "The automaton says:");
    // Set the message to the result
    dialog.set_secondary_text("The enterd word is " + message);
    dialog.run();
  }
}

/**
  * Callback executed when the Close button is clicked
  * 
  * Closes the window
  */
void ValidateWindow::on_quit_clicked() {
  hide();
}