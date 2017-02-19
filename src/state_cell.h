
#ifndef STATE_CELL_H
#define STATE_CELL_H

#include <gtkmm/comboboxtext.h>
#include <string>
#include <vector>

class StateCell : public Gtk::ComboBoxText {

  public:
    StateCell(std::vector<std::string> states, int current_state, std::string letter);
    virtual ~StateCell();
    void set_state(std::string state);
    std::string get_state();
    void set_letter(std::string letter);
    std::string get_letter();
    std::string get_key();  
  
  private:
    std::string state;
    std::string letter;
    std::string key;

};

#endif //STATE_CELL_H