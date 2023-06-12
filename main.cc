#include <iostream>
#include <string>

#include "commandline_interface/input_interface.h"
#include "commandline_interface/output_interface.h"

#include "models/hand.h"

int main() {
    std::string input_file_name = "../測資集合/fullhouse.in";
    std::string output_file_name = "../測資集合/my_output/fullhouse.test.out";

    InputInterface input_interface(input_file_name);
    OutputInterface output_interface(output_file_name);

    Deck deck = input_interface.GetDeck();
    std::vector<std::string> players_name = input_interface.GetPlayersName();
    std::vector<int> play_indices = input_interface.GetNextPlayIndices();
    
    std::cout << "Deck size: " << deck.size() << std::endl;
    std::cout << "Players name: ";
    for (const auto& name : players_name)
        std::cout << name << " ";
    std::cout << std::endl;
    
    std::cout << "Play indices: ";
    for (const auto& index : play_indices)
        std::cout << index << " ";
    std::cout << std::endl;
    
    
    output_interface.OutputMessage("Hello world!\n");
    Hand hand;
    for (int i = 0; i < 52; i++)
        hand.AddCard(deck.DrawOneCard());
    output_interface.OutputCards(hand.get_cards());

    return 0;
}