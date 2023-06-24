#pragma once

#include <fstream>
#include <unordered_map>
#include <string>
#include <deque>
#include <vector>

#include "input_interface.h"

#include "../models/deck.h"
#include "../models/card/suit.h"
#include "../models/card/rank.h"

class InputInterfaceFile : public InputInterface {
public:
    InputInterfaceFile(const std::string& filepath);
    virtual ~InputInterfaceFile() = default;

    virtual Deck GetDeck() override;    
    virtual std::string GetNextPlayerName() override;
    virtual std::vector<int> GetNextPlayIndices() override;

private:
    static const std::unordered_map<std::string, SuitEnum> string_to_suit_enum;
    static const std::unordered_map<std::string, RankEnum> string_to_rank_enum;

    void OpenFile();
    void CloseFile();

    Card GetCard(const std::string& card_string);

    void GetPlayersNameFromFile();
    void GetDeckFromFile();
    void GetPlayIndicesFromFile();

    std::deque<std::string> players_name_;
    Deck deck_;
    std::deque<std::vector<int>> play_indices_;

    std::string filepath_;
    std::ifstream file_;
};