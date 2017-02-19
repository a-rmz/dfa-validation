
#ifndef DFA_H
#define DFA_H

#include <string>
#include <vector>
#include <unordered_map>

class DFA {

  public:
    DFA();
    virtual ~DFA();
    std::vector<std::string> get_states();
    void set_states(std::vector<std::string> states);
    std::vector<std::string> get_final_states();
    void set_final_states(std::vector<std::string> final_states);
    std::vector<std::string> get_alphabet();
    void set_alphabet(std::vector<std::string> alphabet);
    bool is_final_state(std::string state);
    void add_transition(std::string state, std::string letter, std::string next);
    std::unordered_map<std::string, std::string> get_transitions();
    bool is_word_valid(std::string word);
    bool is_letter_in_alphabet(std::string letter);

  private:
    std::vector<std::string> states;
    std::vector<std::string> final_states;
    std::vector<std::string> alphabet;
    std::vector<std::string> keys;
    void create_keys();

    std::unordered_map<std::string, std::string> state_transition_table;
};

#endif // DFA_H