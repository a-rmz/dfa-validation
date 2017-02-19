
#include "define_window.h"
#include <gtkmm/application.h>
#include <iostream>

#include "dfa.h"

int main (int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  DefineWindow define_window;

  DFA automaton = DFA();
  std::vector<std::string> states;
  states.push_back("q0");
  states.push_back("q1");
  states.push_back("q2");
  automaton.set_states(states);

  std::vector<std::string> final_states;
  final_states.push_back("q1");
  automaton.set_final_states(final_states);

  std::vector<std::string> alphabet;
  alphabet.push_back("1");
  alphabet.push_back("0");
  automaton.set_alphabet(alphabet);


  automaton.add_transition("q0", "0", "q0");
  automaton.add_transition("q1", "0", "q0");
  automaton.add_transition("q2", "0", "q2");

  automaton.add_transition("q0", "1", "q1");
  automaton.add_transition("q1", "1", "q2");
  automaton.add_transition("q2", "1", "q1");

  std::string word;
  std::cin >> word;
  std::cout << "The word " << word << " is " << automaton.is_word_valid(word) << std::endl;


  return 0;
  //Shows the window and returns when it is closed.
  // return app->run(define_window);
}