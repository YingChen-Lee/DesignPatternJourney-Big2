#include "input_interface_terminal.h"

#include <iostream>
#include <sstream>

std::string InputInterfaceTerminal::GetNextPlayerName() {
    std::string next_player_name;
    std::cout << "Enter next player name: ";
    
    std::cin.clear();
    fflush(stdin);
    std::getline(std::cin, next_player_name);

    return next_player_name;
}

std::vector<int> InputInterfaceTerminal::GetNextPlayIndices() {
    std::vector<int> next_play_indices;
    // get a new line from std::cin
    std::cin.clear();
    fflush(stdin);
    std::string line;
    std::cout << "Enter next play indices: ";
    std::getline(std::cin, line);

    std::istringstream iss(line);
    std::string index_string;
    while (iss >> index_string)
        next_play_indices.push_back(std::stoi(index_string));
    return next_play_indices;
}
