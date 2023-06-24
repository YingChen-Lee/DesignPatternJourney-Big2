#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../models/hand.h"
#include "../models/card/card.h"

class OutputInterface {
public:
    OutputInterface(const std::string& filepath);
    ~OutputInterface();
    
    void OpenFile();
    void CloseFile();

    void OutputMessage(const std::string& message); 
    void OutputStartNewRound();
    void OutputPlayerTurn(const std::string& player_name);
    void OutputHand(const Hand& hand);
    void OutputCards(const std::vector<Card>& cards);
    void OutputPass(const std::string& player_name, bool is_valid);
    void OutputPlay(const std::string& player_name, const std::vector<Card>& cards,
                    const std::string& card_pattern_name);
    void OutputInvalidPlay(const std::string& player_name);
    void OutputWinner(const std::string& player_name);

private:
    static const std::unordered_map<SuitEnum, std::string> suit_enum_to_string;
    
    std::string CardToString(const Card& card) const;

    std::string filepath_;
    std::ofstream file_;
};