#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <map>
#include "Automaton.h"

#define TEST_FOLDER "C:\\Users\\User\\CLionProjects\\SysProgLab2\\tests"

void processFilesInsideDir(const std::string &pathToDir);

void processFile(const std::string &path);

int main() {
    processFilesInsideDir(TEST_FOLDER);
    return 0;
}

void processFilesInsideDir(const std::string &pathToDir) {
    for (const auto &entry: std::filesystem::directory_iterator(pathToDir)) {
        if (entry.is_directory()) {
            continue;
        }
        processFile(entry.path().string());
    }
}

void processFile(const std::string &path) {
    Automaton automaton = initialize_automation(path);
    std::cout << "For file - " << path << std::endl;
    automaton.get_unreached_states();
    automaton.get_dead_states();
}
