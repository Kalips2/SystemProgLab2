//
// Created by User on 10/4/2023.
//

#ifndef SYSPROGLAB2_AUTOMATON_H
#define SYSPROGLAB2_AUTOMATON_H

#include <set>
#include <algorithm>

struct Automaton {
    int size_elements;
    int size_states;
    int startState;
    int size_final_states;
    std::vector<int> finalStates;
    std::map<int, std::map<char, int>> transitions;

    [[nodiscard]] std::set<int> get_all_states() const {
        std::set<int> all_states;
        for (int i = 0; i < size_states; ++i) {
            all_states.insert(i);
        }
        return all_states;
    }

    void get_unreached_states() {
        std::set<int> reachable_states;
        reachable_states.insert(startState);

        // Шукаємо усі можливі досяжні стани
        std::set<int> new_reachable_states(reachable_states);
       do {
            reachable_states.insert(new_reachable_states.begin(), new_reachable_states.end());
            for (int state: reachable_states) {
                for (const auto &entry: transitions[state]) {
                    new_reachable_states.insert(entry.second);
                }
            }
        }  while (reachable_states != new_reachable_states && !new_reachable_states.empty());

        // { all } / { reachable } = { unreachable }
        std::set<int> unreachable_states;
        const std::set<int> &all_states = get_all_states();
        std::set_difference(all_states.begin(), all_states.end(), reachable_states.begin(), reachable_states.end(),
                            std::inserter(unreachable_states, unreachable_states.end()));

        if (unreachable_states.empty()) {
            std::cout << "There are no unreachable states." << std::endl;
        } else {
            std::cout << "Unreachable states: ";
            for (int state: unreachable_states) {
                std::cout << state << " ";
            }
            std::cout << std::endl;
        }
    }

    void get_dead_states() {
        std::set<int> non_dead_states(finalStates.begin(), finalStates.end());

        // Шукаємо усі states, які можуть привести до фінальних станів
        std::set<int> new_non_dead_states(non_dead_states);
        do {
            non_dead_states.insert(new_non_dead_states.begin(), new_non_dead_states.end());
            for (int state: non_dead_states) {
                for (const auto &entry: transitions) {
                    for (const auto &transition: entry.second) {
                        if (transition.second == state) {
                            new_non_dead_states.insert(entry.first);
                            break;
                        }
                    }
                }
            }
        } while (non_dead_states != new_non_dead_states && !new_non_dead_states.empty());

        // { all } / { non_dead } = { dead }
        std::set<int> dead_states;
        const std::set<int> &all_states = get_all_states();
        std::set_difference(all_states.begin(), all_states.end(), non_dead_states.begin(), non_dead_states.end(),
                            std::inserter(dead_states, dead_states.end()));

        if (dead_states.empty()) {
            std::cout << "There are no dead states." << std::endl;
        } else {
            std::cout << "Dead states: ";
            for (int state: dead_states) {
                std::cout << state << " ";
            }
            std::cout << std::endl;
        }
    }

};

Automaton initialize_automation(const std::string &path);

#endif //SYSPROGLAB2_AUTOMATON_H
