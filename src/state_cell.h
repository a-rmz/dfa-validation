
#include <gtkmm/entry.h>
#include <string>

class StateCell : public Gtk::Entry {

  public:
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