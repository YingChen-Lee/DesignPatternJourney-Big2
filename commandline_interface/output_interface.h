#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

#include "../models/hand.h"
#include "../models/card/card.h"

class OutputInterface {
public:
    OutputInterface(const std::string& filepath);
    ~OutputInterface();
    
    void OpenFile();
    void CloseFile();

    void OutputMessage(const std::string& message);
    void OutputHand(const Hand& hand);
    void OutputCards(const std::vector<std::shared_ptr<const Card>>& cards);


private:
    static const std::unordered_map<SuitEnum, std::string> suit_enum_to_string;
    
    std::string CardToString(const Card& card) const;

    std::string filepath_;
    std::ofstream file_;
};