#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "Automaton.h"

Automaton initialize_automation(const std::string& path) {
    Automaton automaton;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        exit(1);
    }

    file >> automaton.size_elements;
    file >> automaton.size_states;
    file >> automaton.startState;

    int number_of_final_states;
    file >> number_of_final_states;

    automaton.size_final_states = number_of_final_states;
    automaton.finalStates.resize(number_of_final_states);
    for (int i = 0; i < number_of_final_states; ++i) {
        file >> automaton.finalStates[i];
    }

    int from, to;
    char transitionChar;
    while (file >> from >> transitionChar >> to) {
        automaton.transitions[from][transitionChar].insert(to);
    }

    file.close();
    return automaton;
}
