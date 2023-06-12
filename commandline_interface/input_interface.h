#pragma once

#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

#include "../models/deck.h"
#include "../models/card/suit.h"
#include "../models/card/rank.h"

class InputInterface {
public:
    InputInterface(const std::string& filepath);
    ~InputInterface();
    
    void OpenFile();
    void CloseFile();

    Deck GetDeck();    
    std::vector<std::string> GetPlayersName();
    std::vector<int> GetNextPlayIndices();

private:
    static const std::unordered_map<std::string, SuitEnum> string_to_suit_enum;
    static const std::unordered_map<std::string, RankEnum> string_to_rank_enum;

    Card GetCard(const std::string& card_string);

    std::string filepath_;
    std::ifstream file_;
};